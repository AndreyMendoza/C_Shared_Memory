#include "../headers/productor.h"


void producir()
{
    sem_t * sem = NULL;
    int shm_id;
    List * memoria;
    void * shm_addr;

    sem = (sem_t *) solicitar_sem(SEM_NAME);

    bloquear_sem(sem);

    shm_id = read_int("../data/shm_id.txt");
    shm_addr = asociar_mem(shm_id);
    memoria = (List *) shm_addr;

    int a = *(int *) pop(memoria);
    printf("SHM_ID: %d", a);

    desbloquear_sem(sem);

    //cerrar_sem(sem);
}