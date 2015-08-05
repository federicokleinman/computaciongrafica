#define printSizeof(a, type) ({ \
    printf("The number of bytes in a %s is %zu.\n", a, sizeof(type)); \
})

void ej1();
void ej2();
void ej3();
void ej4();
void ej5();

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
