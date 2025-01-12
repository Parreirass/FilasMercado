#include "../include/cliente.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Cliente* criar_cliente(const char* nome, int cpf, int prioridade, int numero_itens) {
    Cliente* novo_cliente = (Cliente*)malloc(sizeof(Cliente));
    if (novo_cliente) {
        strncpy(novo_cliente->nome, nome, MAX_NOME);
        novo_cliente->cpf = cpf;
        novo_cliente->prioridade = prioridade;
        novo_cliente->numero_itens = numero_itens;
        novo_cliente->proximo = NULL;
    }
    return novo_cliente;
}

void imprimir_cliente(const Cliente* cliente) {
    if (cliente) {
        printf("Nome: %s\n", cliente->nome);
        printf("CPF: %d\n", cliente->cpf);
        printf("Prioridade: %d\n", cliente->prioridade);
        printf("Numero de Itens: %d\n", cliente->numero_itens);
    }
}

void liberar_cliente(Cliente* cliente) {
    free(cliente);
}