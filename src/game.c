#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "game.h"

void modificarTabuleiro(Tabuleiro *tab, Historico *hist, char cmd, const char *coord)
{
    int linha = atoi(&coord[1]) - 1;
    int coluna = tolower(coord[0]) - 'a';

    if (linha < 0 || linha >= tab->linhas || coluna < 0 || coluna >= tab->colunas)
    {
        printf("Coordenada inválida.\n");
        return;
    }

    guardar_estado(hist, tab);

    if (cmd == 'b')
    {
        tab->grelha[linha][coluna] = toupper(tab->grelha[linha][coluna]);
    }
    else if (cmd == 'r')
    {
        tab->grelha[linha][coluna] = '#';
    }

    mostrarTabuleiro(tab);
}
