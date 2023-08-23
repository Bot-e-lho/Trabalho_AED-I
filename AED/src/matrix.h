#ifndef MATRIX_H
#define MATRIX_H
#include <stdio.h>
#include <stdlib.h>

struct matrix {
    struct matrix* right;
    struct matrix* below;
    int line;
    int column;
    float info;
};
typedef struct matrix Matrix;

Matrix* matrix_create( void );
void matrix_heads( Matrix* m, int l, int c );
void matrix_destroy( Matrix* m );
void matrix_print( Matrix* m );
Matrix* matrix_create_with_values( int m, int n, float** values );
Matrix* matrix_add( Matrix* m, Matrix* n );
Matrix* matrix_multiply( Matrix* m, Matrix* n );
Matrix* matrix_transpose( Matrix* m );
float matrix_getelem( Matrix* m, int x, int y );
void matrix_setelem( Matrix* m, int x, int y, float elem );

Matrix* matrix_create( void ) {
    Matrix* matrix = (Matrix*)malloc(sizeof(Matrix));

    // Cria a cabeça inicial
    matrix->line = -1;
    matrix->column = -1;
    matrix->right = matrix;
    matrix->below = matrix;

    // Cria o restante das cabeças
    int m = 0, n = 0;
    printf( "\nInforme o tamanho da matrix (linha x coluna):\n" );
    scanf( "%d %d", &m, &n );
    if( m <= 0 || n <= 0 ) {//Adicionado
        printf( "Quantidade de colunas e linhas incompativel.\n" );
        exit( 1 );
    }
    matrix_heads( matrix, m, n );

    // Adiciona os valores na matrix
    printf( "\nInforme a coordenada(x,y) e o seu valor:\n" );
    while( 1 ) {
        int i = 1, j = 1;
        float valor = 0.0;
        scanf("%d %d %f", &i, &j, &valor);
        if( i == -1 || j == -1 || valor == -1 || valor == 0 ) {// acaba ao inserir as coordenadas/valor -1 ou valor 0
            break;
        }
        if( i >= 0 && i < m && j >= 0 && j < n ) {
            matrix_setelem( matrix, i, j, valor );
        } else {
            printf( "Posicao invalida\n" );
        }
    }
    return matrix;
}

void matrix_heads( Matrix* m, int l, int c ) {
    // Preenche todas as cabeças das linhas
    for( int i = 0; i < l; i++ ) {
        Matrix* new_node = ( Matrix* ) malloc ( sizeof( Matrix ) );
        Matrix* aux = m->below;
        while( aux->below != m ) {
            aux = aux->below;
        }
        new_node->line = i;
        new_node->column = -1;
        aux->below = new_node;
        new_node->below = m;
        new_node->right = new_node;
    }
    // Preenche todas as cabeças das colunas
    for( int i = 0; i < c; i++ ) {
        Matrix* new_node = ( Matrix* ) malloc ( sizeof( Matrix ) );
        Matrix* aux = m->right;
        while( aux->right != m ) {
            aux = aux->right;
        }
        new_node->line = -1;
        new_node->column = i;
        aux->right = new_node;
        new_node->right = m;
        new_node->below = new_node;
    }
}

void matrix_destroy( Matrix* m ) {//possui leak
    if ( m == NULL ) {
        return;
    }
    
    Matrix* r_head = m;
    Matrix* aux = r_head->below;
    
    while( aux != r_head ) {
        Matrix* temp = aux->right;
        while( temp != aux ) {
            Matrix* temp_2 = temp->right;
            free( temp );
            temp = temp_2;
        }
        Matrix* r_next = aux->below;
        free( aux );
        aux = r_next;
    }
    free( m );
}

void matrix_print( Matrix* m ) {
    if ( m == NULL ) {
        printf( "\nA matriz esta vazia\n" );
        return;
    }
    Matrix* test = m->right;
    while( test->right != m ) {
        test = test->right;
    }

    Matrix* r_head = m;
    Matrix* aux_row = r_head->below;

    while( aux_row != r_head ) {
        Matrix* aux_col = aux_row->right;
        
        for( int i = 0; i < test->column + 1; i++ ) {
            if( aux_col != NULL && aux_col->column == i ) {
                printf( "%.2f\t", aux_col->info );
                aux_col = aux_col->right;
            } else {
                printf( "%.2f\t", 0.00 );
            }
        }

        printf( "\n" );
        aux_row = aux_row->below;
    }
}

