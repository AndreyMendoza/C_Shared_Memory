#ifndef SHAREDMEMORY_LIST_H
#define SHAREDMEMORY_LIST_H

#include "imports.h"

typedef struct Node {
    struct Node *next, *prev;
    void *data;
}Node;

typedef struct List {
    Node *head, *tail;
    long size;
}List;



Node *new_node(void *);                                              // Crea un nodo
List *new_list(void);                                                // Crea una lista
void add(List *list, void *data);                                   // Agrega un nodo al final de la lista
void push(List *list, void *data);                                  // Agrega un noto al inicio de la lista
void *peek(List *list);                                             // Retorna la informacion de la cabeza de la lista
void *pop(List *list);                                              // Elimina el ultimo elemento de la lista
void print_list(List *list, int (*func)(const char *, ...));          // Muestra el contenido de la lista

#endif //SHAREDMEMORY_LIST_H
