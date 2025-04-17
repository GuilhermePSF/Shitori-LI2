#include <stdio.h>
#include <stdbool.h>
#include "verifica.h"

/*
 verificarRestricoes:
   - Regra 1: Em cada linha, não pode haver duas letras maiúsculas iguais.
   - Regra 2: Em cada coluna, não pode haver duas letras maiúsculas iguais.
   - Regra 3: Para cada célula riscada ('#'), todos os vizinhos ortogonais dentro do tabuleiro
     devem ser letras brancas (maiúsculas) ou espaço em branco (' ').

 */

int verificarRestricoes(const Tabuleiro *tab)
{
    int rows = tab->linhas;
    int cols = tab->colunas;
    int ok = 1;

    // Regra 1:
    for (int i = 0; i < rows; i++)
    {
        bool seen[26] = {false};
        for (int j = 0; j < cols; j++)
        {
            char c = tab->grelha[i][j];
            if (c >= 'A' && c <= 'Z')
            {
                int idx = c - 'A';
                if (seen[idx])
                {
                    char col_label = 'a' + j;
                    printf("Violação: letra '%c' repetida na linha %d, coluna %c\n", c, i + 1, col_label);
                    ok = 0;
                }
                else
                {
                    seen[idx] = true;
                }
            }
        }
    }

    // Regra 2:
    for (int j = 0; j < cols; j++)
    {
        bool seen[26] = {false};
        for (int i = 0; i < rows; i++)
        {
            char c = tab->grelha[i][j];
            if (c >= 'A' && c <= 'Z')
            {
                int idx = c - 'A';
                if (seen[idx])
                {
                    char col_label = 'a' + j;
                    printf("Violação: letra '%c' repetida na coluna %c, linha %d\n", c, col_label, i + 1);
                    ok = 0;
                }
                else
                {
                    seen[idx] = true;
                }
            }
        }
    }

    // Regra 3:
    int dr[4] = {-1, 1, 0, 0};
    int dc[4] = {0, 0, -1, 1};
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (tab->grelha[i][j] == '#')
            {
                char self_col = 'a' + j;
                int self_row = i + 1;
                for (int d = 0; d < 4; d++)
                {
                    int ni = i + dr[d];
                    int nj = j + dc[d];
                    if (ni >= 0 && ni < rows && nj >= 0 && nj < cols)
                    {
                        char nb = tab->grelha[ni][nj];
                        if (!(nb >= 'A' && nb <= 'Z') && nb != ' ')
                        {
                            char neigh_col = 'a' + nj;
                            int neigh_row = ni + 1;
                            printf("Violação: célula riscada em %c%d tem vizinho inválido em %c%d: '%c'\n",
                                   self_col, self_row, neigh_col, neigh_row, nb);
                            ok = 0;
                        }
                    }
                }
            }
        }
    }

    return ok;
}
