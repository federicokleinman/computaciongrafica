#ifndef PARSER_H
#define PARSER_H

#include "Vec3.h"
#include "framework/color.h"

typedef enum CG_LightType {
    CG_POINT, CG_DIRECT
} CG_LightType;

typedef struct CG_Light {
    CG_LightType type;
    Vec3 pos;
    float intens;
    struct CG_Light* next;
} CG_Light;

typedef struct CG_Material {
    Color cd; //Color difuso
    Color cs; //Color especular
    float coef_espec; //Coeficiente especular
    float coef_refl; //Coeficiente reflectivo
} CG_Material;

typedef struct CG_Sphere {
    Vec3 pos;
    float radius;
    CG_Material material;
    struct CG_Sphere* next;
} CG_Sphere;


typedef struct {
    Vec3 cam;
    Vec3 cam_view;
    Vec3 cam_up;
    float dist;
    float vh;
    float vw;
    float intAmbient;

    CG_Light* pLight;
    CG_Sphere* pSphere;
} Escena;

Escena escena;

void cg_parse_conf(char* scene_file);
#endif
