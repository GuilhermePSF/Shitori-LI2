#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "board.h"
#include "undo.h"

void guardar_estado(Historico *hist, Tabuleiro *tabAtual)
{
    if (hist == NULL || tabAtual == NULL)
    {
        return;
    }

    if (hist->topo < MAX_HISTORY)
    {
        hist->estados[hist->topo++] = *tabAtual;
    }
    else
    {
        printf("Aviso: Histórico cheio, não é possível guardar mais estados.\n");
    }
}

int desfazer(Historico *hist, Tabuleiro *tabAtual, Tabuleiro *tabIO, const char *coord)
{
    if (coord == NULL)
    {
        if (hist->topo == 0)
        {
            printf("Não há movimentos para desfazer.\n");
            return -1;
        }

        hist->topo--;
        int i;
        for (i = 0; i < hist->estados[hist->topo].linhas; i++)
        {
            strcpy(tabAtual->grelha[i], hist->estados[hist->topo].grelha[i]);
        }
        tabAtual->linhas = hist->estados[hist->topo].linhas;
        tabAtual->colunas = hist->estados[hist->topo].colunas;

        mostrarTabuleiro(tabAtual);
        return 0;
    }

    if (strlen(coord) < 2 || !isalpha(coord[0]) || !isdigit(coord[1]))
    {
        printf("Coordenada inválida.\n");
        return -1;
    }

    int col = tolower(coord[0]) - 'a';
    int row = atoi(coord + 1) - 1;

    if (row < 0 || row >= tabAtual->linhas || col < 0 || col >= tabAtual->colunas)
    {
        printf("Coordenada fora dos limites.\n");
        return -1;
    }

    if (tabAtual->grelha[row][col] != tabIO->grelha[row][col])
    {
        guardar_estado(hist, tabAtual);
        tabAtual->grelha[row][col] = tabIO->grelha[row][col];
        mostrarTabuleiro(tabAtual);
        return 0;
    }
    printf("Não há modificacoes para desfazer.\n");
    return 1;
}