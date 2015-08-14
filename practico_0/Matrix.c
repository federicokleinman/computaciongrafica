#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"

// printf("[%d] [%d] => [%f]\n", 0,0, pMatrix.array[0][0]);

Matrix* matrix_new(int n, int m) {

    Matrix* pMatrix = (Matrix*) malloc(sizeof(Matrix));
    pMatrix->filas = n;
    pMatrix->columnas = m;
    pMatrix->array = (float**) malloc(n* sizeof(float*));
    int i,j;
    for (i=0;i<n;i++) {
        pMatrix->array[i] = (float *) malloc(m * sizeof(float));
    }
    for (i = 0; i < n; ++i)
    {
        for (j = 0; j < m; ++j){
            matrix_set_elem(pMatrix,i,j,0);
        }
    }
    return pMatrix;
}

Matrix* matrix_identity(int n, int m) {

    Matrix * pMatrix = matrix_new(n,m);
    int i,j;
    for (i = 0; i < n; ++i)
    {
        for (j = 0; j < m; ++j){
            if(i==j)
                matrix_set_elem(pMatrix,i,j,1);
        }
    }
    return pMatrix;
}

void matrix_free(Matrix *pMatrix) {
    int i;
    for (i=0; i < pMatrix->filas; i++) {
        free(pMatrix->array[i]);
    }
    free(pMatrix->array);
    free(pMatrix);
}


float matrix_get_elem(Matrix *m, int r, int c) {

    if (r < m->filas && c < m->columnas) {
        return m->array[r][c];
    }
    else {
        perror("matrix_get_elem -> Indice fuera de rango");
        return -1;
    }
}

void matrix_set_elem(Matrix *m, int r, int c, float val) {

    if (r < m->filas && c < m->columnas) {
        m->array[r][c] = val;
    }
    else {
        perror("matrix_set_elem -> Indice fuera de rango");
    }
}

void matrix_mult(Matrix *a, Matrix *b, Matrix *c) {
    if(a->columnas != b->filas) {
        perror("No se puede multiplicar la matrices, columnas(a) != filas(b)");
    } else {

        int i,j,k;
        for(i=0; i < a->filas; i++){
            for(j=0; j < b->columnas; j++){
                c->array[i][j] = 0;
                for(k=0; k < a->columnas; k++){
                    c->array[i][j] = (c->array[i][j] + (a->array[i][k] * b->array[k][j]));
                }
            }
        }
    }
}

float matrix_get_filas(Matrix *m) {
    return m->filas;
}

float matrix_get_columnas(Matrix *m) {
    return m->columnas;
}

void matrix_toString(Matrix *m)
{
    int i, j;

    printf("\n");
    for (i = 0; i < m->filas; ++i)
    {
        for (j = 0; j < m->columnas; ++j) {
            printf("%4f ", matrix_get_elem(m, i, j));
        }
        printf("\n");
    }
}
