// caixa.h
#ifndef CAIXA_H
#define CAIXA_H

#include "cliente.h"

typedef struct Caixa {
    int id;
    int aberto;
    Cliente* fila;
} Caixa;

Caixa* criar_caixa(int id);
void abrir_caixa(Caixa* caixa);
void fechar_caixa(Caixa* caixa);
void imprimir_status_caixa(const Caixa* caixa);
void adicionar_cliente_caixa(Caixa* caixa, Cliente* cliente);
Cliente* atender_cliente_caixa(Caixa* caixa);
void liberar_caixa(Caixa* caixa);

#endif // CAIXA_H