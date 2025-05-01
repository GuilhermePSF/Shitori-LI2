#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "board.h"
#include "io.h"
#include "game.h"
#include "undo.h"
#include "verifica.h"
#include "verifica.h"
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

// TODO improve safety

bool tem_riscado_adjacaente(const Tabuleiro *tab)
{
    for (int i = 0; i < tab->linhas; i++)
    {
        for (int j = 0; j < tab->colunas; j++)
        {
            if (tab->grelha[i][j] == '#')
            {
                if (i > 0 && tab->grelha[i - 1][j] == '#')
                {
                    return true;
                }
                if (i < tab->linhas - 1 && tab->grelha[i + 1][j] == '#')
                {
                    return true;
                }
                if (j > 0 && tab->grelha[i][j - 1] == '#')
                {
                    return true;
                }
                if (j < tab->colunas - 1 && tab->grelha[i][j] == '#')
                {
                    return true;
                }
            }
        }
    }
    return false;
}

bool existe_maiuscula_igual_na_linha_ou_coluna(Tabuleiro *tab, int linha, int coluna)
{
    char atual = tab->grelha[linha][coluna];

    if (!isalpha((unsigned char)atual))
        return false;

    char alvo = toupper((unsigned char)atual);

    // Verificar linha
    for (int j = 0; j < tab->colunas; j++)
    {
        if (j != coluna && tab->grelha[linha][j] == alvo && isupper((unsigned char)tab->grelha[linha][j]))
        {
            return true;
        }
    }

    // Verificar coluna
    for (int i = 0; i < tab->linhas; i++)
    {
        if (i != linha && tab->grelha[i][coluna] == alvo && isupper((unsigned char)tab->grelha[i][coluna]))
        {
            return true;
        }
    }

    return false;
}
