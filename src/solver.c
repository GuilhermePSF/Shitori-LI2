#include "solver.h"
#include "board.h"
#include "undo.h"
#include "verifica.h"
#include "tip.h"
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

// Regra 1 - Triplo adjacente (a a a) significa riscar
bool regra1_horizontal(Tabuleiro *tabAtual, int linha, int coluna)
{
    char alvo = tolower(tabAtual->grelha[linha][coluna]);
    return (coluna == 0 || alvo == tolower(tabAtual->grelha[linha][coluna - 1])) && (coluna == (tabAtual->colunas - 1) || alvo == tolower(tabAtual->grelha[linha][coluna + 1]));
}

bool regra1_vertical(Tabuleiro *tabAtual, int linha, int coluna)
{
    if (linha >= 1 && linha < tabAtual->linhas - 1)
    {
        char cima = tabAtual->grelha[linha - 1][coluna];
        char meio = tabAtual->grelha[linha][coluna];
        char baixo = tabAtual->grelha[linha + 1][coluna];
        return tolower(cima) == tolower(meio) && tolower(baixo) == tolower(meio);
    }
    return false;
}

void aplicar_regra1(Tabuleiro *tabAtual, Tabuleiro *tabIO, Historico *hist)
{
    // Regra 1 HORIZONTAL (triplo adjacente na linha)
    for (int i = 0; i < tabAtual->linhas; i++)
    {
        for (int j = 1; j < tabAtual->colunas - 1; j++) // Exclui colunas de extremidade
        {
            if (regra1_horizontal(tabAtual, i, j) && tabAtual->grelha[i][j] != '#')
            {
                guardar_estado(hist, tabAtual);
                tabAtual->grelha[i][j] = toupper(tabAtual->grelha[i][j]);
                if (existe_maiuscula_igual_na_linha_ou_coluna(tabAtual, i, j))
                {
                    desfazer(hist, tabAtual, tabIO, NULL);
                }
            }
        }
    }

    // Regra 1 VERTICAL (triplo adjacente na coluna)
    for (int i = 1; i < tabAtual->linhas - 1; i++) // Exclui linhas de extremidade
    {
        for (int j = 0; j < tabAtual->colunas; j++)
        {
            if (regra1_vertical(tabAtual, i, j) && tabAtual->grelha[i][j] != '#')
            {
                guardar_estado(hist, tabAtual);
                tabAtual->grelha[i][j] = toupper(tabAtual->grelha[i][j]);
                if (existe_maiuscula_igual_na_linha_ou_coluna(tabAtual, i, j))
                {
                    desfazer(hist, tabAtual, tabIO, NULL);
                }
            }
        }
    }
}

// Regra 2 - Entre pares (a b a) significa pintar
bool regra2_horizontal(Tabuleiro *tabAtual, int linha, int coluna)
{
    if (coluna >= 1 && coluna < tabAtual->colunas - 1)
    {
        char esq = tabAtual->grelha[linha][coluna - 1];
        char meio = tabAtual->grelha[linha][coluna];
        char dir = tabAtual->grelha[linha][coluna + 1];
        return tolower(esq) == tolower(dir) && tolower(meio) != tolower(esq);
    }
    return false;
}

bool regra2_vertical(Tabuleiro *tabAtual, int linha, int coluna)
{
    if (linha >= 1 && linha < tabAtual->linhas - 1)
    {
        char cima = tabAtual->grelha[linha - 1][coluna];
        char meio = tabAtual->grelha[linha][coluna];
        char baixo = tabAtual->grelha[linha + 1][coluna];
        return tolower(cima) == tolower(baixo) && tolower(meio) != tolower(cima);
    }
    return false;
}

void aplicar_regra2(Tabuleiro *tabAtual, Tabuleiro *tabIO, Historico *hist)
{
    // Regra 2 HORIZONTAL (entre pares na linha)
    for (int i = 0; i < tabAtual->linhas; i++)
    {
        for (int j = 1; j < tabAtual->colunas - 1; j++) // Exclui colunas de extremidade
        {
            if (regra2_horizontal(tabAtual, i, j))
            {
                char atual = tabAtual->grelha[i][j];
                if (isalpha(atual) && islower(atual))
                {
                    guardar_estado(hist, tabAtual);
                    tabAtual->grelha[i][j] = toupper(atual);
                    if (existe_maiuscula_igual_na_linha_ou_coluna(tabAtual, i, j))
                    {
                        desfazer(hist, tabAtual, tabIO, NULL);
                    }
                }
            }
        }
    }

    // Regra 2 VERTICAL (entre pares na coluna)
    for (int i = 1; i < tabAtual->linhas - 1; i++) // Exclui linhas de extremidade
    {
        for (int j = 0; j < tabAtual->colunas; j++)
        {
            if (regra2_vertical(tabAtual, i, j))
            {
                char atual = tabAtual->grelha[i][j];
                if (isalpha(atual) && islower(atual))
                {
                    guardar_estado(hist, tabAtual);
                    tabAtual->grelha[i][j] = toupper(atual);
                    if (existe_maiuscula_igual_na_linha_ou_coluna(tabAtual, i, j))
                    {
                        desfazer(hist, tabAtual, tabIO, NULL);
                    }
                }
            }
        }
    }
}

