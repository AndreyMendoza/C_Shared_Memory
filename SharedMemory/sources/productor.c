#include "../headers/productor.h"


void producir(int shm_id)
{
    int *mem;
    sem_t  *sp;
    int retval, err;

    printf("SHM_ID = %d\n", shm_id);

    // Asociarse al segmento
    printf("Asociandose a memoria...");
    sp = (sem_t*) shmat(shm_id, (void *)0, 0);
    if ((int)mem == -1)
        printf("ERROR\n");
    else
        printf("OK. Contenido = %d\n", *mem);


    // Inicializar Semaforo
    retval = sem_init(sp, 1, 1);

    if (retval != 0)
    {
        perror("No se pudo inicializar el semaforo.");
        exit (3);
    }

    retval = sem_trywait (sp);
    printf("Se hizo  trywait. Retorno  %d  >\n",retval);
    getchar ();

    retval = sem_trywait (sp);
    printf("Se hizo  trywait. Retorno  %d  >\n",retval);
    getchar ();

    retval = sem_trywait (sp);
    printf("Se hizo  trywait. Retorno  %d  >\n",retval);
    getchar ();


    printf("Desasociando segmento");
    if ((err = shmdt((void *) sp) == -1))
        printf("...ERROR\n");
    else
        printf("...OK. Desasociado = %d\n", (int)err);

}