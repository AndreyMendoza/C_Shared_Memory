#include "../headers/pagina.h"

void agregar_pagina(int * n_paginas, Pagina * memoria, int pag_logica, int pag_fisica)
{
    memoria[*n_paginas].pag_logica = pag_logica;
    memoria[*n_paginas].pag_fisica = pag_fisica;
    (*n_paginas)++;
}