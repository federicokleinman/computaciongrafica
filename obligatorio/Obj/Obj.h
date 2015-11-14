#ifndef COMPGRAFICA_OBJ_H
#define COMPGRAFICA_OBJ_H

#define MAX_GAME_OBJECTS 10
#define MAX_FACES 1000
#define MAX_VERTICES 1000
#define MAX_NORMALES 1000
#define MAX_TEXTURAS 1000

typedef struct
{
    char filename[2][50];
} FILERECORD;

typedef struct
{
    float x,y,z;
} VERTEX;

typedef struct
{
    float x,y;
} VERTEX2;

typedef struct
{
    int numsides;
    int vert[4];
    int normal[4];
} FACE;

// f 1/1/1 2/2/2 3/3/3, vertice/normal/textura
typedef struct
{
    int vertices[3];
    int normales[3];
    int texturas[3];
} FACE2;

typedef struct
{
    int numfaces;
    int numfaces2;
    int numverts;
    int numNormales;
    int numTexturas;
    FACE *faces[MAX_FACES];
    VERTEX *vertices[MAX_VERTICES];
    VERTEX *normales[MAX_NORMALES];
    VERTEX2 *texturas[MAX_TEXTURAS];
    FACE2 * faces2[MAX_FACES];
} Obj;

Obj* obj_load(char *filename);

void obj_render(Obj * obj);

void obj_render2(Obj * obj);

void obj_free (Obj * obj);

#endif //COMPGRAFICA_OBJ_H


