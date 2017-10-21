#ifndef SHAREDMEMORY_HERRAMIENTAS_H
#define SHAREDMEMORY_HERRAMIENTAS_H

#include "imports.h"


void sem_lock(int sem_set_id);
void sem_unlock(int sem_set_id);
void save_int(int num, char * file_name);
int read_int(char * file_name);

#endif //SHAREDMEMORY_HERRAMIENTAS_H
