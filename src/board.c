#include <stdio.h>
#include "board.h"

void mostrarTabuleiro(const Tabuleiro *tab) {
    for (int i = 0; i < tab->linhas; i++) {
        printf("%s\n", tab->grelha[i]);
    }
}
