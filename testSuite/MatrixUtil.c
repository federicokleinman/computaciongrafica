#include "CuTest.h"
#include "../practico_0/Matrix.h"


void TestMatrixNew(CuTest *tc) {

    // Prueba de multiplicacion de matrices
    Matrix* pMatrixA = matrix_new(3,3);
    Matrix* pMatrixB = matrix_new(3,3);
    Matrix* pMatrixC = matrix_new(3,3);

    matrix_set_elem(pMatrixA,0,0,2);
    matrix_set_elem(pMatrixA,0,1,0);
    matrix_set_elem(pMatrixA,0,2,1);
    matrix_set_elem(pMatrixA,1,0,3);
    matrix_set_elem(pMatrixA,1,1,0);
    matrix_set_elem(pMatrixA,1,2,0);
    matrix_set_elem(pMatrixA,2,0,5);
    matrix_set_elem(pMatrixA,2,1,1);
    matrix_set_elem(pMatrixA,2,2,1);


    matrix_set_elem(pMatrixB,0,0,1);
    matrix_set_elem(pMatrixB,0,1,0);
    matrix_set_elem(pMatrixB,0,2,1);
    matrix_set_elem(pMatrixB,1,0,1);
    matrix_set_elem(pMatrixB,1,1,2);
    matrix_set_elem(pMatrixB,1,2,1);
    matrix_set_elem(pMatrixB,2,0,1);
    matrix_set_elem(pMatrixB,2,1,1);
    matrix_set_elem(pMatrixB,2,2,0);

    matrix_mult(pMatrixA,pMatrixB, pMatrixC);
    matrix_toString(pMatrixC);

//    char* input = strdup("hello world");

//    char* actual = StrToUpper(input);
//    char* expected = "HELLO WORLD";

    CuAssert(tc, 10, matrix_get_elem(pMatrixC,0,0));

    matrix_free(pMatrixA);
    matrix_free(pMatrixB);
    matrix_free(pMatrixC);
}



CuSuite* MatrixUtilGetSuite() {
    CuSuite* suite = CuSuiteNew();
    SUITE_ADD_TEST(suite, TestMatrixNew);
    return suite;
}