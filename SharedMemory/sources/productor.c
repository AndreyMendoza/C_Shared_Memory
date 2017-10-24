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
        crear_hilos_segmentos();
    }

    // Paginacion
    else if(strcmp(tipoAlgoritmo,"-p")==0)
    {
        prod_paginas(size, shm_id);
        crear_hilos_paginas();
    }

    else{
        printf("El tipo de algoritmo ingresado es desconocido, existen:\n\t-s segmentación\n\t-p paginación\n");
    }

    cerrar_sem(sem);
}

/*--------------------------------------------------------------------------------------------------------------------*/

void crear_hilos_paginas()
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

void crear_hilos_segmentos()
{
    int tiempo = random_number(20, 60);
    pthread_t thread;

    while(true){
        if(pthread_create(&thread, 0, reservar_segmentos, NULL) < 0){
            break;
        }

        sleep((unsigned int)tiempo);
    }
}

/*--------------------------------------------------------------------------------------------------------------------*/

void * reservar_segmentos(void * argv){
    
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

    //Variables para registrar en bitacora
    char * time;
    char buf[256];

    bloquear_sem(sem);

    shm_addr = asociar_mem(shm_id);

    int * n_celdas = (int *) shm_addr;
    int * n_celdas_disp = (int *) (shm_addr + sizeof(int));
    Pagina * memoria = (Pagina *) (shm_addr + OFFSET);

    if (*n_celdas_disp > n_paginas)
    {
        time = get_time();
        sprintf(buf, "Thread %ld. --> Asignando %d páginas de memoria.  --> %s", (long)thread_id, n_paginas , time);
        registrar_accion("../data/bitacora_asignados.txt", buf);

        *n_celdas_disp = *n_celdas_disp - n_paginas;
        for (int i = 0; (i < * n_celdas) && (n_paginas > 0); ++i)
        {
            if (memoria[i].estado == DISPONIBLE)
            {
                memoria[i].estado = OCUPADO;
                memoria[i].thread_id = thread_id;
                n_paginas--;

                sprintf(buf, "\tPágina %d asignada",i);
                registrar_accion("../data/bitacora_asignados.txt", buf);
            }
        }

        time = get_time();
        sprintf(buf, "\tAsignación finalizada con éxito. --> %s\tEsperando %d segundos para liberar memoria\n", time, tiempo);
        registrar_accion("../data/bitacora_asignados.txt", buf);

        desbloquear_sem(sem);

        ver_memoria_paginada(*(int *)shm_addr, (void *) memoria);
        sleep((unsigned int) tiempo);

        bloquear_sem(sem);

        // Eliminar memoria
        time = get_time();
        sprintf(buf, "Thread %ld. --> Desasignando %d páginas de memoria.  --> %s", (long)thread_id, n_paginas_aux , time);
        registrar_accion("../data/bitacora_asignados.txt", buf);

        for (int i = 0; (i < * n_celdas) && (n_paginas < n_paginas_aux); ++i)
        {
            if ((memoria[i].estado == OCUPADO) && ((long) memoria[i].thread_id == (long) thread_id))
            {
                memoria[i].estado = DISPONIBLE;
                memoria[i].thread_id = NULL;
                n_paginas++;
                sprintf(buf, "\tPágina %d desasignada",i);
                registrar_accion("../data/bitacora_asignados.txt", buf);
            }
        }
        *n_celdas_disp = *n_celdas_disp + n_paginas;

        time = get_time();
        sprintf(buf, "\tDesasignación finalizada con éxito. --> %s", time);
        registrar_accion("../data/bitacora_asignados.txt", buf);
    }
    else
    {
        char * time = get_time();
        char buf[256];
        sprintf(buf, "El thread %ld no encontró espacios suficientes. Solicitaba %d páginas. Hora: %s", (long)thread_id, n_paginas_aux, time);
        registrar_accion("../data/bitacora_fallidos.txt", buf);

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
    * n_celdas = 0;
    * n_celdas_disp = 0;
    for (int i = 0; (i < size) && (*n_celdas < size); i++)
    {
        agregar_pagina(n_celdas, n_celdas_disp, memoria, *n_celdas);
    }

    ver_memoria_paginada(*(int *)shm_addr, (void *) memoria);

    desbloquear_sem(sem);
}

/*--------------------------------------------------------------------------------------------------------------------*/

void prod_segmentos(int size, int shm_id)
{
    int n__segmentos = random_number(1,5);
    int n_pag_segmento = random_number(1,3);
    sem_t * sem = (sem_t *) solicitar_sem(SEM_NAME);
    void * shm_addr = asociar_mem(shm_id);

    bloquear_sem(sem);

    int * n_celdas = (int *) shm_addr;
    int * n_celdas_disp = (int *) (shm_addr + sizeof(int));
    Segmento * memoria = (Segmento *) (shm_addr + OFFSET);
    * n_celdas = 0;
    * n_celdas_disp = 0;

    for (int i = 0; (i < size) && (*n_celdas < size); i++)
    {
        agregar_segmento(n_celdas, memoria, n_celdas_disp);
    }

    //ver_memoria_paginada(*(int *)shm_addr, (void *) memoria);

    desbloquear_sem(sem);
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

/*--------------------------------------------------------------------------------------------------------------------*/

void * ver_memoria_segmentada(int n_paginas, void * memoria_ref)
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