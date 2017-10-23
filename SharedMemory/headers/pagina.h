#ifndef SHAREDMEMORY_PAGINA_H
#define SHAREDMEMORY_PAGINA_H

#include "imports.h"

typedef struct Pagina{

    int pag_logica;
    int pag_fisica;

} Pagina;


void agregar_pagina(int * n_paginas, Pagina * memoria, int pag_logica, int pag_fisica);

#endif //SHAREDMEMORY_PAGINA_H
