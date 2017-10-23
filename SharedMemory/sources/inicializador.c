#include "../headers/inicializador.h"


void inicializar(int size)
{
    int shm_id, *n_celdas;
    void * shm_addr;
    sem_t * sem = NULL;
    Pagina * memoria;


    // Inicializar el semaforo
    sem = (sem_t *) solicitar_sem(SEM_NAME);

    // Crear espacio de memoria compartida
    shm_id = solicitar_mem();
    save_int(shm_id, "../data/shm_id.txt");
    shm_addr = asociar_mem(shm_id);

    // Guardar lista que va a contener estructura de la memoria
    n_celdas = (int *) shm_addr;
    *n_celdas = 0;
    memoria = (Pagina *) (shm_addr + sizeof(int));

//    agregar_pagina(n_celdas, memoria, 1, 1000);
//    agregar_pagina(n_celdas, memoria, 2, 2000);
//
//    printf("P.Logica: %d | P.Fisica:%d\n", memoria[0].pag_logica, memoria[0].pag_fisica);
//    printf("P.Logica: %d | P.Fisica:%d\n", memoria[1].pag_logica, memoria[1].pag_fisica);

    // cerrar_sem(sem);

}