// Regra 3 - Par adjacente + instância separada signfica riscar
bool regra3_horizontal(Tabuleiro *tabAtual, int linha, int coluna)
{
    char alvo = tabAtual->grelha[linha][coluna];
    if ((coluna == 0 || alvo != (tabAtual->grelha[linha][coluna - 1])) && (coluna == (tabAtual->colunas - 1) || alvo != (tabAtual->grelha[linha][coluna + 1])))
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
    if ((linha == 0 || alvo != (tabAtual->grelha[linha - 1][coluna])) && (linha == (tabAtual->linhas - 1) || alvo != (tabAtual->grelha[linha + 1][coluna])))
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

void aplicar_regra3(Tabuleiro *tabAtual, Tabuleiro *tabIO, Historico *hist)
{
    for (int i = 0; i < tabAtual->linhas; i++)
    {
        for (int j = 0; j < tabAtual->colunas; j++)
        {
            if (regra3_horizontal(tabAtual, i, j) && tabAtual->grelha[i][j] != '#')
            {
                guardar_estado(hist, tabAtual);
                tabAtual->grelha[i][j] = '#';
                if (tem_riscado_adjacente(tabAtual) || !verificarConectividade(tabAtual, 's'))
                {
                    desfazer(hist, tabAtual, tabIO, NULL);
                }
            }

            if (regra3_vertical(tabAtual, i, j) && tabAtual->grelha[i][j] != '#')
            {
                guardar_estado(hist, tabAtual);
                tabAtual->grelha[i][j] = '#';
                if (tem_riscado_adjacente(tabAtual) || !verificarConectividade(tabAtual, 's'))
                {
                    desfazer(hist, tabAtual, tabIO, NULL);
                }
            }
        }
    }
}

void tecnicas_iniciais(Tabuleiro *tabAtual, Tabuleiro *tabIO, Historico *hist) // cccac
{
    aplicar_regra2(tabAtual, tabIO, hist);
    aplicar_regra3(tabAtual, tabIO, hist);
    aplicar_regra1(tabAtual, tabIO, hist);
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
bool solve(Tabuleiro *tabAtual, int l, int c)
{

    if (l == tabAtual->linhas)
    {
        return true;
    }
    else if (c == tabAtual->colunas)
    {
        return (solve(tabAtual, l + 1, 0));
    }
    else if (!('a' <= tabAtual->grelha[l][c] && tabAtual->grelha[l][c] <= 'z'))
    {
        return (solve(tabAtual, l, c + 1));
    }
    else
    {
        if (ser_valido(tabAtual, l, c, toupper(tabAtual->grelha[l][c])))
        {
            char original = tabAtual->grelha[l][c];
            tabAtual->grelha[l][c] = toupper(tabAtual->grelha[l][c]);
            if (solve(tabAtual, l, c + 1))
            {
                return true;
            }
            tabAtual->grelha[l][c] = original;
        }
        if (ser_valido(tabAtual, l, c, '#'))
        {
            char original = tabAtual->grelha[l][c];
            tabAtual->grelha[l][c] = '#';
            if (solve(tabAtual, l, c + 1))
            {
                return true;
            }
            tabAtual->grelha[l][c] = original;
        }
        return false;
    }
}

void comando_R(Tabuleiro *tabAtual, Tabuleiro *tabIO, Historico *hist)
{
    Tabuleiro tabOriginal = copiar_tabuleiro(&hist->estados[0]);

    Historico histTemp;
    inicializar_historico(&histTemp);

    tecnicas_iniciais(&tabOriginal, tabIO, &histTemp);
    comando_A(&tabOriginal, tabIO, &histTemp);
    solve(&tabOriginal, 0, 0);

    copiar_tabuleiro_para(&tabOriginal, tabAtual);
}
