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
    if (coluna >= 1 && coluna < tabAtual->colunas - 1)
    {
        char esq = tabAtual->grelha[linha][coluna - 1];
        char mid = tabAtual->grelha[linha][coluna];
        char dir = tabAtual->grelha[linha][coluna + 1];
        return tolower(esq) == tolower(mid) && tolower(dir) == tolower(mid);
    }
    return false;
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
                tabAtual->grelha[i][j] = '#';
                if (tem_riscado_adjacente(tabAtual) || !verificarConectividade(tabAtual, 's'))
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
                tabAtual->grelha[i][j] = '#';
                if (tem_riscado_adjacente(tabAtual) || !verificarConectividade(tabAtual, 's'))
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
    char alvo = tolower(tabAtual->grelha[linha][coluna]);
    int count = 0;
    bool tem_dupla_adj = false;

    for (int j = 0; j < tabAtual->colunas; j++)
    {
        if (tolower(tabAtual->grelha[linha][j]) == alvo)
        {
            count++;
            if (j < tabAtual->colunas - 1 && tolower(tabAtual->grelha[linha][j + 1]) == alvo)
                tem_dupla_adj = true;
        }
    }
    return count >= 3 && tem_dupla_adj;
}

bool regra3_vertical(Tabuleiro *tabAtual, int linha, int coluna)
{
    char alvo = tolower(tabAtual->grelha[linha][coluna]);
    int count = 0;
    bool tem_dupla_adj = false;

    for (int i = 0; i < tabAtual->linhas; i++)
    {
        if (tolower(tabAtual->grelha[i][coluna]) == alvo)
        {
            count++;
            if (i < tabAtual->linhas - 1 && tolower(tabAtual->grelha[i + 1][coluna]) == alvo)
                tem_dupla_adj = true;
        }
    }
    return count >= 3 && tem_dupla_adj;
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

void tecnicas_iniciais(Tabuleiro *tabAtual, Tabuleiro *tabIO, Historico *hist)
{
    aplicar_regra1(tabAtual, tabIO, hist);
    aplicar_regra2(tabAtual, tabIO, hist);
    aplicar_regra3(tabAtual, tabIO, hist);
}

void comando_R(Tabuleiro *tabAtual, Tabuleiro *tabIO, Historico *hist)
{
    Tabuleiro tabOriginal = copiar_tabuleiro(&hist->estados[0]);

    Historico histTemp;
    inicializar_historico(&histTemp);

    tecnicas_iniciais(&tabOriginal, tabIO, &histTemp);
    comando_A(&tabOriginal, tabIO, &histTemp);

    copiar_tabuleiro_para(&tabOriginal, tabAtual);
}
