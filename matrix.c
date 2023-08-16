#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

Matrix* matrix_create( void ) {
/* A ideia inicial era fazer aquela cabeça a mais aqui e colocar as outras a partir
de uma função externa (matrix_help), porém isso parece meio estranho.*/


/*Tem a opção de transformar em um vetor de matrizes e usar o indice para 
facilitar na hora de adicionar elementos, isso também parece estranho*/
  Matrix* matrix = ( Matrix* ) malloc ( sizeof( Matrix ) );

  matrix->line = -1;
  matrix->column = -1;
  matrix->right = matrix;
  matrix->below = matrix;
  //gerando a primeira caixinha

  int m = 0, n = 0, i = 0, j = 0;
  float valor = 0;

  scanf( "%d %d", &m, &n );
  for( int a = 0; a < m; a++ ) {
    matrix_help( matrix, a );
  }

  do {
    scanf( "%d %d %f", &i, &j, &valor);
    if( valor != 0 ) {
    matrix_setele( matrix, i, j, valor );
    }
  } while( valor != 0 || valor != '.' );
}

void matrix_help( Matrix* m, int a ) {
  //fiz na ideia de criar as outras caixas, olhando melhor parece meio exagerada.
  Matrix* new_right = ( Matrix* ) malloc ( sizeof( Matrix ) );
  Matrix* new_below = ( Matrix* ) malloc ( sizeof( Matrix ) );

  new_right->line = -1;
  m->below = new_right;
  new_right->below = m;

  new_below->column = -1;
  m->line = new_below;
  new_below = m;

  free( new_right );
  free( new_below );

  
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
                  free(temp);
                  temp = temp_2;
          }
          Matrix* r_next = aux->below;
          free(aux);
          aux = r_next;
  }
  
 free(m); 
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
          int column = 0;
          while ( temp != aux || column <= m->column ) {
                  if ( temp != aux && temp->column == column ) {
                      printf("%.2f", temp->info);
                      temp = temp->right;
                  } else {
                      printf("%.2f", 0.00);
                      column++;
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
  Matrix* res = matrix_create();
  Matrix* r_head_m = m;
  Matrix* r_head_n = n;
  Matrix* aux_m = r_head_m->below;
  Matrix* aux_n = r_head_n->below;
  
}

Matrix* matrix_multiply(Matrix* m, Matrix* n) {

}

Matrix* matrix_transpose(Matrix* m) {

}

float matrix_getelem(Matrix* m, int x, int y) {

}

void matrix_setelem(Matrix* m, int x, int y, float elem) {
  Matrix* new = ( Matrix* ) malloc ( sizeof( Matrix ) );
  
  new->line = x;
  new->column = y;
  new->info = elem;

  //Criando uma caixinha para adicionar o valor, porém também essa área também pode servir apenas
  //para trocar o valor de um nodo já existente.
}
