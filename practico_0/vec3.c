#include <stdio.h>
#include <stdlib.h>
#include "vec3.h"

void vec3Init(Vec3* v, float x, float y, float z)
{
    v->x = x;
    v->y = y;
    v->z = z;
}

/**
 * Constuctor
 */
Vec3 vec3Contructor( float x, float y, float z)
{
    Vec3 res;
    res.x = x;
    res.y = y;
    res.z = z;
    return res;
}

/**
 * Constuctor con sus componentes entre 0 y 1.
 */
Vec3 vec3InitRandom()
{
    Vec3 res;
    res.x = (float)rand() / (float)RAND_MAX;
    res.y = (float)rand() / (float)RAND_MAX;
    res.z = (float)rand() / (float)RAND_MAX;
    return res;
}

float add(Vec3 *a, Vec3 *b)
{
    return a->x * b->x + a->y * b->y + a->z * b->z;
}

Vec3 addp(Vec3 *a, Vec3 *b){
    Vec3 res;
    res.x = a->x + b->x;
    res.y = a->y + b->y;
    res.z = a->z + b->z;
    return res;
}

void toString(Vec3* v){
    printf("(a,b,c) = (%.2f,%.2f,%.2f)\n", v->x,v->y,v->z);
}