#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "io.h"

#define BOARD_DIR "boards/"
#define MAX_LINHAS 128
#define MAX_COLUNAS 26

int carregarTabuleiro(Tabuleiro *tab, Historico *hist, const char *ficheiro)
{
    char caminho[512];
    snprintf(caminho, sizeof(caminho), "%s%s", BOARD_DIR, ficheiro);
    if (strlen(BOARD_DIR) + strlen(ficheiro) >= sizeof(caminho))
    {
        return -2;
    }
    FILE *f = fopen(caminho, "r");
    if (!f)
        return -1;

    if (fscanf(f, "%d %d", &tab->linhas, &tab->colunas) != 2)
    {
        fclose(f);
        return -1;
    }

    if (tab->linhas <= 0 || tab->linhas > MAX_LINHAS ||
        tab->colunas <= 0 || tab->colunas > MAX_COLUNAS)
    {
        fclose(f);
        return -3;
    }

    for (int i = 0; i < tab->linhas; i++)
    {
        if (fscanf(f, "%s", tab->grelha[i]) != 1)
        {
            fclose(f);
            return -1;
        }

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

int gravarTabuleiro(const Tabuleiro *tab, const char *ficheiro)
{
    char caminho[512];
    snprintf(caminho, sizeof(caminho), "%s%s", BOARD_DIR, ficheiro);

    if (strlen(BOARD_DIR) + strlen(ficheiro) >= sizeof(caminho))
    {
        return -2;
    }
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
