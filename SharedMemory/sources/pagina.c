#include "../headers/pagina.h"

void * new_pagina(int * pag_logica, int * pag_fisica)
{
    Pagina *n = malloc(sizeof(Pagina));
    n->pag_logica = pag_logica;
    n->pag_fisica = pag_fisica;
    return n;
}