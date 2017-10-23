#include "../headers/inicializador.h"


void inicializar(int size)
{
    int shm_id, result;
    void * shm_addr;
    sem_t * sem = NULL;
    List * memoria;


    // Inicializar el semaforo
    sem = (sem_t *) solicitar_sem(SEM_NAME);

    // Crear espacio de memoria compartida
    shm_id = solicitar_mem();
    save_int(shm_id, "../data/shm_id.txt");
    shm_addr = asociar_mem(shm_id);

    // Guardar lista que va a contener estructura de la memoria
    memoria = (List *) shm_addr;
    memoria = new_list();
    add(memoria, &shm_id);

    printf("VALOR: %d\n", *(int *)pop(memoria));
    getchar();

    // cerrar_sem(sem);

}


