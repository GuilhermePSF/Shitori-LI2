#include "solver.h"
#include "board.h"
#include "undo.h"
#include "verifica.h"
#include "tip.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>

bool regras1ou2(Tabuleiro *tabAtual, int linha, int coluna)
{
    char alvo = tabAtual->grelha[linha][coluna];
    if (coluna != 0 && coluna != tabAtual->colunas - 1)
    {
        char esq = tabAtual->grelha[linha][coluna - 1];
        char dir = tabAtual->grelha[linha][coluna + 1];
        if ((alvo == esq && alvo == dir) || (esq == dir && alvo != esq))
            return true;
    }
    if (linha != 0 && linha != tabAtual->linhas - 1)
    {
        char cima = tabAtual->grelha[linha - 1][coluna];
        char baixo = tabAtual->grelha[linha + 1][coluna];
        if ((alvo == cima && alvo == baixo) || (cima == baixo && alvo != cima))
            return true;
    }
    return false;
}

// Regra 3 - Par adjacente + instância separada signfica riscar
bool regra3_horizontal(Tabuleiro *tabAtual, int linha, int coluna)
{
    char alvo = tabAtual->grelha[linha][coluna];
    if ((coluna == 0 || alvo != tabAtual->grelha[linha][coluna - 1]) && (coluna == tabAtual->colunas - 1 || alvo != tabAtual->grelha[linha][coluna + 1]))
    {
        for (int j = 0; j < tabAtual->colunas - 1; j++)
        {
            if (alvo == tabAtual->grelha[linha][j] && alvo == tabAtual->grelha[linha][j + 1])
            {
                return true;
            }
        }
    }
    return false;
}

bool regra3_vertical(Tabuleiro *tabAtual, int linha, int coluna)
{
    char alvo = tabAtual->grelha[linha][coluna];
    if ((linha == 0 || alvo != tabAtual->grelha[linha - 1][coluna]) && (linha == tabAtual->linhas - 1 || alvo != tabAtual->grelha[linha + 1][coluna]))
    {
        for (int i = 0; i < tabAtual->linhas - 1; i++)
        {
            if (alvo == tabAtual->grelha[i][coluna] && alvo == tabAtual->grelha[i + 1][coluna])
            {
                return true;
            }
        }
    }
    return false;
}

void tecnicas_iniciais(Tabuleiro *tabAtual, Historico *hist) // cccac
{
    for (int i = 0; i < tabAtual->linhas; i++)
    {
        for (int j = 0; j < tabAtual->colunas; j++)
        {
            char atual = tabAtual->grelha[i][j];
            if (islower(atual))
            {
                if (regras1ou2(tabAtual, i, j))
                {
                    guardar_estado(hist, tabAtual);
                    tabAtual->grelha[i][j] = toupper(atual);
                }
                if (regra3_horizontal(tabAtual, i, j) || regra3_vertical(tabAtual, i, j))
                {
                    guardar_estado(hist, tabAtual);
                    tabAtual->grelha[i][j] = '#';
                }
            }
        }
    }
}

bool ser_valido(Tabuleiro *tabAtual, int l, int c, char sub)
{
    bool r;
    char original = tabAtual->grelha[l][c];
    tabAtual->grelha[l][c] = sub;
    if (sub == '#')
    {
        r = !tem_riscado_adjacente_coord(tabAtual, l, c) && verificarConectividade(tabAtual, 's');
    }
    else
    {
        r = !existe_maiuscula_igual_na_linha_ou_coluna(tabAtual, l, c);
    }
    tabAtual->grelha[l][c] = original;
    return r;
}
bool solve(Tabuleiro *tabAtual, int l, int c, bool modo)
{

    if (l == tabAtual->linhas)
    {
        return true;
    }
    else if (c == tabAtual->colunas)
    {
        return (solve(tabAtual, l + 1, 0, modo));
    }
    else if (!('a' <= tabAtual->grelha[l][c] && tabAtual->grelha[l][c] <= 'z'))
    {
        return (solve(tabAtual, l, c + 1, modo));
    }
    else
    {
        if (modo)
        {
            mostrarTabuleiro(tabAtual);
            usleep(10000);
            if ((system("clear")))
                printf("\033[1;31m ⚠ failed to clean ⚠ \n\033[0m");
        }
        if (ser_valido(tabAtual, l, c, toupper(tabAtual->grelha[l][c])))
        {
            char original = tabAtual->grelha[l][c];
            tabAtual->grelha[l][c] = toupper(tabAtual->grelha[l][c]);
            if (solve(tabAtual, l, c + 1, modo))
            {
                return true;
            }
            tabAtual->grelha[l][c] = original;
        }
        if (ser_valido(tabAtual, l, c, '#'))
        {
            char original = tabAtual->grelha[l][c];
            tabAtual->grelha[l][c] = '#';
            if (solve(tabAtual, l, c + 1, modo))
            {
                return true;
            }
            tabAtual->grelha[l][c] = original;
        }
        return false;
    }
}

void comando_R(Tabuleiro *tabAtual, Tabuleiro *tabIO, Historico *hist, bool modo)
{
    Tabuleiro tabOriginal = copiar_tabuleiro(&hist->estados[0]);

    Historico histTemp;
    inicializar_historico(&histTemp);

    tecnicas_iniciais(&tabOriginal, &histTemp);
    comando_A(&tabOriginal, tabIO, &histTemp);
    solve(&tabOriginal, 0, 0, modo);

    copiar_tabuleiro_para(&tabOriginal, tabAtual);
}
