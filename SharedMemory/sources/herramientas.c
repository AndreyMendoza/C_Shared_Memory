#include "../headers/herramientas.h"


/*--------------------------------------------------------------------------------------------------------------------*/

void save_int(int num, char * file_name)
{
    FILE *file = fopen(file_name, "w");
    if (file == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    fprintf(file, "%d", num);
    fclose(file);
}

/*--------------------------------------------------------------------------------------------------------------------*/

int read_int(char * file_name)
{
    FILE *file;
    char buff[255];

    file = fopen(file_name, "r");
    fscanf(file, "%s", buff);
    fclose(file);

    return atoi(buff);
}

/*--------------------------------------------------------------------------------------------------------------------*/

void * solicitar_sem(char * nombre_sem)
{
    sem_t * sem;

    printf("Solicitando semaforo...");
    sem = sem_open (nombre_sem , O_CREAT|O_EXCL , S_IRUSR|S_IWUSR , 1);

    if (!sem == SEM_FAILED)
        printf("creado...");
    else if (errno == EEXIST)
    {
        sem = sem_open (SEM_NAME, 0);
        printf("abierto...");
    }
    printf("OK\n");
    return (void *) sem;
}

/*--------------------------------------------------------------------------------------------------------------------*/

void bloquear_sem(void * sem_ref)
{
    sem_t * sem = (sem_t *) sem_ref;
    int result = 0;

    printf("Bloqueando semaforo...");

    result = sem_wait(sem);
    if (result == -1)
    {
        printf("ERROR\n");
        exit(2);
    }
    printf("OK\n");
}

/*--------------------------------------------------------------------------------------------------------------------*/

void desbloquear_sem(void * sem_ref)
{
    sem_t * sem = (sem_t *) sem_ref;
    int result;

    printf("Desbloqueando semaforo...");

    result = sem_post(sem);
    if (result == -1)
    {
        printf("ERROR\n");
        exit(2);
    }
    printf("OK\n");
}

/*--------------------------------------------------------------------------------------------------------------------*/

void cerrar_sem(void * sem_ref)
{
    sem_t * sem = (sem_t *) sem_ref;
    int result = 0;

    printf("Cerrando semaforo...");

    result = sem_close (sem);
    if (result == -1)
    {
        printf("ERROR\n");
        exit(2);
    }
    printf("clausurado...");

    result = sem_unlink (SEM_NAME);
    if (result == -1)
    {
        printf("ERROR\n");
        exit(2);
    }
    printf("OK\n");
}

/*--------------------------------------------------------------------------------------------------------------------*/

void operar_semaforo(void * sem_ref, int operacion)
{
    sem_t * sem = (sem_t *) sem_ref;
    if (operacion == 1 )
    {
        printf("Incrementando el semaforo...");
        sem_post (sem);
    }
    else  if (operacion ==  -1 )
    {
        printf("Decrementando el semaforo...");
        sem_wait (sem);
    }
    else  if (operacion == 2 ){
        printf("Limpiando semaforo...");
        sem_close (sem);
        sem_unlink (SEM_NAME);
    }
    printf("OK\n");
}

/*--------------------------------------------------------------------------------------------------------------------*/

int solicitar_mem()
{
    int shm_id;

    // Solicitar espacio de memoria compartida
    printf("Solicitando espacio de memoria...");
    shm_id = shmget(IPC_PRIVATE, SEGMENTSIZE, IPC_CREAT | IPC_EXCL | SEGMENTPERM);
    if (shm_id == -1) {
        perror("ERROR\n");
        exit(1);
    }
    printf("OK. ID: %d\n", shm_id);

    return shm_id;
}

/*--------------------------------------------------------------------------------------------------------------------*/

void * asociar_mem(int shm_id)
{
    void * shm_addr;

    // Asociar segmento de memoria al proceso
    printf("Asociando a espacio de memoria %d...", shm_id);
    shm_addr = shmat(shm_id, NULL, 0);
    if (!shm_addr) { /* operation failed. */
        printf("ERROR\n");
        exit(1);
    }
    printf("OK\n");

    return shm_addr;
}

