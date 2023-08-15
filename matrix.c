#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

Matrix* matrix_create(void) {
  
}
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
                  
          }
          Matrix* r_next = aux->below;
          aux = r_next;
  }
}

Matrix* matrix_add(Matrix* m, Matrix* n) {
  
}

Matrix* matrix_multiply(Matrix* m, Matrix* n) {

}

Matrix* matrix_transpose(Matrix* m) {

}

float matrix_getelem(Matrix* m, int x, int y) {

}

void matrix_setelem(Matrix* m, int x, int y, float elem) {

}
