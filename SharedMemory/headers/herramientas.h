#ifndef SHAREDMEMORY_HERRAMIENTAS_H
#define SHAREDMEMORY_HERRAMIENTAS_H

#include <time.h>
#include "imports.h"

int random_number(int min_num, int max_num);
void sem_lock(int sem_set_id);
void sem_unlock(int sem_set_id);
void save_int(int num, char * file_name);
int read_int(char * file_name);

#endif //SHAREDMEMORY_HERRAMIENTAS_H
