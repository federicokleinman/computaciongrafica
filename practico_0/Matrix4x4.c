#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "Matrix4x4.h"


Matrix4x4 *matrix4x4_new() {
    Matrix4x4* pMatrix = (Matrix4x4*) malloc(sizeof(Matrix4x4));
    pMatrix->array = (float*) malloc(16* sizeof(float*));
    int i,j;
    for (i = 0; i < 4; ++i)
    {
        for (j = 0; j < 4; ++j){
            matrix4x4_set_elem(pMatrix,i,j,0);
        }
    }
    return pMatrix;
}

Matrix4x4 *matrix4x4_identity() {
    Matrix4x4* pMatrix = matrix4x4_new();

    int i,j;
    for (i = 0; i < 4; ++i)
    {
        for (j = 0; j < 4; ++j){
            if(i==j)
                matrix4x4_set_elem(pMatrix,i,j,1);
        }
    }

    return pMatrix;
}

void matrix4x4_free(Matrix4x4 *pMatrix) {
    free(pMatrix->array);
    free(pMatrix);
}

void matrix4x4_toString(Matrix4x4 *m) {
    int i, j;

    printf("\n");
    for (i = 0; i < 4; ++i)
    {
        for (j = 0; j < 4; ++j) {
            printf("%4f ", matrix4x4_get_elem(m, i, j));
        }
        printf("\n");
    }

}

float matrix4x4_get_elem(Matrix4x4 *m, int r, int c) {
    if (r < 4 && c < 4) {
        return m->array[r*4 + c];
    }
    else {
        perror("matrix_get_elem -> Indice fuera de rango");
        return -1;
    }
}

void matrix4x4_set_elem(Matrix4x4 *m, int r, int c, float val) {

    if (r < 4 && c < 4) {
        m->array[r*4 + c] = val;
    }
    else {
        perror("matrix_set_elem -> Indice fuera de rango");
    }
}

void matrix4x4_mult(Matrix4x4 *a, Matrix4x4 *b, Matrix4x4 *c) {
    int i,j,k;
    for(i=0; i < 4; i++){
        for(j=0; j < 4; j++){
            c->array[i*4 + j] = 0;
            for(k=0; k < 4; k++){
                c->array[i*4 +j] = (c->array[i*4 +j] + (a->array[i*4 +k] * b->array[k*4 +j]));
            }
        }
    }
}
