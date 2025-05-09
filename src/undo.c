#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "board.h"
#include "undo.h"

void inicializar_historico(Historico *hist)
{
    hist->topo = 0;
}

bool guardar_estado(Historico *hist, Tabuleiro *tabAtual)
{
    if (hist == NULL || tabAtual == NULL)
    {
        return false;
    }

    if (hist->topo < MAX_HISTORY)
    {
        hist->estados[hist->topo++] = *tabAtual;
        return true;
    }

    return false;
}

bool desfazer(Historico *hist, Tabuleiro *tabAtual, Tabuleiro *tabIO, const char *coord)
{
    if (hist->topo == 0)
        return false;
    if (coord == NULL)
    {
        hist->topo--;
        int i;
        for (i = 0; i < hist->estados[hist->topo].linhas; i++)
        {
            strcpy(tabAtual->grelha[i], hist->estados[hist->topo].grelha[i]);
        }
        tabAtual->linhas = hist->estados[hist->topo].linhas;
        tabAtual->colunas = hist->estados[hist->topo].colunas;

        return true;
    }

    int col = tolower(coord[0]) - 'a';
    int row = atoi(coord + 1) - 1;

    if (tabAtual->grelha[row][col] != tabIO->grelha[row][col])
    {
        if (guardar_estado(hist, tabAtual))
        {
            tabAtual->grelha[row][col] = tabIO->grelha[row][col];
            return true;
        }
        return false;
    }

    return false;
}