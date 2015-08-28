#ifndef COMPGRAFICA_MATRIX4X4_H
#define COMPGRAFICA_MATRIX4X4_H

typedef struct
{
    float *array;
} Matrix4x4;

/**
 * - Crea una matriz de dimensiones NXM
 */
Matrix4x4* matrix4x4_new();

/**
 * Crea una matriz de dimensiones NXM inicializada en la Identidad.
 */
Matrix4x4* matrix4x4_identity();

/**
 * Destruye la matrix
 */
void matrix4x4_free(Matrix4x4 *pMatrix);

/**
 * Imprime la matrix
 */
void matrix4x4_toString(Matrix4x4 *m);

/**
 * Devuelve el elemento almacenado en m[r, c]si y solo si r y c son indices válidos dentro de m.
 * */
float matrix4x4_get_elem(Matrix4x4* m, int r, int c);

/**
 * Asigna m[r, c] = val si y solo si r y c son indices válidos dentro de m.
 */
void matrix4x4_set_elem(Matrix4x4* m, int r, int c, float val) ;

/**
 *  - Asigna c = aXb.
 */
void matrix4x4_mult(Matrix4x4* a, Matrix4x4* b, Matrix4x4* c);


#endif //COMPGRAFICA_MATRIX4X4_H
