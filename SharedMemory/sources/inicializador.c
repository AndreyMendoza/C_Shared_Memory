#include "../headers/inicializador.h"


void inicializar()
{
    int shm_id;
    char* shm_addr;


    // Solicitar espacio de memoria compartida
    printf("Solicitando espacio de memoria...");

    shm_id = shmget(IPC_PRIVATE, 2048, IPC_CREAT | IPC_EXCL | 0600);
    if (shm_id == -1) {
        perror("FAILED\n");
        exit(1);
    }
    printf("OK. ID: %d\n", shm_id);

    // Asociar segmento de memoria al proceso
    printf("Asociando espacio de memoria...");
    shm_addr = shmat(shm_id, NULL, 0);
    if (!shm_addr) { /* operation failed. */
        printf("FAILED\n");
        exit(1);
    }

}
