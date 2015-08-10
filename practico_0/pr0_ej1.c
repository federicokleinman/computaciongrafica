#include <assert.h>
#include "practico_0.h"


/**
 * Para ejecutar los ejercicios, debemos recibir por linea de comandos, el numero de ejercicio, y luego parametros opcionales.
 */
int main(int argc, const char* argv[]) {

    int count;
    int d;

    printf ("This program was called with \"%s\".\n",argv[0]);

    if (argc > 1)
    {
//        for (count = 1; count < argc; count++)
//        {
//
//            printf("argv[%d] = %s\n", count, argv[count]);
//        }

        d = atoi(argv[1]);
        printf("\nEjercicio => %d\n",d);

        switch(d){   /* break are optional */
            case 1 : ej1(); break;
            case 2 : ej2(); break;
            case 3 : ej3(); break;
            case 4 : ej4(); break;
            case 5 : ej5(); break;
            case 6 : ej6( argv[0]); break;  // TODO verificar cant de argumentos de
            case 7 : ej7(); break;
            case 8 : ej8(); break;
//            case '9' :
            case 10 :  ej10(); break;
//TODO falta mergeo con el ejercio 11 de casa
            case 12 :
                assert(argc==4);
                ej12(atoi(argv[2]),atoi(argv[3]));
                break;

            default :
                printf("No existe un ejercicio con este el numero  %s\n", argv[1]);
        }
    }
    else
    {
        printf("Ingrese con un parametro numero de ejercicio.\n");
    }

    return 0;
}
