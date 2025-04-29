#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <board.h>
#include "io.h"

#define BOARD_DIR "boards/"

int carregarTabuleiro(Tabuleiro *tabAtual, Historico *hist, char *ficheiro)
{
    char caminho[512];
    int len = snprintf(caminho, sizeof(caminho), "%s%s", BOARD_DIR, ficheiro);
    if (len < 0 || (size_t)len >= sizeof(caminho))
        return -2;

    FILE *f = fopen(caminho, "r");
    if (!f)
        return -1;

    if (fscanf(f, "%d %d\n", &tabAtual->linhas, &tabAtual->colunas) != 2 ||
        tabAtual->linhas <= 0 || tabAtual->linhas > MAX_SIDE ||
        tabAtual->colunas <= 0 || tabAtual->colunas > MAX_SIDE)
    {
        fclose(f);
        return -3;
    }

    for (int i = 0; i < tabAtual->linhas; i++)
    {
        if (!fgets(tabAtual->grelha[i], tabAtual->colunas + 2, f))
        {
            fclose(f);
            return -1;
        }

        size_t len = strlen(tabAtual->grelha[i]);
        if (len > 0 && tabAtual->grelha[i][len - 1] == '\n')
            tabAtual->grelha[i][len - 1] = '\0';

        if ((int)strlen(tabAtual->grelha[i]) != tabAtual->colunas)
        {
            fclose(f);
            return -4;
        }
    }

    fclose(f);
    hist->topo = 0;
    mostrarTabuleiro(tabAtual);
    return 0;
}

int gravarTabuleiro(Tabuleiro *tabAtual, char *ficheiro)
{
    char caminho[512];
    int len = snprintf(caminho, sizeof(caminho), "%s%s", BOARD_DIR, ficheiro);
    if (len < 0 || (size_t)len >= sizeof(caminho))
        return -2;

    FILE *f = fopen(caminho, "w");
    if (!f)
        return -1;

    if (fprintf(f, "%d %d\n", tabAtual->linhas, tabAtual->colunas) < 0)
    {
        fclose(f);
        return -3;
    }

    for (int i = 0; i < tabAtual->linhas; i++)
    {
        if (fprintf(f, "%s\n", tabAtual->grelha[i]) < 0)
        {
            fclose(f);
            return -3;
        }
    }

    fclose(f);
    return 0;
}