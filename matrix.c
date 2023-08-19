#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

Matrix* matrix_create( void ) {
    Matrix* matrix = ( Matrix* ) malloc ( sizeof( Matrix ) );

    matrix->line = -1;
    matrix->column = -1;
    matrix->right = matrix;
    matrix->below = matrix;
    //Gerando a cabeça a mais, a primeira de todas

    int m = 0, n = 0, i = 0, j = 0;
    float valor = 0;

    scanf( "%d %d", &m, &n );
    for( int a = 0; a < m; a++ ) {
        matrix_heads_line( matrix, a );
    }

    for( int b = 0; b < n; b++ ) {
        matrix_heads_column( matrix, b );
    }

    do {
        scanf( "%d %d %f", &i, &j, &valor);
        if( valor != 0 ) {
            matrix_setele( matrix, i, j, valor );
        }
    } while( valor != 0 );
}

void matrix_heads_line( Matrix* m, int a ) {
    Matrix* new = ( Matrix* ) malloc ( sizeof( Matrix ) );
    Matrix* aux = m->below;

    while( aux->below != m ) {
        aux = aux->below;
    }
    new->line = a;
    new->column = -1;
    aux->below = new;
    new->below = m;
    new->right = new;
}

void matrix_heads_column( Matrix* m, int a ) {
    Matrix* new = ( Matrix* ) malloc ( sizeof( Matrix ) );
    Matrix* aux = m->right;

    while( aux->right != m ) {
        aux = aux->right;
    }
    new->line = -1;
    new->column = a;
    aux->right = new;
    new->right = m;
    new->below = new;
}

