#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "vec3.h"

#define printSizeof(a, type) ({ \
    printf("The number of bytes in a %s is %zu.\n", a, sizeof(type)); \
})

void ej1();
void ej2();
void ej3();
void ej4();
void ej5();
void ej6(const char * path);
void ej7();
void ej8();
void ej10();

/*

https://en.wikipedia.org/wiki/C_data_types

1. Desarrollar un programa C que imprime en la Terminal el largo en bytes de los siguientes tipos de
datos: char, int, long, long long, float, double, long double, char*, int*, float*, void*. Sugerencia:
utilizar el operador sizeof.
*/
void ej1(){
    printSizeof("char", char);
    printSizeof("int", int);
    printSizeof("long", long);
    printSizeof("long long", long long);
    printSizeof("float", float);
    printSizeof("long double", long double);

    printSizeof("char*", char*);
    printSizeof("int*", int*);
    printSizeof("long*", long*);
    printSizeof("float*", float*);
    printSizeof("void*", void*);
}

/*
2. Desarrollar un programa C que crea un array de 100 elementos, almacena en cada posición su
´ındice correspondiente y lo imprime en la Terminal.
*/
void ej2(){

    int arreglo[100],i;

    for(i=0; i <100; i++){
        arreglo[i] = i;
    }

    for(i=0; i <100; i++){
        printf("%7d%13d\n", i, arreglo[i]);
    }

}

/*
3. Desarrollar un programa C que crea un array de 100 elementos, lo llena con números aleatorios
y lo imprime en la Terminal.
*/
void ej3(){

    int arreglo[100],i;
    srand(time(NULL));

    for(i=0; i <100; i++){
        arreglo[i] = rand();
    }

    for(i=0; i <100; i++){
        printf("%7d%13d\n", i, arreglo[i]);
    }

}

/*
4. Desarrollar un programa C que crea un array de 100 elementos, lo llena con números aleatorios
en el intervalo [0, 1] y lo imprime en la Terminal.
http://stackoverflow.com/questions/6218399/how-to-generate-a-random-number-between-0-and-1
*/
void ej4(){

    double arreglo[100];
    int i;
    srand(time(NULL));

    for(i=0; i <100; i++){
        arreglo[i] = (double)rand() / (double)RAND_MAX ;
    }

    for(i=0; i <100; i++){
        printf("%7d%13f\n", i, arreglo[i]);
    }

}

/*
Desarrollar el mismo programa del problema anterior, recibiendo la cantidad de elementos como
entrada del usuario.
El arreglo debe ser dinamico
*/
void ej5(){

    int numeroElementos,i;
    double *arreglo;

    printf ("¿Cuántos elementos quieres? ");
    scanf ("%d", &numeroElementos);

    arreglo = (double*)malloc(numeroElementos*sizeof(double));

    if (arreglo==NULL)
    {
    perror("Problemas reservando memoria");
    exit (1);
    }

    srand(time(NULL));
    for(i=0; i <numeroElementos; i++){
        arreglo[i] = (double)rand() / (double)RAND_MAX ;
    }

    for(i=0; i <numeroElementos; i++){
        printf("%7d%13f\n", i, arreglo[i]);
    }

    free (arreglo);

}

/*
 * Desarrollar el mismo programa del problema anterior, esta vez imprimiendo los números generados en un
 * archivo utilizando el siguiente formato: [n0, n1, ..., nn],
 * donde ni es el número almacenado en la posición i del array.
 */
void ej6(const char * path){
    FILE *f = fopen("ej6pr0.txt", "w");
    if (f == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    /* print some text */
    const char *text = "Write this to the file";
    fprintf(f, "Some text: %s\n", text);

    /* print integers and floats */
    int j = 1;
    float py = 3.1415927;
    fprintf(f, "Integer: %d, float: %f\n", j, py);


    int numeroElementos,i;
    double *arreglo;

    printf ("¿Cuántos elementos quieres? ");
    scanf ("%d", &numeroElementos);

    arreglo = (double*)malloc(numeroElementos*sizeof(double));

    if (arreglo==NULL)
    {
        perror("Problemas reservando memoria");
        exit (1);
    }

    srand(time(NULL));
    for(i=0; i <numeroElementos; i++){
        arreglo[i] = (double)rand() / (double)RAND_MAX ;
    }
    fprintf(f, "[");
    for(i=0; i <numeroElementos; i++){
        fprintf(f, "%f,", arreglo[i]);
    }
    fprintf(f, "]");

    free (arreglo);
    fclose(f);
    printf("Archivo guardado en: %s", path);
}

void ej7(){
    Vec3 a;
    Vec3 b;
    vec3Init(&a, 1.0f, 2.0f, 3.0f);
    vec3Init(&b, 3.0f, 2.0f, 1.0f);
    printf("<a,b> = %.2f\n", add(&a, &b));

}

void ej8(){
    Vec3 a;
    Vec3 b;
    vec3Init(&a, 1.0f, 2.0f, 3.0f);
    vec3Init(&b, 3.0f, 2.0f, 1.0f);
    Vec3 c = addp(&a, &b);
    toString(&a);
    toString(&b);
    toString(&c);
}


/**
 * Desarrollar un programa C que crea un array de 100 “Vec3” donde los 3 componentes (x, y, z)
 * de cada elemento son un número aleatorio en el intervalo [0, 1].
 */
void ej10(){
    int i=0, cant=100;
    Vec3 pVec3[100];

    for(i; i <cant; i++){
        pVec3[i] = vec3InitRandom();
        toString(&pVec3[i]);
    }
}




