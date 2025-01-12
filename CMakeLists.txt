cmake_minimum_required(VERSION 3.10)

# Nome do projeto
project(SistemaFilasSupermercado C)

# Adiciona os diretórios com os arquivos-fonte
include_directories(include)

# Adiciona os arquivos-fonte
add_executable(SistemaFilasSupermercado
    src/main.c
    src/cliente.c
    src/caixa.c
    src/fila_prioridade.c
    src/utils.c
)

# Especifica o padrão de C para o compilador
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)
