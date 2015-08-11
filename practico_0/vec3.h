#ifndef COMPGRAFICA_VEC3_H
#define COMPGRAFICA_VEC3_H

typedef struct
{
    float x, y, z;
} Vec3;

Vec3 vec3InitRandom();

Vec3 vec3InitHomotecia(int a, int b);

Vec3 vec3Contructor( float x, float y, float z);

Vec3 addp(Vec3 *a, Vec3 *b);

float add(Vec3 *a, Vec3 *b);

void vec3Init(Vec3* v, float x, float y, float z);

void toString(Vec3* v);

#endif //COMPGRAFICA_VEC3_H
