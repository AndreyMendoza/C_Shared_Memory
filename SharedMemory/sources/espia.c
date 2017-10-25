#include "../headers/imports.h"


//----------------------------------------------------------
void espiar_mem()
{
    int shm_id = read_int("../data/shm_id.txt");
    sem_t * sem = (sem_t *) solicitar_sem(SEM_NAME);
    void * shm_addr = asociar_mem(shm_id);
    Pagina * memoria = (Pagina *) (shm_addr + OFFSET);
    int * tipo = (int *) (shm_addr + (sizeof(int) * 2));

    bloquear_sem(sem);
    printf("\n---------------------   Estado de la memoria   ---------------------\n\n");

    if (* tipo == PAGINACION)
        ver_memoria_paginada(*(int *)shm_addr, (void *) memoria);
    else if (* tipo == SEGMENTACION)
        ver_memoria_segmentada(*(int *)shm_addr, (void *) memoria);
    else
        printf("LA MEMORIA NO HA SIDO INICIALIZADA!");

    printf("\n----------------------------   FIN   -------------------------------\n");
    desbloquear_sem(sem);
}


//----------------------------------------------------------
void espiar_proc(){
    printf("\n---------------------   Estado de la memoria   ---------------------\n\n");

    

    printf("\n----------------------------   FIN   -------------------------------\n");
}