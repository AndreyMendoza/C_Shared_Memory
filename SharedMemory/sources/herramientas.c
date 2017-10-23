#include "../headers/herramientas.h"



/*--------------------------------------------------------------------------------------------------------------------*/
int random_number(int min_num, int max_num)
{
    int result = 0, low_num = 0, hi_num = 0;

    if (min_num < max_num)
    {
        low_num = min_num;
        hi_num = max_num + 1; // include max_num in output
    } else {
        low_num = max_num + 1; // include max_num in output
        hi_num = min_num;
    }

    srand(time(NULL));
    result = (rand() % (hi_num - low_num)) + low_num;
    return result;
}



/*--------------------------------------------------------------------------------------------------------------------*/

void sem_lock(int sem_set_id)
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
void registrar_accion(char * file_name, char * registro){
    FILE *fptr;

    //Se abre con "a" para realizar un append en el archivo
    fptr = fopen(file_name, "a");
    if(fptr == NULL)
    {
        printf("Error opening file!");
        exit(1);
    }

    fprintf(fptr,"\n%s", registro);
    fclose(fptr);
}