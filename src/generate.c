#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <ctype.h>
#include <time.h>
#include "board.h"
#include "io.h"
#include "game.h"
#include "undo.h"
#include "verifica.h"
#include "solver.h"
#include "tip.h"
#include "generate.h"

char random_letra_minuscula(int side)
{
    return 'a' + (rand() % side);
}

void inicializarGerador(Tabuleiro *tab)
{
    for (int i = 0; i < tab->linhas; i++)
    {
        for (int j = 0; j < tab->colunas; j++)
        {
            tab->grelha[i][j] = '-';
        }
    }
}

void preencherGerador(Tabuleiro *tab)
{
    for (int i = 0; i < tab->linhas; i++)
    {
        for (int j = 0; j < tab->colunas; j++)
        {
            tab->grelha[i][j] = random_letra_minuscula(tab->colunas < tab->linhas ? tab->colunas : tab->linhas);
            ;
        }
    }
}

bool valida_quatro(Tabuleiro *tab, int l, int c, char letra)
{
    int count = 0;

    for (int j = 0; j < c; j++)
    {
        if (tab->grelha[l][j] == letra)
            count++;
    }
    if (count >= 3)
        return false;

    count = 0;

    for (int i = 0; i < l; i++)
    {
        if (tab->grelha[i][c] == letra)
            count++;
    }
    if (count >= 3)
        return false;

    return true;
}

bool ser_resolvivel(Tabuleiro *tab, int l, int c, char sub)
{
    Tabuleiro tabOriginal = copiar_tabuleiro(tab);

    Historico histTemp;
    inicializar_historico(&histTemp);

    tab->grelha[l][c] = sub;

    tecnicas_iniciais(&tabOriginal, &histTemp);
    comando_A(&tabOriginal, NULL, &histTemp);
    bool r = solve(&tabOriginal, 0, 0, false);

    return r;
}

bool generate(Tabuleiro *tab)
{
    Tabuleiro tabOriginal;
    bool stop_ciclo = false;
    while (!stop_ciclo)
    {
        inicializarGerador(tab);
        preencherGerador(tab);
        Historico histTemp;
        inicializar_historico(&histTemp);
        tabOriginal = copiar_tabuleiro(tab);
        tecnicas_iniciais(&tabOriginal, &histTemp);
        comando_A(&tabOriginal, NULL, &histTemp);
        stop_ciclo = solve(&tabOriginal, 0, 0, false);
    }
}

/* bool generate(Tabuleiro *tab, int l, int c)
{
    int margem = tab->colunas < tab->linhas ? tab->colunas : tab->linhas;

    if (l == tab->linhas)
    {
        return true;
    }
    else if (c == tab->colunas)
    {
        return (generate(tab, l + 1, 0));
    }
    else if (tab->grelha[l][c] != '-')
    {
        return (generate(tab, l, c + 1));
    }
    else
    {
        mostrarTabuleiro(tab);
        usleep(4000);
        if ((system("clear")))
            printf("\033[1;31m ⚠ failed to clean ⚠ \n\033[0m");

        char substituto = random_letra_minuscula(margem);
        int count = 0;

        while (count != margem * 20 && !(ser_resolvivel(tab, l, c, substituto) && valida_quatro(tab, l, c, substituto)))
        {
            count++;
            substituto = random_letra_minuscula(tab->colunas < tab->linhas ? tab->colunas : tab->linhas);
        }
        if (ser_resolvivel(tab, l, c, substituto) && valida_quatro(tab, l, c, substituto))
        {
            tab->grelha[l][c] = substituto;
            if (generate(tab, l, c + 1))
            {
                return true;
            }
        }
        tab->grelha[l][c] = '-';

        return false;
    }
} */