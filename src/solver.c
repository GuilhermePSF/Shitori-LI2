#include "solver.h"
#include "board.h"
#include <stdbool.h>
#include <ctype.h>

// Regra 1 - Triplo adjacente (a a a) significa riscar
bool regra1_horizontal(Tabuleiro *tab, int linha, int coluna) {
    if (coluna >= 1 && coluna < tab->colunas - 1) {
        char esq = tab->grelha[linha][coluna - 1];
        char mid = tab->grelha[linha][coluna];
        char dir = tab->grelha[linha][coluna + 1];
        return tolower(esq) == tolower(mid) && tolower(dir) == tolower(mid);
    }
    return false;
}

bool regra1_vertical(Tabuleiro *tab, int linha, int coluna) {
    if (linha >= 1 && linha < tab->linhas - 1) {
        char cima = tab->grelha[linha - 1][coluna];
        char meio = tab->grelha[linha][coluna];
        char baixo = tab->grelha[linha + 1][coluna];
        return tolower(cima) == tolower(meio) && tolower(baixo) == tolower(meio);
    }
    return false;
}

// Regra 2 - Entre pares (a b a) significa pintar
bool regra2_horizontal(Tabuleiro *tab, int linha, int coluna) {
    if (coluna >= 1 && coluna < tab->colunas - 1) {
        char esq = tab->grelha[linha][coluna - 1];
        char meio = tab->grelha[linha][coluna];
        char dir = tab->grelha[linha][coluna + 1];
        return tolower(esq) == tolower(dir) && tolower(meio) != tolower(esq);
    }
    return false;
}

bool regra2_vertical(Tabuleiro *tab, int linha, int coluna) {
    if (linha >= 1 && linha < tab->linhas - 1) {
        char cima = tab->grelha[linha - 1][coluna];
        char meio = tab->grelha[linha][coluna];
        char baixo = tab->grelha[linha + 1][coluna];
        return tolower(cima) == tolower(baixo) && tolower(meio) != tolower(cima);
    }
    return false;
}

// Regra 3 - Par adjacente + instância separada signfica riscar
bool regra3_horizontal(Tabuleiro *tab, int linha, int coluna) {
    char alvo = tolower(tab->grelha[linha][coluna]);
    int count = 0;
    bool tem_dupla_adj = false;

    for (int j = 0; j < tab->colunas; j++) {
        if (tolower(tab->grelha[linha][j]) == alvo) {
            count++;
            if (j < tab->colunas - 1 && tolower(tab->grelha[linha][j + 1]) == alvo)
                tem_dupla_adj = true;
        }
    }
    return count >= 3 && tem_dupla_adj;
}

bool regra3_vertical(Tabuleiro *tab, int linha, int coluna) {
    char alvo = tolower(tab->grelha[linha][coluna]);
    int count = 0;
    bool tem_dupla_adj = false;

    for (int i = 0; i < tab->linhas; i++) {
        if (tolower(tab->grelha[i][coluna]) == alvo) {
            count++;
            if (i < tab->linhas - 1 && tolower(tab->grelha[i + 1][coluna]) == alvo)
                tem_dupla_adj = true;
        }
    }
    return count >= 3 && tem_dupla_adj;
}

void dummy();