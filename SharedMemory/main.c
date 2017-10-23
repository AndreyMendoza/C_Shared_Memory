#include "headers/imports.h"


int main(int argc, char **argv) {

    printf("\n");
    puts("************************** INICIO DEL PROGRAMA ***************************");
    printf("\n");


    char * modo_programa = basename(argv[0]);

    //Ejemplo-> ./inic 2000
    if (strcmp(modo_programa, "inic") == 0)
    {
        /*Cantidad de espacios de memoria que va haber*/
        if(argc < 2){
            printf("Parámetros incompletos, falta el tamaño de la memoria\n");
        }else{
            int size = atoi(argv[1]);
            inicializar(size);
        }
    }

    //Ejemplo-> ./prod -s
    else if (strcmp(modo_programa, "prod") == 0) {
        // Tipo de algoritmo [Paginación(-p)| Segmentación(-s)]
        if(argc<2){
            printf("Parámetros incompletos, falta el tipo de algoritmo(-s|-p) con el que se van a crear los procesos\n");
        }
        else{
            char * tipoAlgoritmo = argv[1];

            // La Distribución con la que se generaran los procesos
            // estará determinada por un tiempo aleatorio(30s-60s)
            int distribucion_generador = random_number(30,60);

            producir(tipoAlgoritmo, distribucion_generador);
        }
    }
    //Ejemplo-> ./espia men
    else if (strcmp(modo_programa, "espia") == 0){
        // Estado de la memoria -> mem
        // Estado de los procesos -> proc
        if(argc>2){
            char * solicitud = argv[1];

            if(strcmp(solicitud,"mem")==0){
                espiarMem();
            }
            else if(strcmp(solicitud,"proc")==0){
                espiarProc();
            }
            else{
                printf("Solicitud %s desconocida.",solicitud);
                printf("Comandos de espía aceptados:\n\t-> mem, para espiar la memoria\n\t-> proc, para espiar los procesos");
            }
        }
        else{
            printf("Parámetros incompletos, falta el modo de espiar(men|proc)\n");
        }
    }

    else if (strcmp(modo_programa, "fin") == 0) {
        finalizar();
    }


    printf("\n");
    puts("**************************** FIN DEL PROGRAMA ****************************");


    return 0;
}