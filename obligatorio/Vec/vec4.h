#ifndef COMPGRAFICA_VEC4_H
#define COMPGRAFICA_VEC4_H

typedef struct
{
    float x, y, z, w;
} Vec4;

Vec4 vec4InitRandom();

Vec4 vec4InitHomotecia(int a, int b);

Vec4 * vec4Contructor( float x, float y, float z, float w);

Vec4 addp(Vec4 *a, Vec4 *b);

float add(Vec4 *a, Vec4 *b);

void vec4Init(Vec4* v, float x, float y, float z, float w);

void toString(Vec4* v);

#endif
