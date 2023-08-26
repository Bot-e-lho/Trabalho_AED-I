#ifndef MATRIX_H
#define MATRIX_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct matrix {
    int line;
    int column;
    float info;
    struct matrix* right;
    struct matrix* below;
}Matrix;

Matrix* matrix_create( void );
//Matrix* matrix_create( unsigned int m );
void matrix_heads( Matrix* m, int l, int c );
void matrix_destroy( Matrix* m );
void matrix_print( Matrix* m );
Matrix* matrix_create_with_values( int m, int n, float** values );
Matrix* matrix_add( Matrix* m, Matrix* n );
Matrix* matrix_multiply( Matrix* m, Matrix* n );
Matrix* matrix_normal_multiply( Matrix* m, Matrix* n );
Matrix* matrix_transpose( Matrix* m );
float matrix_getelem( Matrix* m, int x, int y );
void matrix_setelem( Matrix* m, int x, int y, float elem );

Matrix* matrix_create( void ) {
    Matrix* matrix = ( Matrix* ) malloc ( sizeof ( Matrix ) );
    matrix->line = -1;
    matrix->column = -1;
    matrix->right = matrix;
    matrix->below = matrix;

    int m = 0, n = 0;
    printf( "\nInforme o tamanho da matrix (linha x coluna):\n" );
    scanf( "%d %d", &m, &n );
    if( m <= 0 || n <= 0 ) {
        printf( "Quantidade de colunas e linhas incompativel.\n" );
        exit( 1 );
    }
    matrix_heads( matrix, m, n );

    printf( "\nInforme a coordenada(x,y) e o seu valor:\n" );
    while( 1 ) {
        int i = 1, j = 1;
        float valor = 0.0;
        scanf( "%d %d %f", &i, &j, &valor );
        char esc = getchar();
        if( esc == '0' || esc == '.' ) {
            break;
        }
        if( i >= 1 && i <= m && j >= 1 && j <= n ) {
            matrix_setelem( matrix, i, j, valor );
        } else {
            printf( "Posicao invalida\n" );
        }
    }
    return matrix;
}

//Matrix* matrix_create( unsigned int m ) {
 //   srand( ( float ) time ( NULL ) );
   // Matrix* matrix = ( Matrix* ) malloc ( sizeof ( Matrix ) );
   // matrix->line = -1;
    //matrix->column = -1;
    //matrix->right = matrix;
    //matrix->below = matrix;
    //matrix_heads( matrix, m, m ); // mxm

//    for( int i = 0; i < m; i++ ) {
  //      for( int j = 0; j < m; j++ ) {
    //            float valor = ( ( float ) rand() / RAND_MAX *  1000.00 ) - 500.00; 
      //            if ( valor > 0.3 ) {
        //              matrix_setelem(matrix, i, j, valor);
          //        }
      //   
       // }
   // }
    //return matrix;
//}

