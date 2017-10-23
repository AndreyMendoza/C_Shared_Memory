#ifndef SHAREDMEMORY_HERRAMIENTAS_H
#define SHAREDMEMORY_HERRAMIENTAS_H

#include <time.h>
#include "imports.h"

int random_number(int min_num, int max_num);
void sem_lock(int sem_set_id);
void sem_unlock(int sem_set_id);
// General
void save_int(int num, char * file_name);
int read_int(char * file_name);
void registrar_accion(char * file_name, char * registro);

// Semaforos
void * solicitar_sem(char * nombre_sem);
void bloquear_sem(void * sem_ref);
void desbloquear_sem(void * sem_ref);
void cerrar_sem(void * sem_ref);

// Memoria
int solicitar_mem();
void * asociar_mem(int id);

#endif //SHAREDMEMORY_HERRAMIENTAS_H