//Pesquisei como percorrer uma matriz encadeada circular
//utilizei a mesma logica para o print
//não sei se é do jeito que imaginavas
void matrix_destroy(Matrix* m) { // tem que testar, mas imagino que ela n deva deixar leak
    if ( m == NULL ) {
        return;
    }
    Matrix* r_head = m;
    Matrix* aux = r_head->below;
    while ( aux != r_head ) {
        Matrix* temp = aux->right;
        while ( temp != aux ) {
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

void matrix_print(Matrix* m) {
    if ( m == NULL ) {
        printf("\nA matriz esta vazia!!");
        return;
    }
    Matrix* r_head = m;
    Matrix* aux = r_head->below;
    while ( aux != r_head ) {
        Matrix* temp = aux->right;
        while ( temp != aux ) {
            if ( temp != aux ) {
                printf("%.2f\t", temp->info);
                temp = temp->right;
            } else {
                printf("%.2f", 0.00);
            }  
        }
        printf("\n");
        aux = aux->below;
    }
}

Matrix* matrix_add(Matrix* m, Matrix* n) {
    if ( m == NULL || n == NULL || m->line != n->line || m->column != n->column ) {
        return NULL;
    } 
  /*struct matrix* right;
	struct matrix* below;
	int line;
	int column;
	float info;
 */

    Matrix* res = matrix_create();
    Matrix* r_head_m = m;
    Matrix* r_head_n = n;
    Matrix* aux_m = r_head_m->below;
    Matrix* aux_n = r_head_n->below;
    while ( aux_m != r_head_m && aux_n != r_head_n ) {
        Matrix* box_m = aux_m->right;
        Matrix* box_n = aux_n->right;
        Matrix* aux_temp = NULL;
        while ( box_m != aux_m || box_n != aux_n ) {
            Matrix* temp = ( Matrix* )malloc( sizeof( Matrix ) );
            temp->line = aux_m->line;
            temp->column = aux_n->column;
            temp->info = aux_m->info + aux_n->info;
            temp->right = temp;
            temp->below = temp;
          
            if ( aux_temp == NULL ) {
                res->right = temp;
            } else {
                aux_temp->right = temp;
            } 
            aux_temp = temp;
        }
        aux_m = aux_m->right;
        aux_n = aux_n->right;
    } 
    return res;
}

Matrix* matrix_multiply( Matrix* m, Matrix* n ) {//m - linha e n - coluna (aux)
    if ( m == NULL || n == NULL || m->column != n->line ) {
        return NULL;
    } 
    Matrix* res = matrix_create();
    Matrix* r_head_m = m;
    Matrix* r_head_n = n;
    Matrix* aux_m = r_head_m->below;
  
    while ( aux_m != r_head_m ) {
        Matrix* aux_n = r_head_n->right;
        while ( aux_n != r_head_n ) {
            float sum = 0.00;
            Matrix* temp_n = aux_n->below;
            Matrix* temp_m = aux_m->right;
            while ( temp_m != aux_m && temp_n != aux_n ) {
           	    if ( temp_m->column != temp_n->line ) {
		    		 printf("\nValores de Colunas(m) e Linhas(n) é incompativel...\n");
			    	 return NULL;
			    } else {
				    sum = temp_m->info * temp_n->info;
				    temp_m = temp_m->right;
				    temp_n = temp_n->below;
			    } 
            } 
		    //void matrix_setelem( Matrix* m, int x, int y, float elem );
		    if ( sum != 0 ) {
			    matrix_setelem( res, aux_m->line, aux_n->column, sum );
		    }   
            aux_n = aux_n->right;
            } 
        aux_m = aux_m->below;
    } 
    return res;
}

Matrix* matrix_transpose( Matrix* m ) {
    if ( m == NULL ) {
        return NULL;
    } 
    Matrix* res = matrix_create();
    Matrix* r_head = m;
    Matrix* aux = r_head->below;
    while ( aux != r_head ) {
	    Matrix* temp = aux->right;
	    while ( temp != aux ) {
		  //void matrix_setelem( Matrix* m, int x(coluna), int y(linha), float elem ); <---- para transposição
		    matrix_setelem( res, aux->column, aux->line, aux->info );
		    temp = temp->right;
	    } 
    }
	return res;
}

float matrix_getelem(Matrix* m, int x, int y) {// retorna o valor da coordenada [x][y]?
    if ( m == NULL || x < 0 || y < 0 ) {
        return 0.00;
    }
    Matrix* r_head = m;
    Matrix* aux = r_head->below;
  	while ( aux != r_head || aux->line != x ) {
	    aux = aux->below;
    } 
 	if ( aux == r_head ) {//Os dois if's são para linhas ou colunas inexistentes -- talvez dê para n colocar nada?
	    return 0.00;
	} 
	Matrix* temp = aux->right;
	while ( temp != aux || temp->column != y ) {
	    temp = temp->right;
	}
	if ( temp == aux ) {
	    return 0.00;
	}
	
    return temp->info;
}

void matrix_setelem(Matrix* m, int x, int y, float elem) {
    if ( m == NULL || x < 0 || y < 0 ) {//Dei uma arrumada aqui a tua logica tava certa mas tu não tinha feito o percurso para chegar na posição que tu queria chegar
	    return;
    }
    Matrix* r_head = m;
    Matrix* aux = r_head->below;
    while ( aux != r_head && aux->line != x ) {
	    aux = aux->below;
    } 
  if( aux == r_head ) {
        return;
    } 
    Matrix* temp_1 = aux;
    Matrix* temp_2 = aux->right;
    while ( temp_2 != aux && temp_2->column != y ) {
	    temp_1 = temp_2;
	    temp_2 = temp_2->right;
    } 
  if(temp_2 != aux && aux->column == y) {
        temp_2->info = elem;
    } else {
        Matrix* new = (Matrix*)malloc(sizeof(Matrix));
        new->line = x;
        new->column = y;
        new->info = elem;
        new->right = temp_2;
        temp_1->right = new;
    }
  //Criando uma caixinha para adicionar o valor, porém também essa área também pode servir apenas
  //para trocar o valor de um nodo já existente.
}
