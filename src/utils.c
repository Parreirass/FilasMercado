#include <stdio.h>
#include "utils.h"

void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void pause() {
    printf("Pressione Enter para continuar...");
    limpar_buffer();
}
