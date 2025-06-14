#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include "game.h"
#include "verifica.h"

bool modificarTabuleiro(Tabuleiro *tabAtual, Historico *hist, char cmd, const char *coord)
{
    int linha = atoi(&coord[1]) - 1;
    int coluna = tolower(coord[0]) - 'a';

    if (linha < 0 || linha >= tabAtual->linhas || coluna < 0 || coluna >= tabAtual->colunas)
    {
        printf("\\033[1;31m ⚠ Coordenada inválida. ⚠ \n\033[0m");
        return false;
    }

    if (!guardar_estado(hist, tabAtual))
    {
        return false;
    }

    if (cmd == 'b')
    {
        if (tabAtual->grelha[linha][coluna] == '#')
        {
            return false;
        }

        tabAtual->grelha[linha][coluna] = toupper(tabAtual->grelha[linha][coluna]);
    }

    else if (cmd == 'r')
    {
        if (isupper(tabAtual->grelha[linha][coluna]))
        {
            return false;
        }
        tabAtual->grelha[linha][coluna] = '#';
    }
    else
    {
        return false;
    }

    return true;
}

bool ganhou(Tabuleiro *tabAtual)
{
    for (int i = 0; i < tabAtual->linhas; i++)
    {
        for (int j = 0; j < tabAtual->colunas; j++)
        {
            if (islower(tabAtual->grelha[i][j]) && isalpha(tabAtual->grelha[i][j]))
            {
                return false;
            }
        }
    }
    return true && verificarRestricoes(tabAtual, false);
}