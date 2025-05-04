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
    else
    {
        printf("Aviso: Histórico cheio, não é possível guardar mais estados.\n");
        return false;
    }
}

bool desfazer(Historico *hist, Tabuleiro *tabAtual, Tabuleiro *tabIO, const char *coord)
{
    if (coord == NULL)
    {
        if (hist->topo == 0)
        {
            printf("Não há movimentos para desfazer.\n");
            return false;
        }

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

    if (strlen(coord) < 2 || !isalpha(coord[0]) || !isdigit(coord[1]))
    {
        printf("Coordenada inválida.\n");
        return false;
    }

    int col = tolower(coord[0]) - 'a';
    int row = atoi(coord + 1) - 1;

    if (row < 0 || row >= tabAtual->linhas || col < 0 || col >= tabAtual->colunas)
    {
        printf("Coordenada fora dos limites.\n");
        return false;
    }

    if (tabAtual->grelha[row][col] != tabIO->grelha[row][col])
    {
        if (guardar_estado(hist, tabAtual))
        {
            tabAtual->grelha[row][col] = tabIO->grelha[row][col];
            return true;
        }
        return false;
    }
    printf("Não há modificacoes para desfazer.\n");
    return false;
}