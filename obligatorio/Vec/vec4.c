#include <stdio.h>
#include <stdlib.h>
#include "vec4.h"

void vec4Init(Vec4* v, float x, float y, float z, float w)
{
    v->x = x;
    v->y = y;
    v->z = z;
    v->w = w;
}

/**
 * Constuctor
 */
Vec4 * vec4Contructor( float x, float y, float z, float w)
{
    Vec4 res;
    res.x = x;
    res.y = y;
    res.z = z;
    res.w = w;
    return & res;
}

/**
 * Constuctor con sus componentes entre 0 y 1.
 */
Vec4 vec4InitRandom()
{
    Vec4 res;
    res.x = (float)rand() / (float)RAND_MAX;
    res.y = (float)rand() / (float)RAND_MAX;
    res.z = (float)rand() / (float)RAND_MAX;
    res.w = (float)rand() / (float)RAND_MAX;
    return res;
}

/**
 * Si x es un número aleatorio perteneciente al intervalo [0,1],
 * entonces puedo definir un número aleatorio perteneciente al intervalo [a,b] como:
 * x ->    r = a + (b-a)*x
 */
Vec4 vec4InitHomotecia(int a, int b)
{
    Vec4 res;
    res.x = a +(float)(((b - a +1.0)*rand())/(RAND_MAX+1.0));
    res.y = a +(float)(((b - a +1.0)*rand())/(RAND_MAX+1.0));
    res.z = a +(float)(((b - a +1.0)*rand())/(RAND_MAX+1.0));
    res.w = a +(float)(((b - a +1.0)*rand())/(RAND_MAX+1.0));
    return res;
}

float add(Vec4 *a, Vec4 *b)
{
    return a->x * b->x + a->y * b->y + a->z * b->z + a->w * b->w ;
}

Vec4 addp(Vec4 *a, Vec4 *b){
    Vec4 res;
    res.x = a->x + b->x;
    res.y = a->y + b->y;
    res.z = a->z + b->z;
    res.w = a->w + b->w;
    return res;
}

void toString(Vec4* v){
    printf("(a,b,c,w) = (%.2f,%.2f,%.2f,%.2f)\n", v->x,v->y,v->z,v->w);
}
