#include <stdio.h>
#include "CuTest.h"
#include "../practico_0/Matrix.h"
#include "../practico_0/Matrix4x4.h"


void TestMatrixNew(CuTest *tc) {

    printf("\nBegin -> TestMatrixNew\n");

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

    CuAssertFloatEquals(tc,3,matrix_get_elem(pMatrixC,0,0));
    CuAssertFloatEquals(tc,1,matrix_get_elem(pMatrixC,0,1));
    CuAssertFloatEquals(tc,2,matrix_get_elem(pMatrixC,0,2));
    CuAssertFloatEquals(tc,3,matrix_get_elem(pMatrixC,1,0));
    CuAssertFloatEquals(tc,0,matrix_get_elem(pMatrixC,1,1));
    CuAssertFloatEquals(tc,3,matrix_get_elem(pMatrixC,1,2));
    CuAssertFloatEquals(tc,7,matrix_get_elem(pMatrixC,2,0));
    CuAssertFloatEquals(tc,3,matrix_get_elem(pMatrixC,2,1));
    CuAssertFloatEquals(tc,6,matrix_get_elem(pMatrixC,2,2));

    matrix_free(pMatrixA);
    matrix_free(pMatrixB);
    matrix_free(pMatrixC);
}

void TestMatrix4x4_1(CuTest *tc) {

    printf("\nBegin -> TestMatrix4x4_1\n");

    // Prueba de multiplicacion de matrices
    Matrix4x4* pMatrixA = matrix4x4_new();
    Matrix4x4* pMatrixB = matrix4x4_new();
    Matrix4x4* pMatrixC = matrix4x4_new();

    matrix4x4_set_elem(pMatrixA,0,0,1);
    matrix4x4_set_elem(pMatrixA,0,1,2);
    matrix4x4_set_elem(pMatrixA,0,2,3);
    matrix4x4_set_elem(pMatrixA,0,3,4);
    matrix4x4_set_elem(pMatrixA,1,0,1);
    matrix4x4_set_elem(pMatrixA,1,1,2);
    matrix4x4_set_elem(pMatrixA,1,2,3);
    matrix4x4_set_elem(pMatrixA,1,3,4);
    matrix4x4_set_elem(pMatrixA,2,0,1);
    matrix4x4_set_elem(pMatrixA,2,1,2);
    matrix4x4_set_elem(pMatrixA,2,2,3);
    matrix4x4_set_elem(pMatrixA,2,3,4);
    matrix4x4_set_elem(pMatrixA,3,0,1);
    matrix4x4_set_elem(pMatrixA,3,1,2);
    matrix4x4_set_elem(pMatrixA,3,2,3);
    matrix4x4_set_elem(pMatrixA,3,3,4);

    matrix4x4_set_elem(pMatrixB,0,0,1);
    matrix4x4_set_elem(pMatrixB,0,1,2);
    matrix4x4_set_elem(pMatrixB,0,2,3);
    matrix4x4_set_elem(pMatrixB,0,3,4);
    matrix4x4_set_elem(pMatrixB,1,0,1);
    matrix4x4_set_elem(pMatrixB,1,1,2);
    matrix4x4_set_elem(pMatrixB,1,2,3);
    matrix4x4_set_elem(pMatrixB,1,3,4);
    matrix4x4_set_elem(pMatrixB,2,0,1);
    matrix4x4_set_elem(pMatrixB,2,1,2);
    matrix4x4_set_elem(pMatrixB,2,2,3);
    matrix4x4_set_elem(pMatrixB,2,3,4);
    matrix4x4_set_elem(pMatrixB,3,0,1);
    matrix4x4_set_elem(pMatrixB,3,1,2);
    matrix4x4_set_elem(pMatrixB,3,2,3);
    matrix4x4_set_elem(pMatrixB,3,3,4);

    matrix4x4_mult(pMatrixA,pMatrixB, pMatrixC);
    matrix4x4_toString(pMatrixA);
    matrix4x4_toString(pMatrixB);
    matrix4x4_toString(pMatrixC);

    CuAssertFloatEquals(tc,10,matrix4x4_get_elem(pMatrixC,0,0));
    CuAssertFloatEquals(tc,20,matrix4x4_get_elem(pMatrixC,0,1));
    CuAssertFloatEquals(tc,30,matrix4x4_get_elem(pMatrixC,0,2));
    CuAssertFloatEquals(tc,40,matrix4x4_get_elem(pMatrixC,0,3));

    CuAssertFloatEquals(tc,10,matrix4x4_get_elem(pMatrixC,1,0));
    CuAssertFloatEquals(tc,20,matrix4x4_get_elem(pMatrixC,1,1));
    CuAssertFloatEquals(tc,30,matrix4x4_get_elem(pMatrixC,1,2));
    CuAssertFloatEquals(tc,40,matrix4x4_get_elem(pMatrixC,1,3));

    CuAssertFloatEquals(tc,10,matrix4x4_get_elem(pMatrixC,2,0));
    CuAssertFloatEquals(tc,20,matrix4x4_get_elem(pMatrixC,2,1));
    CuAssertFloatEquals(tc,30,matrix4x4_get_elem(pMatrixC,2,2));
    CuAssertFloatEquals(tc,40,matrix4x4_get_elem(pMatrixC,2,3));

    CuAssertFloatEquals(tc,10,matrix4x4_get_elem(pMatrixC,3,0));
    CuAssertFloatEquals(tc,20,matrix4x4_get_elem(pMatrixC,3,1));
    CuAssertFloatEquals(tc,30,matrix4x4_get_elem(pMatrixC,3,2));
    CuAssertFloatEquals(tc,40,matrix4x4_get_elem(pMatrixC,3,3));

    matrix4x4_free(pMatrixA);
    matrix4x4_free(pMatrixB);
    matrix4x4_free(pMatrixC);
}

