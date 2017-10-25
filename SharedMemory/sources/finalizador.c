#include "../headers/imports.h"

void finalizar()
{
    sem_t * sem_shm = (sem_t *) solicitar_sem(SEM_NAME);
    sem_t * sem_proc = (sem_t *) solicitar_sem(SEM_NAME_PROC);

    system("killall prod");
    printf("Procesos eliminados\n");


//    cerrar_sem(sem_shm);
//    cerrar_sem(sem_proc);

}