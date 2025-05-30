#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <board.h>
#include "io.h"

#define BOARD_DIR "boards/"

#include <stdbool.h>

bool carregarTabuleiro(Tabuleiro *tabAtual, Tabuleiro *tabIO, Historico *hist, char *ficheiro)
{
    char caminho[512];
    int len = snprintf(caminho, sizeof(caminho), "%s%s", BOARD_DIR, ficheiro);
    if (len < 0 || (size_t)len >= sizeof(caminho))
        return false;

    FILE *f = fopen(caminho, "r");
    if (!f)
        return false;

    if (fscanf(f, "%d %d\n", &tabAtual->linhas, &tabAtual->colunas) != 2 ||
        tabAtual->linhas <= 0 || tabAtual->linhas > MAX_SIDE ||
        tabAtual->colunas <= 0 || tabAtual->colunas > MAX_SIDE)
    {
        fclose(f);
        return false;
    }

    for (int i = 0; i < tabAtual->linhas; i++)
    {
        if (!fgets(tabAtual->grelha[i], tabAtual->colunas + 2, f))
        {
            fclose(f);
            return false;
        }

        int lenLinha = strlen(tabAtual->grelha[i]);
        if (lenLinha > 0 && tabAtual->grelha[i][lenLinha - 1] == '\n')
            tabAtual->grelha[i][lenLinha - 1] = '\0';

        if ((int)strlen(tabAtual->grelha[i]) != tabAtual->colunas)
        {
            fclose(f);
            return false;
        }
    }

    fclose(f);

    tabIO->linhas = tabAtual->linhas;
    tabIO->colunas = tabAtual->colunas;
    for (int i = 0; i < tabAtual->linhas; i++)
    {
        strcpy(tabIO->grelha[i], tabAtual->grelha[i]);
    }

    hist->topo = 0;
    return true;
}

bool gravarTabuleiro(Tabuleiro *tabAtual, char *ficheiro)
{
    char caminho[512];
    int len = snprintf(caminho, sizeof(caminho), "%s%s", BOARD_DIR, ficheiro);
    if (len < 0 || (size_t)len >= sizeof(caminho))
        return false;

    FILE *f = fopen(caminho, "w");
    if (!f)
        return false;

    if (fprintf(f, "%d %d\n", tabAtual->linhas, tabAtual->colunas) < 0)
    {
        fclose(f);
        return false;
    }

    for (int i = 0; i < tabAtual->linhas; i++)
    {
        if (fprintf(f, "%s\n", tabAtual->grelha[i]) < 0)
        {
            fclose(f);
            return false;
        }
    }

    fclose(f);
    return true;
}