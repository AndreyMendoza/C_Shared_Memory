#ifndef SHAREDMEMORY_SEGMENTO_H
#define SHAREDMEMORY_SEGMENTO_H

#include "imports.h"

typedef struct Segmento{
    int * n_segmento;
    int * reg_base;
    int * tamanho;

} Segmento;


void * new_segmento(int * n_segmento, int * reg_base, int * tamanho);


#endif //SHAREDMEMORY_SEGMENTO_H
