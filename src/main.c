#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/caixa.h"
#include "../include/cliente.h"
#include "../include/fila_prioridade.h"
#include "../include/utils.h"

#define NUM_CAIXAS 5

void cadastrar_cliente(FilaPrioridade caixas[], Caixa info_caixas[], int num_caixas);
void atender_cliente(Caixa caixas[], FilaPrioridade filas[], int num_caixas);
void abrir_fechar_caixa(Caixa caixas[], FilaPrioridade filas[], int num_caixas);
void imprimir_clientes(FilaPrioridade caixas[], int num_caixas);
void imprimir_status_caixas(Caixa caixas[], int num_caixas);

int main() {
    FilaPrioridade filas[NUM_CAIXAS];
    Caixa caixas[NUM_CAIXAS];
    int opcao;

    // Inicializa as filas e caixas
    for (int i = 0; i < NUM_CAIXAS; i++) {
        inicializar_fila(&filas[i]);
        caixas[i].id = i + 1;
        caixas[i].aberto = 1; // Aberto
    }

    do {
        printf("\nSistema de Gerenciamento de Filas\n");
        printf("1. Cadastrar um Cliente\n");
        printf("2. Atender um Cliente\n");
        printf("3. Abrir ou Fechar um Caixa\n");
        printf("4. Imprimir a Lista de Clientes em Espera\n");
        printf("5. Imprimir o Status dos Caixas\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limpar_buffer();

        switch (opcao) {
            case 1:
                cadastrar_cliente(filas, caixas, NUM_CAIXAS);
                break;
            case 2:
                atender_cliente(caixas, filas, NUM_CAIXAS);
                break;
            case 3:
                abrir_fechar_caixa(caixas, filas, NUM_CAIXAS);
                break;
            case 4:
                imprimir_clientes(filas, NUM_CAIXAS);
                break;
            case 5:
                imprimir_status_caixas(caixas, NUM_CAIXAS);
                break;
            case 0:
                printf("Encerrando o sistema...\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }

        if (opcao != 0) pause();
    } while (opcao != 0);

    return 0;
}

// Funcoes de implementacao

void cadastrar_cliente(FilaPrioridade caixas[], Caixa info_caixas[], int num_caixas) {
    Cliente cliente;
    int caixa_escolhido;

    printf("Nome do cliente: ");
    fgets(cliente.nome, 100, stdin);
    strtok(cliente.nome, "\n"); // Remove o \n no final da string
    printf("CPF (somente numeros): ");
    scanf("%d", &cliente.cpf);
    limpar_buffer();
    printf("Prioridade (1-Alta, 2-Media, 3-Baixa): ");
    scanf("%d", &cliente.prioridade);
    limpar_buffer();
    printf("Numero de itens no carrinho: ");
    scanf("%d", &cliente.numero_itens);
    limpar_buffer();
    printf("Escolha o caixa (1 a %d): ", num_caixas);
    scanf("%d", &caixa_escolhido);
    limpar_buffer();

    if (caixa_escolhido < 1 || caixa_escolhido > num_caixas) {
        printf("Caixa invalido.\n");
        return;
    }

    if (info_caixas[caixa_escolhido - 1].aberto == 2) {
        printf("O caixa escolhido esta fechado. Cliente nao cadastrado.\n");
        return;
    }

    adicionar_cliente(&caixas[caixa_escolhido - 1], cliente);
    printf("Cliente cadastrado com sucesso!\n");
}

void atender_cliente(Caixa caixas[], FilaPrioridade filas[], int num_caixas) {
    int caixa_escolhido;
    printf("Escolha o caixa para atendimento (1 a %d): ", num_caixas);
    scanf("%d", &caixa_escolhido);
    limpar_buffer();

    if (caixa_escolhido < 1 || caixa_escolhido > num_caixas) {
        printf("Caixa invalido.\n");
        return;
    }

    if (caixas[caixa_escolhido - 1].aberto == 0) {
        printf("O caixa escolhido esta fechado.\n");
        return;
    }

    Cliente* cliente = atender_cliente_caixa(&caixas[caixa_escolhido - 1]);
    if (cliente != NULL && strlen(cliente->nome) > 0) {
        printf("Atendendo cliente: %s, CPF: %d\n", cliente->nome, cliente->cpf);
    } else {
        printf("Nenhum cliente na fila.\n");
    }
}

void abrir_fechar_caixa(Caixa caixas[], FilaPrioridade filas[], int num_caixas) {
    int caixa_escolhido, novo_estado;
    int numero_caixas_passado = 0;

    printf("Escolha o caixa para abrir/fechar (1 a %d): ", num_caixas);
    scanf("%d", &caixa_escolhido);
    limpar_buffer();

    if (caixa_escolhido < 1 || caixa_escolhido > num_caixas) {
        printf("Caixa invalido.\n");
        return;
    }

    printf("1. Abrir\n2. Fechar\nEscolha a nova situacao: ");
    scanf("%d", &novo_estado);
    limpar_buffer();

    if (novo_estado == 1 || novo_estado == 2) {
        if(caixas[caixa_escolhido -1].aberto == 1 && novo_estado == 1) {
            printf("\nCaixa já está aberto e continua aberto!\n");
            return;
        }
        else if(caixas[caixa_escolhido -1].aberto == 2 && novo_estado == 2) {
            printf("\nCaixa já está fechado e continua fechado!\n");
            return;
        }
        caixas[caixa_escolhido - 1].aberto = novo_estado;
        if (novo_estado == 2) {
            Nodo* atual = filas[caixa_escolhido - 1].frente;
            // Verificar se há clientes para realocar
            if (atual == NULL) {
                printf("Nenhum cliente para realocar.\n");
            }
            else {
                printf("Realocando clientes para outros caixas abertos...\n");
                for (int i = 0; i < num_caixas; i++) {
                    //printf("\ncaixa atual: %d - situacao dele: %d\n", i, caixas[i].aberto);
                    if (i != caixa_escolhido - 1 && caixas[i].aberto != 2) {
                        
                        Nodo* atual = filas[caixa_escolhido - 1].frente;
                        //printf("\natual: %d\n", *atual);
                        while (atual != NULL) {
                            adicionar_cliente(&filas[i], atual->cliente);
                            atual = atual->proximo;
                        }
                        inicializar_fila(&filas[caixa_escolhido - 1]);
                        
                        break;
                    }
                    else {
                        //printf("\ncaixas passados %d fechados!\n", numero_caixas_passado);
                        numero_caixas_passado ++;
                    }
                }
                if(numero_caixas_passado == 5) {
                    printf("\n ------------------------- TODOS OS CAIXAS ESTÃO FECHADOS! SUPERMERCADO FECHADO! -------------------------\n");
                    exit(0);
                }
            }
        }
        printf("Caixa atualizado.\n");
    } else {
        printf("Situacao invalida.\n");
    }
}

void imprimir_clientes(FilaPrioridade caixas[], int num_caixas) {
    for (int i = 0; i < num_caixas; i++) {
        printf("\nCaixa %d:\n", i + 1);
        if (esta_vazia(&caixas[i])) {
            printf("Nenhum cliente na fila.\n");
        } else {
            Nodo* atual = caixas[i].frente;
            while (atual != NULL) {
                Cliente c = atual->cliente;
                printf("Nome: %s, CPF: %d, Prioridade: %d, Itens: %d\n", c.nome, c.cpf, c.prioridade, c.numero_itens);
                atual = atual->proximo;
            }
        }
    }
}

void imprimir_status_caixas(Caixa caixas[], int num_caixas) {
    for (int i = 0; i < num_caixas; i++) {
        printf("Caixa %d: %s\n", caixas[i].id, caixas[i].aberto == 1 ? "Aberto" : "Fechado");
    }
}
