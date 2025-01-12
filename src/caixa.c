// caixa.c
#include "caixa.h"
#include <stdlib.h>
#include <stdio.h>

Caixa* criar_caixa(int id) {
    Caixa* novo_caixa = (Caixa*)malloc(sizeof(Caixa));
    if (novo_caixa) {
        novo_caixa->id = id;
        novo_caixa->aberto = 1;
        novo_caixa->fila = NULL;
    }
    return novo_caixa;
}

void abrir_caixa(Caixa* caixa) {
    if (caixa) {
        caixa->aberto = 1;
    }
}

void fechar_caixa(Caixa* caixa) {
    if (caixa) {
        caixa->aberto = 0;
    }
}

void imprimir_status_caixa(const Caixa* caixa) {
    if (caixa) {
        printf("Caixa %d: %s\n", caixa->id, caixa->aberto ? "Aberto" : "Fechado");
    }
}

void adicionar_cliente_caixa(Caixa* caixa, Cliente* cliente) {
    if (caixa && cliente) {
        Cliente* atual = caixa->fila;
        if (!atual) {
            caixa->fila = cliente;
        } else {
            while (atual->proximo) {
                atual = atual->proximo;
            }
            atual->proximo = cliente;
        }
    }
}

Cliente* atender_cliente_caixa(Caixa* caixa) {
    if (caixa && caixa->fila) {
        Cliente* cliente_atendido = caixa->fila;
        caixa->fila = cliente_atendido->proximo;
        return cliente_atendido;
    }
    return NULL;
}

void liberar_caixa(Caixa* caixa) {
    if (caixa) {
        Cliente* atual = caixa->fila;
        while (atual) {
            Cliente* proximo = atual->proximo;
            liberar_cliente(atual);
            atual = proximo;
        }
        free(caixa);
    }
}