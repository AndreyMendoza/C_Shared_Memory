#ifndef SHAREDMEMORY_PAGINA_H
#define SHAREDMEMORY_PAGINA_H

#include "imports.h"

typedef struct Pagina{
    int *pag_logica;
    int *pag_fisica;

} Pagina;


void * new_pagina(int * pag_logica, int * pag_fisica);

#endif //SHAREDMEMORY_PAGINA_H
