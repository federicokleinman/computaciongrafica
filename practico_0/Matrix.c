#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"

Matrix pMatrix;

Matrix* matrix_new(int n, int m) {

    int i;
    pMatrix.filas= (int*) malloc(sizeof(int));
    pMatrix.columnas=(int*) malloc(sizeof(int));

    *(pMatrix.filas) = n;
    *(pMatrix.columnas)= m;

    pMatrix.array = (float**) malloc(n* sizeof(float*));
    for (i=0;i<n;i++)
       pMatrix.array[i] = (float*)malloc(m*sizeof(float));


    // printf("[%d] [%d] => [%f]\n", 0,0, pMatrix.array[0][0]);

    return &pMatrix;
}

Matrix* matrix_identity(int n, int m) {

    Matrix * mIdentity = matrix_new(n,m);
    int i,j;

    for (i = 0; i < n; ++i)
    {
        for (j = 0; j < m; ++j){
            if(i==j)
                matrix_set_elem(mIdentity,i,j,1);
            else
                matrix_set_elem(mIdentity,i,j,0);
        }
    }
}

float matrix_get_elem(Matrix *m, int r, int c) {

    if (r < matrix_get_filas(m) && c < matrix_get_columnas(m))
        return m->array[r][c];
    else {
        perror("Indice fuera de rango");
        return -1;
    }
}

void matrix_set_elem(Matrix *m, int r, int c, float val) {

    if (r < matrix_get_filas(m) && c < matrix_get_columnas(m))
        m->array[r][c] = val;
    else {
        perror("Indice fuera de rango");
    }
}

float matrix_get_filas(Matrix *m) {
    return *(m->filas);
}

float matrix_get_columnas(Matrix *m) {
    return *(m->columnas);
}

void matrix_toString(Matrix *m)
{
    int i, j;

    for (i = 0; i < *(m->filas); ++i)
    {
        for (j = 0; j < *(m->columnas); ++j)
            printf("%4f ", matrix_get_elem(m,i,j));
        printf("\n");
    }
}
