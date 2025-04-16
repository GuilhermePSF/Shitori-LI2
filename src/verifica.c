#include <stdio.h>
#include <ctype.h>
#include "board.h"

int verificarRestricoes(const Tabuleiro *tab)
{
    int valido = 1;

    // Verificar se há letras repetidas em linhas ou colunas
    for (int i = 0; i < tab->linhas; i++)
    {
        for (int j = 0; j < tab->colunas; j++)
        {
            char atual = tab->grelha[i][j];
            if (isupper(atual)) // Apenas verifica letras brancas
            {
                // Verificar na linha
                for (int k = 0; k < tab->colunas; k++)
                {
                    if (k != j && toupper(tab->grelha[i][k]) == atual)
                    {
                        printf("Restrição violada: '%c' repetido na linha %d.\n", atual, i + 1);
                        valido = 0;
                    }
                }

                // Verificar na coluna
                for (int k = 0; k < tab->linhas; k++)
                {
                    if (k != i && toupper(tab->grelha[k][j]) == atual)
                    {
                        printf("Restrição violada: '%c' repetido na coluna %d.\n", atual, j + 1);
                        valido = 0;
                    }
                }
            }

            // Verificar casas riscadas (#) e suas vizinhas
            if (atual == '#')
            {
                int dx[] = {-1, 1, 0, 0};
                int dy[] = {0, 0, -1, 1};
                for (int d = 0; d < 4; d++)
                {
                    int ni = i + dx[d];
                    int nj = j + dy[d];
                    if (ni >= 0 && ni < tab->linhas && nj >= 0 && nj < tab->colunas)
                    {
                        if (tab->grelha[ni][nj] != toupper(tab->grelha[ni][nj]))
                        {
                            printf("Restrição violada: Casa riscada (%d, %d) tem vizinho não branco.\n", i + 1, j + 1);
                            valido = 0;
                        }
                    }
                }
            }
        }
    }

    return valido;
}