void TestMatrix4x4_2(CuTest *tc) {
    printf("\nBegin -> TestMatrix4x4_2, Identity\n");

    // Prueba de multiplicacion de matrices
    Matrix4x4* pMatrixA = matrix4x4_identity();
    matrix4x4_toString(pMatrixA);

    CuAssertFloatEquals(tc,1,matrix4x4_get_elem(pMatrixA,0,0));
    CuAssertFloatEquals(tc,0,matrix4x4_get_elem(pMatrixA,0,1));
    CuAssertFloatEquals(tc,0,matrix4x4_get_elem(pMatrixA,0,2));
    CuAssertFloatEquals(tc,0,matrix4x4_get_elem(pMatrixA,0,3));
    CuAssertFloatEquals(tc,0,matrix4x4_get_elem(pMatrixA,1,0));
    CuAssertFloatEquals(tc,1,matrix4x4_get_elem(pMatrixA,1,1));
    CuAssertFloatEquals(tc,0,matrix4x4_get_elem(pMatrixA,1,2));
    CuAssertFloatEquals(tc,0,matrix4x4_get_elem(pMatrixA,1,3));
    CuAssertFloatEquals(tc,0,matrix4x4_get_elem(pMatrixA,2,0));
    CuAssertFloatEquals(tc,0,matrix4x4_get_elem(pMatrixA,2,1));
    CuAssertFloatEquals(tc,1,matrix4x4_get_elem(pMatrixA,2,2));
    CuAssertFloatEquals(tc,0,matrix4x4_get_elem(pMatrixA,2,3));
    CuAssertFloatEquals(tc,0,matrix4x4_get_elem(pMatrixA,3,0));
    CuAssertFloatEquals(tc,0,matrix4x4_get_elem(pMatrixA,3,1));
    CuAssertFloatEquals(tc,0,matrix4x4_get_elem(pMatrixA,3,2));
    CuAssertFloatEquals(tc,1,matrix4x4_get_elem(pMatrixA,3,3));

}

CuSuite* MatrixUtilGetSuite() {
    CuSuite* suite = CuSuiteNew();
    SUITE_ADD_TEST(suite, TestMatrixNew);
    SUITE_ADD_TEST(suite, TestMatrix4x4_1);
    SUITE_ADD_TEST(suite, TestMatrix4x4_2);
    return suite;
}