void matrix_heads( Matrix* m, int l, int c ) {
    for( int i = 1; i <= l; i++ ) {
        Matrix* new_node = ( Matrix* ) malloc ( sizeof ( Matrix ) );
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
    
    for( int i = 1; i <= c; i++ ) {
        Matrix* new_node = ( Matrix* ) malloc ( sizeof ( Matrix ) );
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

void matrix_destroy( Matrix* m ) {
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

    aux = r_head->right;
    while( aux != r_head ) {
       Matrix* r_next = aux->right;
       free( aux );
       aux = r_next;
    }
    free( m );
}

void matrix_print( Matrix* m ) {
    if ( m == NULL ) {
        printf( "\nEsta vazia\n" );
        return;
    }
    Matrix* fill = m->right;
    while( fill->right != m ) {
        fill = fill->right;
    }
    printf( "\n" );

    Matrix* r_head = m;
    Matrix* aux_r = r_head->below;
    while( aux_r != r_head ) {
        Matrix* aux_col = aux_r->right;
        
        for( int i = 1; i <= test->column; i++ ) {
            if( aux_col != NULL && aux_col->column == i ) {
                printf( "%.2f\t", aux_col->info );
                aux_col = aux_col->right;
            } else {
                printf( "%.2f\t", 0.00 );
            }
        }
        printf( "\n" );
        aux_r = aux_r->below;
    }
}

Matrix* matrix_create_with_values( int m, int n, float** values ) {
    Matrix* matrix = ( Matrix* ) malloc ( sizeof ( Matrix ) );
    matrix->line = m;
    matrix->column = n;
    matrix->right = matrix;
    matrix->below = matrix;

    matrix_heads( matrix, m, n );

    for( int i = 0; i < m; i++ ) {
        for( int j = 0; j < n; j++ ) {
            float valor = values[i][j];
            matrix_setelem( matrix, i + 1, j + 1, valor );
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
    int row = aux->line;
    aux = m->right;
    while( aux->right != m ) {
        aux = aux->right;
    }
    int col = aux->column;

    float** res = ( float** ) malloc ( row * sizeof ( float* ) );
    for( int i = 0; i < row; i++ ) {
        res[i] = ( float* ) malloc ( col * sizeof ( float ) );
        for( int j = 0; j < col; j++ ) {
            res[i][j] = matrix_getelem( m, i + 1, j + 1 ) + matrix_getelem( n, i + 1, j + 1 );
        }
    }

    Matrix* matrix = matrix_create_with_values( row, col, res );
    for( int i = 0; i < row; i++ ) {
        free( res[i] );
    }

    free( res );
    return matrix;
}

Matrix* matrix_multiply( Matrix* m, Matrix* n ) {
    if( m == NULL || n == NULL || m->column != n->line ) {
        return NULL;
    }

    Matrix* aux = m->below;
    while( aux->below != m ) {
        aux = aux->below;
    }
    int line = aux->line;
    aux = m->right;
    while( aux->right != m ) {
        aux = aux->right;
    }
    int m_column = aux->column;

    aux = n->right;
    while( aux->right != n ) {
        aux = aux->right;
    }
    int n_column = aux->column;

    float** res = ( float** ) malloc ( line * sizeof( float* ) );
    for( int i = 0; i < line; i++ ) {
        res[i] = ( float* )malloc( n_column * sizeof( float ) );
        for( int j = 0; j < n_column; j++ ) {
            float value = 0.0;
            for (int k = 0; k < m_column; k++) {
                value += matrix_getelem( m, i + 1, k + 1 ) * matrix_getelem( n, k + 1, j + 1 );
            }
            res[i][j] = value;
        }
    }

    Matrix* matrix = matrix_create_with_values(line, n_column, res);

    for( int i = 0; i < line; i++ ) {
        free( res[i] );
    }
    free( res );

    return matrix;
}


//Matrix* matrix_normal_multiply( Matrix* m, Matrix* n ) {
 //   if( m == NULL || n == NULL || m->column != n->line ) {
 //       printf( "Quantidade de colunas e linhas incompativel.\n" );
 //       return NULL;
 //   }

 //   int row_m = m->line;
 //   int col_m = m->column;
 //   int col_n = n->column;

 //   float** res = ( float** ) malloc ( row_m * sizeof ( float* ) );

 //   for( int i = 0; i < row_m; i++ ) {
 //       res[i] = ( float* )malloc( col_n * sizeof ( float ) );
 //       for( int j = 0; j < col_n; j++ ) {
 //           float value = 0.00;
 //           for (int k = 0; k < col_m; k++) {
//              value += matrix_getelem( m, i, k ) * matrix_getelem( n, k, j );
//            }
  //          res[i][j] = value;
     //   }
   // }
   // Matrix* result = matrix_create_with_values(row_m, col_n, res);
   // for (int i = 0; i < row_m; i++) {
   //     free(res[i]);
   // }
   // free(res);

   // return result;
//}

Matrix* matrix_transpose( Matrix* m ) {
    if( m == NULL ) {
        return NULL;
    }

    Matrix* aux = m->below;
    while( aux->below != m ) {
        aux = aux->below;
    }
    int line = aux->line;
    aux = m->right;
    while( aux->right != m ) {
        aux = aux->right;
    }
    int column = aux->column;

    float** res = ( float** ) malloc ( line * sizeof( float* ) );
    for( int i = 0; i < line; i++ ) {
        res[i] = ( float* ) malloc ( column* sizeof( float ) );
        for( int j = 0; j < column; j++ ) {
            res[i][j] = matrix_getelem( m, j + 1, i + 1 );
        }
    }

    Matrix* matrix = matrix_create_with_values(line, column, res);
    for( int i = 0; i < line; i++ ) {
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
  	while( aux != r_head && aux->line != x ) {
        aux = aux->below;
    } 
 	if( aux == r_head ) {
	    return 0.0; 
	} 
	Matrix* temp = aux->right;
	while( temp != aux && temp->column != y ) {
        temp = temp->right;
	}
	if( temp == aux ) {
	    return 0.0; 
	}
    return temp->info;
}

void matrix_setelem( Matrix* m, int x, int y, float elem ) {
    if( m == NULL || x < 0 || y < 0 ) {
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
        Matrix* new_node = ( Matrix* ) malloc ( sizeof ( Matrix ) );
        new_node->line = x;
        new_node->column = y;
        new_node->info = elem;
        new_node->right = temp_2;
        temp_1->right = new_node;
        aux = r_head->right;

        while( aux != r_head && aux->column != y ) {
	        aux = aux->right;
        }
        Matrix* aux_1 = aux;
        Matrix* aux_2 = aux->below;
        while( aux_2 != aux && aux_2->line != x ) {
	        aux_1 = aux_2;
	        aux_2 = aux_2->below;
        }
        new_node->below = aux_2;
        aux_1->below = new_node;
    }
}
#endif /*MATRIX_H*/
