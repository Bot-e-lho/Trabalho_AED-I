#include "matrix.h"
/*int main( void ) {
// Inicializacao da aplicacao ... 
Matrix *A = matrix_create();
matrix_print( A );
Matrix *B = matrix_create(); 
matrix_print( B );
Matrix *C = matrix_add( A, B ); 
matrix_print( C );
matrix_destroy( C );
C = matrix_multiply( A, B ); 
matrix_print( C );
matrix_destroy( C );
C = matrix_transpose( A ); 
matrix_print( C );
matrix_destroy( C );
matrix_destroy( A );
matrix_destroy( B );
return 0;
}
*/

// ------------ Teste 2 -----------------
// ------------  Main -------------------

int main( void ) {
    unsigned int size = 1850;
    Matrix* matrix = matrix_create( size );
    Matrix* matrix_transposed = matrix_transpose( matrix );

    printf( "Matriz:\n" );
    matrix_print( matrix );

    printf( "\nTransposicao:\n" );
    matrix_print( matrix_transposed );
    matrix_destroy( matrix );
    matrix_destroy( matrix_transposed );

    return 0;
}


