#ifndef COMPGRAFICA_MATRIX_H
#define COMPGRAFICA_MATRIX_H

typedef struct
{
    float **array;
    int filas;
    int columnas;
} Matrix;

//* (a) Matrix* matrix_new(int n, int m) - Crea una matriz de dimensiones NXM
//* (b) Matrix* matrix_identity(int n, int m) - Crea una matriz de dimensiones NXM inicializada en la Identidad.
//* (c) float matrix_get_elem(Matrix* m, int r, int c) - Devuelve el elemento almacenado en m[r, c]si y solo si r y c son indices válidos dentro de m.
//* (d) void matrix_set elem(Matrix* m, int r, int c, float val) - Asigna m[r, c] = val si y solo si r y c son indices válidos dentro de m.
//* (e) void matrix_mult(Matrix* a, Matrix* b, Matrix* c) - Asigna c = aXb.
//* (f) void matrix_free(Matrix* m) - Elimina una matriz, liberando sus recursos.

/**
 * - Crea una matriz de dimensiones NXM
 */
Matrix* matrix_new(int n, int m);

/**
 * Crea una matriz de dimensiones NXM inicializada en la Identidad.
 */
Matrix* matrix_identity(int n, int m);

/**
 * Destruye la matrix
 */
void matrix_free(Matrix *pMatrix);

/**
 * Imprime la matrix
 */
void matrix_toString(Matrix *m);

/**
 * Retorna las filas de una matrix
 */
float matrix_get_filas(Matrix *m);

/**
 * Retorna las columnas de una matrix
 */
float matrix_get_columnas(Matrix *m);

/**
 * Devuelve el elemento almacenado en m[r, c]si y solo si r y c son indices válidos dentro de m.
 * */
float matrix_get_elem(Matrix* m, int r, int c);

/**
 * Asigna m[r, c] = val si y solo si r y c son indices válidos dentro de m.
 */
void matrix_set_elem(Matrix* m, int r, int c, float val) ;

/**
 *  - Asigna c = aXb.
 */
void matrix_mult(Matrix* a, Matrix* b, Matrix* c);


#endif //COMPGRAFICA_MATRIX_H
