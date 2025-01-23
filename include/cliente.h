#ifndef CLIENTE_H
#define CLIENTE_H

#define MAX_NOME 100

typedef struct Cliente {
    char nome[MAX_NOME];
    int cpf; // 11 dígitos + 1 para o terminador null
    int prioridade;
    int numero_itens;
    struct Cliente* proximo;
} Cliente;

Cliente* criar_cliente(const char* nome, int cpf, int prioridade, int numero_itens);
void imprimir_cliente(const Cliente* cliente);
void liberar_cliente(Cliente* cliente);

#endif // CLIENTE_H