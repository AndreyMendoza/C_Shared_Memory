#ifndef SHAREDMEMORY_BIBLIOTECAS_H
#define SHAREDMEMORY_BIBLIOTECAS_H


// Generales
#include <stdio.h>
#include <stdlib.h>
#include <libgen.h>
#include <string.h>
#include <errno.h>

// Otros headers
#include "inicializador.h"
#include "productor.h"
#include "espia.h"
#include "finalizador.h"
#include "herramientas.h"
#include "list.h"
#include "pagina.h"
#include "segmento.h"

// Memoria Compartida
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

// Semaforos
#include <semaphore.h>
#include <sys/stat.h>
#include <sys/sem.h>


// Variables globales
#define SEGMENTSIZE sizeof(sem_t)
#define SEGMENTPERM 0666

#endif //SHAREDMEMORY_BIBLIOTECAS_H
