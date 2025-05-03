#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "board.h"
#include "io.h"
#include "game.h"
#include "undo.h"
#include "verifica.h"
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

// TODO improve safety

bool tem_riscado_adjacente_coord(const Tabuleiro *tabAtual, int linha, int coluna)
{
    if (linha > 0 && tabAtual->grelha[linha - 1][coluna] == '#')
        return true;
    if (linha < tabAtual->linhas - 1 && tabAtual->grelha[linha + 1][coluna] == '#')
        return true;
    if (coluna > 0 && tabAtual->grelha[linha][coluna - 1] == '#')
        return true;
    if (coluna < tabAtual->colunas - 1 && tabAtual->grelha[linha][coluna + 1] == '#')
        return true;

    return false;
}

bool tem_riscado_adjacente(const Tabuleiro *tabAtual)
{
    for (int i = 0; i < tabAtual->linhas; i++)
    {
        for (int j = 0; j < tabAtual->colunas; j++)
        {
            if (tabAtual->grelha[i][j] == '#' && tem_riscado_adjacente_coord(tabAtual, i, j))
                return true;
        }
    }
    return false;
}

bool existe_maiuscula_igual_na_linha_ou_coluna(Tabuleiro *tabAtual, int linha, int coluna)
{
    char atual = tabAtual->grelha[linha][coluna];

    char alvo = toupper((unsigned char)atual);

    for (int j = 0; j < tabAtual->colunas; j++)
    {
        if (j != coluna && tabAtual->grelha[linha][j] == alvo && isupper((unsigned char)tabAtual->grelha[linha][j]))
        {
            return true;
        }
    }

    for (int i = 0; i < tabAtual->linhas; i++)
    {
        if (i != linha && tabAtual->grelha[i][coluna] == alvo && isupper((unsigned char)tabAtual->grelha[i][coluna]))
        {
            return true;
        }
    }

    return false;
}

bool existe_igual_na_linha_ou_coluna(Tabuleiro *tabAtual, int linha, int coluna)
{
    char atual = tabAtual->grelha[linha][coluna];

    for (int j = 0; j < tabAtual->colunas; j++)
    {
        if (j != coluna && (tabAtual->grelha[linha][j] == atual || tabAtual->grelha[linha][j] == toupper(atual)))
        {
            return true;
        }
    }

    for (int i = 0; i < tabAtual->linhas; i++)
    {
        if (i != linha && (tabAtual->grelha[i][coluna] == atual || tabAtual->grelha[i][coluna] == toupper(atual)))
        {
            return true;
        }
    }

    return false;
}

bool tem_maiuscula_na_linha_ou_col_geral(Tabuleiro *tabAtual)
{
    for (int i = 0; i < tabAtual->linhas; i++)
    {
        for (int j = 0; j < tabAtual->colunas; j++)
        {
            char atual = tabAtual->grelha[i][j];
            if (islower((unsigned char)atual))
            {
                char M = toupper((unsigned char)atual);
                for (int k = 0; k < tabAtual->colunas; k++)
                {
                    if (k != j && tabAtual->grelha[i][k] == M)
                    {
                        return true;
                    }
                }
                for (int k = 0; k < tabAtual->linhas; k++)
                {
                    if (k != i && tabAtual->grelha[k][j] == M)
                    {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

bool necessaria_para_conectividade(Tabuleiro *tabAtual, int linha, int coluna)
{
    char original = tabAtual->grelha[linha][coluna];

    tabAtual->grelha[linha][coluna] = '#';

    bool conectada = verificarConectividade(tabAtual, 's');

    tabAtual->grelha[linha][coluna] = original;

    return !conectada;
}

bool compara_tabuleiros(Tabuleiro *tabA, Tabuleiro *tabB)
{
    for (int i = 0; i < tabA->linhas; i++)
    {
        for (int j = 0; j < tabA->colunas; j++)
        {
            if (tabA->grelha[i][j] != tabB->grelha[i][j])
            {
                return false;
            }
        }
    }
    return true;
}

void copia_tabuleiros(Tabuleiro *tabA, Tabuleiro *tabB)
{
    for (int i = 0; i < tabA->linhas; i++)
    {
        for (int j = 0; j < tabA->colunas; j++)
        {
            tabA->grelha[i][j] = tabB->grelha[i][j];
        }
    }
}

void comando_a(Tabuleiro *tabAtual, Tabuleiro *tabIO, Historico *hist)
{
    for (int i = 0; i < tabAtual->linhas; i++)
    {
        for (int j = 0; j < tabAtual->colunas; j++)
        {
            char atual = tabAtual->grelha[i][j];
            bool next = true;

            while (next)
            {
                bool fez_algo = false;

                if (!isupper(atual) && atual != '#')
                {
                    if (!existe_igual_na_linha_ou_coluna(tabAtual, i, j))
                    {
                        if (tabAtual->grelha[i][j] != toupper(atual))
                        {
                            guardar_estado(hist, tabAtual);
                            tabAtual->grelha[i][j] = toupper(atual);
                            fez_algo = true;
                        }
                        next = false;
                    }

                    if (!fez_algo && tem_riscado_adjacente_coord(tabAtual, i, j))
                    {
                        if (tabAtual->grelha[i][j] != toupper(atual))
                        {
                            guardar_estado(hist, tabAtual);
                            tabAtual->grelha[i][j] = toupper(atual);
                            fez_algo = true;
                        }

                        if (existe_maiuscula_igual_na_linha_ou_coluna(tabAtual, i, j))
                        {
                            desfazer(hist, tabAtual, tabIO, NULL);
                        }
                        else
                        {
                            next = false;
                        }
                    }

                    if (!fez_algo && necessaria_para_conectividade(tabAtual, i, j))
                    {
                        if (tabAtual->grelha[i][j] != toupper(atual))
                        {
                            guardar_estado(hist, tabAtual);
                            tabAtual->grelha[i][j] = toupper(atual);
                            fez_algo = true;
                        }

                        if (existe_maiuscula_igual_na_linha_ou_coluna(tabAtual, i, j))
                        {
                            desfazer(hist, tabAtual, tabIO, NULL);
                        }
                        else
                        {
                            next = false;
                        }
                    }

                    if (!fez_algo && existe_maiuscula_igual_na_linha_ou_coluna(tabAtual, i, j))
                    {
                        if (tabAtual->grelha[i][j] != '#')
                        {
                            guardar_estado(hist, tabAtual);
                            tabAtual->grelha[i][j] = '#';
                            fez_algo = true;
                        }

                        if (tem_riscado_adjacente(tabAtual) || !verificarConectividade(tabAtual, 's'))
                        {
                            desfazer(hist, tabAtual, tabIO, NULL);
                        }
                        else
                        {
                            next = false;
                        }
                    }

                    if (!fez_algo)
                    {
                        next = false;
                    }

                    next = false;
                }
                else
                {
                    next = false;
                }
            }
        }
    }
}

void comando_A(Tabuleiro *tabAtual, Tabuleiro *tabIO, Historico *hist)
{
    Tabuleiro original;
    bool continuar = true;
    int ant;
    while (continuar)
    {
        ant = hist->topo;
        comando_a(tabAtual, tabIO, hist);
        if (hist->topo == ant)
        {
            continuar = false;
        }
    }
}
