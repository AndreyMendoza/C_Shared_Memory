#ifndef SHAREDMEMORY_PRODUCTOR_H
#define SHAREDMEMORY_PRODUCTOR_H

#include "imports.h"



void producir(char * tipoAlgoritmo, int distribucion_generador);
void prod_paginas(int size, int shm_id);
void prod_segmentos(int size, int shm_id);
void crear_hilos_Paginas();
void * reservar_paginas(void * n_paginas);
void * ver_memoria_paginada(int n_paginas, void * memoria);


#endif //SHAREDMEMORY_PRODUCTOR_H