Matrix* matrix_create_with_values( int m, int n, float** values ) {
    Matrix* matrix = ( Matrix* )malloc( sizeof( Matrix ) );
    matrix->line = m;
    matrix->column = n;
    matrix->right = matrix;
    matrix->below = matrix;

    matrix_heads( matrix, m, n );

    for( int i = 0; i < m; i++ ) {
        for( int j = 0; j < n; j++ ) {
            float valor = values[i][j];
            matrix_setelem( matrix, i, j, valor );
        }
    }

    return matrix;
}

Matrix* matrix_add( Matrix* m, Matrix* n ) {
    if( m == NULL || n == NULL || m->line != n->line || m->column != n->column ) {
        return NULL;
    }
    
    Matrix* aux = m->below;
    while( aux->below != m ) {
        aux = aux->below;
    }
    int line = aux->line + 1;
    aux = m->right;
    while( aux->right != m ) {
        aux = aux->right;
    }
    int column = aux->column + 1;

    float** res = (float**)malloc(line* sizeof(float*));
    for( int i = 0; i < line; i++ ) {
        res[i] = (float*)malloc(column * sizeof(float));
        for( int j = 0; j < column; j++ ) {
            res[i][j] = matrix_getelem( m, i, j ) + matrix_getelem( n, i, j );
        }
    }

    Matrix* matrix = matrix_create_with_values(line, column, res);

    for( int i = 0; i < line; i++ ) {
        free( res[i] );
    }
    free( res );

    return matrix;
}

Matrix* matrix_multiply( Matrix* m, Matrix* n ) {
    if( m == NULL || n == NULL || m->column != n->line ) {
        return NULL;
    }

    int m_linha = m->line;
    int m_col = m->column;
    //int n_linha = n->line;
    int n_col = n->column;

    float** res = (float**)malloc(m_linha * sizeof(float*));
    for( int i = 0; i < m_linha; i++ ) {
        res[i] = ( float* )malloc( n_col * sizeof( float ) );
        for( int j = 0; j < n_col; j++ ) {
            float value = 0.0;
            for (int k = 0; k < m_col; k++) {
                value += matrix_getelem( m, i, k ) * matrix_getelem( n, k, j );
            }
            res[i][j] = value;
        }
    }

    Matrix* matrix = matrix_create_with_values(m_linha, n_col, res);

    for( int i = 0; i < m_linha; i++ ) {
        free( res[i] );
    }
    free( res );

    return matrix;
}

Matrix* matrix_transpose( Matrix* m ) {
    if( m == NULL ) {
        return NULL;
    }

    int m_linha = m->column;
    int m_col = m->line;

    float** res = (float**)malloc(m_linha * sizeof(float*));
    for( int i = 0; i < m_linha; i++ ) {
        res[i] = ( float* )malloc( m_col * sizeof( float ) );
        for( int j = 0; j < m_col; j++ ) {
            res[i][j] = matrix_getelem( m, j, i );
        }
    }

    Matrix* matrix = matrix_create_with_values(m_linha, m_col, res);

    for( int i = 0; i < m_linha; i++ ) {
        free( res[i] );
    }
    free( res );

    return matrix;
}

float matrix_getelem( Matrix* m, int x, int y ) {
    if( m == NULL || x < 0 || y < 0 ) {
	    return 0.00;
    }
    Matrix* r_head = m;
    Matrix* aux = r_head->below;
  	while( aux != r_head || aux->line != x ) {
	  	aux = aux->below;
    } 
 	if( aux == r_head ) {
	    return 0.00;
	} 
	Matrix* temp = aux->right;
	while( temp != aux || temp->column != y ) {
		temp = temp->right;
	}
	if( temp == aux ) {
	    return 0.00;
	}
	
  return temp->info;
}

void matrix_setelem( Matrix* m, int x, int y, float elem ) {
    if( m == NULL || x < 0 || y < 0 ) {//Dei uma arrumada aqui a tua logica tava certa mas tu não tinha feito o percurso para chegar na posição que tu queria chegar
	    return;
    }
    Matrix* r_head = m;
    Matrix* aux = r_head->below;
    while( aux != r_head && aux->line != x ) {
	    aux = aux->below;
    } 
    if( aux == r_head ) {
        return;
    } 
    Matrix* temp_1 = aux;
    Matrix* temp_2 = aux->right;
    while( temp_2 != aux && temp_2->column != y ) {
	    temp_1 = temp_2;
	    temp_2 = temp_2->right;
    } 
    if( temp_2 != aux && temp_2->column == y ){
        temp_2->info = elem;
    } else {
        Matrix* new_node = ( Matrix* )malloc( sizeof( Matrix ) );
        new_node->line = x;
        new_node->column = y;
        new_node->info = elem;
        new_node->right = temp_2;
        temp_1->right = new_node;
    }
}

#endif /*MATRIX_H*/
