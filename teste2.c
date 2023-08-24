#include "matrix.h"

Matrix* matrix_create_r( unsigned int m) {
    Matrix* matrix = ( Matrix* ) malloc ( sizeof( Matrix ) );
    matrix->line = -1;
    matrix->column = -1;
    matrix->right = matrix;
    matrix->below = matrix;

    matrix_heads( matrix, m, m );

    for( int i = 1; i <= m; i++ ) {
        for( int j = 1; j <= m; i++ ) {
            float value = rand();
            matrix_setelem( matrix, i, j, value );
        }
    }
    return matrix;
}

int main() {
    unsigned int m = 10000;
    Matrix* A = matrix_create_r( m );
    matrix_print( A );
    Matrix* B = matrix_create_r( m );
    matrix_print( B );
    Matrix* C = matrix_multiply( A, B );
    matrix_print( C );
    matrix_destroy( A );
    matrix_destroy( B );
    matrix_destroy( C );
    return 0;

}