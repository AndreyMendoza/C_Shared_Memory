#include "headers/imports.h"


int main(int argc, char **argv) {

    printf("\n");
    puts("************************** INICIO DEL PROGRAMA ***************************");
    printf("\n");


    char * modo_programa = basename(argv[0]);


    if (strcmp(modo_programa, "inic") == 0)
    {
        /*Cantidad de espacios de memoria que va haber*/
        int size = 2048;
        inicializar(size);
    }

    else if (strcmp(modo_programa, "prod") == 0) {
        // Tipo de algoritmo (Paginación| Segmentación)
        // tipoAlgoritmo = "-s" | "-p";
        //char * tipoAlgoritmo = argv[2];
        char * tipoAlgoritmo = "-s";

        //-----------Valores generados para cada hilo-----------
        //------------------------------------------------------
        // Variables de segmentación
        int cant_segmentos = random_number(1,5);
        int cant_espaciosXsegmento = random_number(1,3);

        // Variables de paginación
        int cant_paginas = random_number(1,10);

        // Variable común entre paginación y segmentación
        int tiempo = random_number(20,60);
        //------------------------------------------------------
        //------------------------------------------------------

        // La Distribución con la que se generaran los procesos
        // estará determinada por un tiempo aleatorio(30s-60s)
        int distribucion_generador = random_number(30,60);

        producir(atoi(argv[1]));
    }

    else if (strcmp(modo_programa, "espia") == 0){
        // Estado de la memoria -> mem
        // Estado de los procesos -> proc
        char * solicitud = "mem";

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

    else if (strcmp(modo_programa, "fin") == 0) {

        finalizar();
    }


    printf("\n");
    puts("**************************** FIN DEL PROGRAMA ****************************");


    return 0;
}