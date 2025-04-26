#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "io.h"

#define BOARD_DIR "boards/"
#define MAX_LINHAS 128
#define MAX_COLUNAS 26

int carregarTabuleiro(Tabuleiro *tab, Historico *hist, char *ficheiro)
{
    char caminho[512];
    int len = snprintf(caminho, sizeof(caminho), "%s%s", BOARD_DIR, ficheiro);
    if (len < 0 || (size_t)len >= sizeof(caminho))
        return -2;

    FILE *f = fopen(caminho, "r");
    if (!f)
        return -1;

    if (fscanf(f, "%d %d\n", &tab->linhas, &tab->colunas) != 2 ||
        tab->linhas <= 0 || tab->linhas > MAX_LINHAS ||
        tab->colunas <= 0 || tab->colunas > MAX_COLUNAS)
    {
        fclose(f);
        return -3;
    }

    for (int i = 0; i < tab->linhas; i++)
    {
        if (!fgets(tab->grelha[i], tab->colunas + 2, f))
        {
            fclose(f);
            return -1;
        }

        size_t len = strlen(tab->grelha[i]);
        if (len > 0 && tab->grelha[i][len - 1] == '\n')
            tab->grelha[i][len - 1] = '\0';

        if ((int)strlen(tab->grelha[i]) != tab->colunas)
        {
            fclose(f);
            return -4;
        }
    }

    fclose(f);
    hist->topo = 0;
    mostrarTabuleiro(tab);
    return 0;
}

int gravarTabuleiro(Tabuleiro *tab, char *ficheiro)
{
    char caminho[512];
    int len = snprintf(caminho, sizeof(caminho), "%s%s", BOARD_DIR, ficheiro);
    if (len < 0 || (size_t)len >= sizeof(caminho))
        return -2;

    FILE *f = fopen(caminho, "w");
    if (!f)
        return -1;

    if (fprintf(f, "%d %d\n", tab->linhas, tab->colunas) < 0)
    {
        fclose(f);
        return -3;
    }

    for (int i = 0; i < tab->linhas; i++)
    {
        if (fprintf(f, "%s\n", tab->grelha[i]) < 0)
        {
            fclose(f);
            return -3;
        }
    }

    fclose(f);
    return 0;
}