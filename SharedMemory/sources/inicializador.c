#include "../headers/inicializador.h"


void inicializar()
{
    int shm_id = 0, err = 0;
    sem_t  *sp;
    int retval;

    printf("Reservando espacio de memoria...");
    if ((shm_id = shmget(IPC_PRIVATE, SEGMENTSIZE, SEGMENTPERM)) == -1)
        printf("...ERROR\n");
    else
        printf("...OK. ID = %d\n", shm_id);


    // Asociar la memoria
    printf("Asociando memoria...");
    sp = (sem_t *) shmat(shm_id, (void *)0, 0);
    if((int)sp == -1)
    {
        printf("...ERROR\n");
        exit(2);
    }

    retval = sem_init(sp, 1, 2);

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

    sem_destroy (sp);

    printf("Removiendo segmento...");
    if ((err = shmctl(shm_id, IPC_RMID, 0) == -1))
        printf("...ERROR\n");
    else
        printf("...OK. Removido = %d\n", err);

}

// #####################################################################################################################

void sem_test(char * argv[]) {
    const char * sem_name;
    int op = 0;
    int val = 0;

    sem_name = argv[1];
    op = atoi(argv[2]);


    sem_t *sem = sem_open(sem_name,  O_CREAT|O_EXCL, S_IRUSR|S_IWUSR, 0);

    if (sem != SEM_FAILED)
        printf("Semaforo  creado!\n");
    else if (errno == EEXIST)
    {
        printf("Parece que el semaforo ya existe...!\n");
        sem = sem_open(sem_name, 0);
    }

    assert(sem != SEM_FAILED);
    sem_getvalue(sem, &val);
    printf("Valor del semaforo antes: %d\n", val);

    if (op == 1)
    {
        printf("Incrementando el semaforo...\n");
        sem_post(sem);
    }

    else if (op == -1)
    {
        printf("Decrementando el semaforo...\n");
        sem_wait(sem);
    }
    else if (op == 2)
    {
        printf("Limpiando semaforo...\n");
        sem_close(sem);
        sem_unlink(sem_name);
        exit(1);

    }
    else
        printf("Operacion no definida!\n");

    sem_getvalue(sem, &val);
    printf("Valor actual del semaforo: %d\n", val);
    sem_close(sem);
}







