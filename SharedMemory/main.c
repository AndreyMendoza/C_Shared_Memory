#include "headers/imports.h"


int main(int argc, char **argv) {

    printf("\n");
    puts("************************** INICIO DEL PROGRAMA ***************************");
    printf("\n");


    char * modo_programa = basename(argv[0]);


    if (strcmp(modo_programa, "inic") == 0)
    {
        /*Cantidad de espacios de memoria que va haber*/
        int size = 2048;
        inicializar(size);
    }

    else if (strcmp(modo_programa, "prod") == 0)
        producir(atoi(argv[1]));

    else if (strcmp(modo_programa, "espia") == 0)
        espiar();

    else if (strcmp(modo_programa, "fin") == 0)
        finalizar();


    printf("\n");
    puts("**************************** FIN DEL PROGRAMA ****************************");


    return 0;
}