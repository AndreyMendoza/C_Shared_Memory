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

    struct sembuf sem_op;

    /* wait on the semaphore, unless it's value is non-negative. */
    sem_op.sem_num = 0;
    sem_op.sem_op = -1;
    sem_op.sem_flg = 0;
    semop(sem_set_id, &sem_op, 1);
}

/*--------------------------------------------------------------------------------------------------------------------*/

void sem_unlock(int sem_set_id)
{
    /* structure for semaphore operations.   */
    struct sembuf sem_op;

    /* signal the semaphore - increase its value by one. */
    sem_op.sem_num = 0;
    sem_op.sem_op = 1;   /* <-- Comment 3 */
    sem_op.sem_flg = 0;
    semop(sem_set_id, &sem_op, 1);
}

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
    printf("%s\n", buff);

    fclose(file);

    return atoi(buff);
}

/*--------------------------------------------------------------------------------------------------------------------*/
