#ifndef COMPGRAFICA_OBJ_H
#define COMPGRAFICA_OBJ_H

#define MAX_GAME_OBJECTS 100
#define MAX_FACES 100000
#define MAX_VERTICES 100000

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
    int numsides;
    int vert[4];
} FACE;

typedef struct
{
    int numfaces;
    int numverts;
    FACE *faces[MAX_FACES];
    VERTEX *vertices[MAX_VERTICES];
} Obj;

Obj* obj_load(char *filename);

void obj_render(Obj * obj);

void obj_free (Obj * obj);

#endif //COMPGRAFICA_OBJ_H