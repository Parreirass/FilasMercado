#include <stdlib.h>
#include "fila_prioridade.h"

void inicializar_fila(FilaPrioridade* fila) {
    fila->frente = NULL;
}

void adicionar_cliente(FilaPrioridade* fila, Cliente cliente) {
    Nodo* novo_nodo = (Nodo*)malloc(sizeof(Nodo));
    novo_nodo->cliente = cliente;
    novo_nodo->proximo = NULL;

    if (fila->frente == NULL || cliente.prioridade < fila->frente->cliente.prioridade) {
        novo_nodo->proximo = fila->frente;
        fila->frente = novo_nodo;
    } else {
        Nodo* atual = fila->frente;
        while (atual->proximo != NULL && atual->proximo->cliente.prioridade <= cliente.prioridade) {
            atual = atual->proximo;
        }
        novo_nodo->proximo = atual->proximo;
        atual->proximo = novo_nodo;
    }
}

Cliente atender_cliente_prioridade(FilaPrioridade* fila) {
    if (fila->frente == NULL) {
        Cliente vazio = {"", 0, 0, 0};
        return vazio;
    }

    Nodo* temp = fila->frente;
    Cliente cliente = temp->cliente;
    fila->frente = fila->frente->proximo;
    free(temp);
    return cliente;
}

int esta_vazia(FilaPrioridade* fila) {
    return fila->frente == NULL;
}
