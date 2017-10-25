#include "../headers/imports.h"

void finalizar()
{
    int shm_id = read_int("../data/shm_id.txt");
    int shm_id_proc = read_int("../data/shm_id_proc.txt");

    system("killall prod");
    printf("\nProcesos eliminados\n");

    if (shmctl(shm_id, IPC_RMID, 0) != -1)
        printf("\nMemoria compartida liberada\n");

    if (shmctl(shm_id_proc, IPC_RMID, 0) != -1)
        printf("\nMemoria compartida de procesos liberada\n");


    if (sem_unlink(SEM_NAME) == 0)
        printf("\nSemaforo de memoria compartido eliminado\n");

    if (sem_unlink(SEM_NAME_PROC) == 0)
        printf("\nSemaforo de memoria de procesos eliminado\n");
}