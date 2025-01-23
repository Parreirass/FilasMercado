#ifndef FILA_PRIORIDADE_H
#define FILA_PRIORIDADE_H

#include "cliente.h"

typedef struct Nodo {
    Cliente cliente;
    struct Nodo* proximo;
} Nodo;

typedef struct {
    Nodo* frente;
} FilaPrioridade;

void inicializar_fila(FilaPrioridade* fila);
void adicionar_cliente(FilaPrioridade* fila, Cliente cliente);
Cliente atender_cliente_prioridade(FilaPrioridade* fila);
int esta_vazia(FilaPrioridade* fila);

#endif // FILA_PRIORIDADE_H