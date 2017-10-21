#include "../headers/segmento.h"


void * new_segmento(int * n_segmento, int * reg_base, int * tamanho)
{
    Segmento *n = malloc(sizeof(Segmento));
    n->n_segmento = n_segmento;
    n->reg_base = reg_base;
    n->tamanho = tamanho;
    return n;
}