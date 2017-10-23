#include "../headers/productor.h"


/*--------------------------------------------------------------------------------------------------------------------*/

void producir(char * tipoAlgoritmo, int distribucion_generador)
{
    int size = read_int("../data/size.txt");
    int shm_id = read_int("../data/shm_id.txt");
    sem_t * sem = (sem_t *) solicitar_sem(SEM_NAME);

    // Segmentacion
    if(strcmp(tipoAlgoritmo,"-s")==0)
    {
        prod_segmentos(size, shm_id);

    }

    // Paginacion
    else if(strcmp(tipoAlgoritmo,"-p")==0)
    {
        prod_paginas(size, shm_id);
        crear_hilos_Paginas();
    }

    else{
        printf("El tipo de algoritmo ingresado es desconocido, existen:\n\t-s segmentación\n\t-p paginación\n");
    }

    cerrar_sem(sem);
}

/*--------------------------------------------------------------------------------------------------------------------*/

void crear_hilos_Paginas()
{
    int tiempo = random_number(3, 6);
    int n_paginas;
    pthread_t thread;

    while(true){
        n_paginas = random_number(1,10);
        pthread_create(&thread, 0, reservar_paginas, &n_paginas);

        sleep((unsigned int)tiempo);

        if (n_paginas < -1) break;

    }
}

/*--------------------------------------------------------------------------------------------------------------------*/

void * reservar_paginas(void * ref_n_paginas)
{
    int n_paginas = (*(int *)ref_n_paginas);
    int n_paginas_aux = n_paginas;
    sem_t * sem = (sem_t *) solicitar_sem(SEM_NAME);
    pthread_t thread_id = pthread_self();
    pthread_detach(thread_id);
    void * shm_addr;
    int shm_id = read_int("../data/shm_id.txt");
    int tiempo = random_number(20,60);

    bloquear_sem(sem);

    shm_addr = asociar_mem(shm_id);

    int * n_celdas = (int *) shm_addr;
    int * n_celdas_disp = (int *) (shm_addr + sizeof(int));
    Pagina * memoria = (Pagina *) (shm_addr + OFFSET);

    if (*n_celdas_disp > n_paginas)
    {
        *n_celdas_disp = *n_celdas_disp - n_paginas;
        for (int i = 0; (i < * n_celdas) && (n_paginas > 0); ++i)
        {
            if (memoria[i].estado == DISPONIBLE)
            {
                memoria[i].estado = OCUPADO;
                memoria[i].thread_id = thread_id;
                n_paginas--;
            }
        }
        registrar_accion("../data/bitacora.txt", "El thread %d reservo memoria.");

        desbloquear_sem(sem);

        ver_memoria_paginada(*(int *)shm_addr, (void *) memoria);
        sleep((unsigned int) tiempo);
        

        bloquear_sem(sem);

        // Eliminar memoria
        for (int i = 0; (i < * n_celdas) && (n_paginas < n_paginas_aux); ++i)
        {
            if ((memoria[i].estado == OCUPADO) && ((long) memoria[i].thread_id == (long) thread_id))
            {
                memoria[i].estado = DISPONIBLE;
                memoria[i].thread_id = NULL;
                n_paginas++;
            }
        }
        *n_celdas_disp = *n_celdas_disp + n_paginas;
    }
    else
    {
        registrar_accion("../data/bitacora.txt", "El thread %d no encontro espacio suficiente.");
    }
    ver_memoria_paginada(*(int *)shm_addr, (void *) memoria);
    desbloquear_sem(sem);
}

/*--------------------------------------------------------------------------------------------------------------------*/

void prod_paginas(int size, int shm_id)
{
    sem_t * sem = (sem_t *) solicitar_sem(SEM_NAME);
    void * shm_addr = asociar_mem(shm_id);

    bloquear_sem(sem);

    int * n_celdas = (int *) shm_addr;
    int * n_celdas_disp = (int *) (shm_addr + sizeof(int));
    Pagina * memoria = (Pagina *) (shm_addr + OFFSET);

    for (int i = 0; i < size; i++)
    {
        agregar_pagina(n_celdas, n_celdas_disp, memoria, *n_celdas);
    }

    ver_memoria_paginada(*(int *)shm_addr, (void *) memoria);

    desbloquear_sem(sem);
}

/*--------------------------------------------------------------------------------------------------------------------*/

void prod_segmentos(int size, int shm_id)
{
    int cant_segmentos = random_number(1,5);
    int cant_espaciosXsegmento = random_number(1,3);
    sem_t * sem = (sem_t *) solicitar_sem(SEM_NAME);
}

/*--------------------------------------------------------------------------------------------------------------------*/

void * ver_memoria_paginada(int n_paginas, void * memoria_ref)
{
    int shm_id = read_int("../data/shm_id.txt");
    void * shm_addr = asociar_mem(shm_id);
    int * pag_disp = (int *) (shm_addr + sizeof(int));
    Pagina * memoria = (Pagina *) memoria_ref;
    printf("Paginas disponibles: %d\n", *pag_disp);
    for (int i = 0; i < n_paginas; i++) {
        printf("P.Logica: %d | Estado:%d | Proc.ID:%ld\n",
               memoria[i].pag_logica, memoria[i].estado, (long) memoria[i].thread_id);
    }
}