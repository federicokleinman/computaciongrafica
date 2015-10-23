#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "GL/gl.h"
#include "Obj.h"

// globals
FILE *stream;
Obj *gameobject[MAX_GAME_OBJECTS];
int numobjects = 0,objectsInFile = 0;

void obj_CountObjects()
{
    char s[100];
    char objectname[100];
    char *tok;

    objectsInFile = 0;
    while ((fgets(s,100,stream)) != NULL)
    {
        if (s[0] == 'g')
        {
            if (strlen(s) > 2) {
                tok = strtok(s," ");
                tok = strtok(NULL," ");
                if (strcmp(objectname,tok) != 0){
                    strcpy(objectname,tok);
                    objectname[strlen(tok)-1] = 0;
                    objectsInFile++;
                }
            }
        }
    }
    if (objectsInFile == 0)
        objectsInFile = 1;
    numobjects += objectsInFile;
}

int ObjFileQue(int whichobject,char whatdata)
{
    char s[100],objectname[100];
    char *tok;
    int numobj = 0;
    int linecount = 0,i;

    rewind(stream);
    while ((fgets(s,100,stream)) != NULL)
    {
        linecount++;
        if (s[0] == 'g' || objectsInFile == 1)
        {
            if (strlen(s) > 2)
            {
                tok = strtok(s," ");
                tok = strtok(NULL," ");
                if (strcmp(objectname,tok) != 0 || objectsInFile == 1)
                {
                    strcpy(objectname,tok);
                    objectname[strlen(tok)-1] = 0;
                    numobj++;
                    if ((numobj-1) == whichobject)
                    {
                        if (objectsInFile == 1)
                        {
                            rewind(stream);
                            linecount = 0;
                        }
                        while ((fgets(s,100,stream)) != NULL)
                        {
                            if (s[0] == whatdata)
                            {
                                rewind(stream);
                                for (i=0;i<linecount;i++)
                                    fgets(s,100,stream);
                                return 1;
                            }
                            linecount++;
                        }
                    }
                }
            }

        }
    }
    return 0;
}

void LoadFaces(int theobject)
{
    char s[100];
    int numsides,vert[4];
    char *tok;
    char temp[100];
    int i,facecount = 0;
    FACE *newface;

    if(ObjFileQue(theobject,'f')){
        while ((fgets(s,100,stream)) != NULL && s[0] == 'f')
        {
            numsides = 4;
            tok = strtok(s," ");
            i = 0;
            while ((tok = strtok(NULL," ")) != NULL)
            {
                strcpy(temp,tok);
                temp[strcspn(temp,"/")] = 0;
                vert[i] = (int)strtol(temp,NULL,10);
                i++;
            }
            newface = (FACE *)malloc(sizeof(FACE));
            gameobject[theobject + (numobjects - objectsInFile)]->faces[facecount] = newface;
            gameobject[theobject + (numobjects - objectsInFile)]->faces[facecount]->numsides = numsides;
            for(i=0;i<4;i++)
                gameobject[theobject + (numobjects - objectsInFile)]->faces[facecount]->vert[i] = vert[i];
            facecount++;
        }
        gameobject[theobject + (numobjects - objectsInFile)]->numfaces = facecount;
    }
}

void LoadVertices(int theobject)
{
    char s[100];
    char *tok;
    char temp[100];
    float coor[3];
    int vertcount = 0,i;
    VERTEX *newvert;

    if (ObjFileQue(theobject,'v')){
        while ((fgets(s,100,stream)) != NULL && (s[0] == 'v' && s[1] == ' '))
        {
            tok = strtok(s," ");
            for (i=0;i<3;i++)
            {
                tok = strtok(NULL," ");
                strcpy(temp,tok);
                temp[strcspn(temp," ")] = 0;
                coor[i] = (float)atof(temp);
            }
            newvert = (VERTEX *)malloc(sizeof(VERTEX));
            gameobject[theobject + (numobjects - objectsInFile)]->vertices[vertcount] = newvert;
            gameobject[theobject + (numobjects - objectsInFile)]->vertices[vertcount]->x = coor[0];
            gameobject[theobject + (numobjects - objectsInFile)]->vertices[vertcount]->y = coor[1];
            gameobject[theobject + (numobjects - objectsInFile)]->vertices[vertcount]->z = coor[2];
            vertcount++;
        }
        gameobject[theobject + (numobjects - objectsInFile)]->numverts = vertcount;
    }
}

Obj* obj_load(char *filename)
{
    // open and read obj file
    int i;
    Obj *newobject;

    if((stream = fopen( filename, "r+t" )) != NULL )
    {
        obj_CountObjects();
        for (i=numobjects - objectsInFile;i<numobjects;i++)
        {
            newobject = (Obj *)malloc(sizeof(Obj));
            gameobject[i] = newobject;
            LoadFaces(i - (numobjects - objectsInFile));
            LoadVertices(i - (numobjects - objectsInFile));
        }
        fclose( stream );
    }
    return newobject;
}

void obj_render(Obj * obj)
{
    int i;
    glBegin(GL_TRIANGLES);
    for(i=0; i< obj->numfaces; i++) {
        glVertex3f(
                obj->vertices[obj->faces[i]->vert[0] -1]->x,
                obj->vertices[obj->faces[i]->vert[0] -1]->y,
                obj->vertices[obj->faces[i]->vert[0] -1]->z
        );
        glVertex3f(
                obj->vertices[obj->faces[i]->vert[1] -1]->x,
                obj->vertices[obj->faces[i]->vert[1] -1]->y,
                obj->vertices[obj->faces[i]->vert[1] -1]->z
        );
        glVertex3f(
                obj->vertices[obj->faces[i]->vert[2] -1]->x,
                obj->vertices[obj->faces[i]->vert[2] -1]->y,
                obj->vertices[obj->faces[i]->vert[2] -1]->z
        );
    }
    glEnd();
}

void obj_free(Obj * obj) {
    int i;
    for (i=0; i < obj->numfaces; ++i) {
        free(obj->faces[i]);
    }

    for (i = 0; i < obj->numverts; ++i) {
        free(obj->vertices[i]);
    }
    free(obj);
}
