#include <syntax_errors/matrix.h>

int main()
{
    Matrix mat1( 2, 2 );
    Matrix mat2( 2, 2 );

    mat1( 0, 0 ) = 0;
    mat1( 0, 1 ) = 1;
    mat1( 1, 0 ) = 2;
    mat1( 1, 1 ) = 3;

    mat2( 0, 0 ) = 4;
    mat2( 0, 1 ) = 5;
    mat2( 1, 0 ) = 6;
    mat2( 1, 1 ) = 7;

    Matrix mat3 = mat1 + mat2;

    mat2 += mat1;

    Matrix mat4 = mat3 + mat2;

    return 0;
}
