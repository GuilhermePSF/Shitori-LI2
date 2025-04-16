#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "game.h"

void modificarTabuleiro(Tabuleiro *tab, Historico *hist, char cmd, const char *coord) {
    // Validate coordinate format first (should be a letter followed by a number)
    if (coord == NULL || !isalpha(coord[0]) || !isdigit(coord[1])) {
        printf("Formato de coordenada inválido. Use letra seguida de número (ex: a1).\n");
        return;
    }
    
    int linha = atoi(&coord[1]) - 1;
    int coluna = tolower(coord[0]) - 'a';

    if (linha < 0 || linha >= tab->linhas || coluna < 0 || coluna >= tab->colunas) {
        printf("Coordenada inválida.\n");
        return;
    }
}

    guardar_estado(hist, tab);

    if (cmd == 'b') {
        tab->grelha[linha][coluna] = toupper(tab->grelha[linha][coluna]);
    } else if (cmd == 'r') {
        tab->grelha[linha][coluna] = '#';
    }

    mostrarTabuleiro(tab);
}
