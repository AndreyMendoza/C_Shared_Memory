#include "../headers/productor.h"


void producir(char * tipoAlgoritmo, int distribucion_generador)
{
    // Variable común entre paginación y segmentación
    int tiempo = random_number(20,60);

    //--- Algoritmo de segmentación ---
    if(strcmp(tipoAlgoritmo,"-s")==0){
        int cant_segmentos = random_number(1,5);
        int cant_espaciosXsegmento = random_number(1,3);

    }//--- Algoritmo de paginación ---
    else if(strcmp(tipoAlgoritmo,"-p")==0){
        int cant_paginas = random_number(1,10);

    }//--- Algoritmo desconocido ---
    else{
        printf("El tipo de algoritmo ingresado es desconocido, existen:\n\t-s segmentación\n\t-p paginación\n");
    }


    sem_t * sem = NULL;
    int shm_id;
    Pagina * memoria;
    void * shm_addr;

    sem = (sem_t *) solicitar_sem(SEM_NAME);

    bloquear_sem(sem);

    shm_id = read_int("../data/shm_id.txt");
    shm_addr = asociar_mem(shm_id);

    printf("Cantidad de celdas: %d\n", *((int *) shm_addr));

    desbloquear_sem(sem);

    cerrar_sem(sem);
}