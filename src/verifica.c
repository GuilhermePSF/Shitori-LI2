#include <stdio.h>
#include <stdbool.h>
#include <board.h>
#include "verifica.h"

/*
 verificarRestricoes:
   - Regra 1: Em cada linha, não pode haver duas letras maiúsculas iguais.
   - Regra 2: Em cada coluna, não pode haver duas letras maiúsculas iguais.
   - Regra 3: Para cada célula riscada ('#'), todos os vizinhos ortogonais dentro do tabuleiro
     devem ser letras brancas (maiúsculas).
   - Regra 4: Todas as casas não riscadas ('#') devem estar conectadas ortogonalmente.
 */

// Regra 1
int verificarLinhas(Tabuleiro *tab)
{
    int ok = 1;
    int linhas = tab->linhas;
    int cols = tab->colunas;
    int i, j;

    for (i = 0; i < linhas; i++)
    {
        bool seen[MAX_SIDE] = {false};
        for (j = 0; j < cols; j++)
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

    return ok;
}

// Regra 2
int verificarColunas(Tabuleiro *tab)
{
    int ok = 1;
    int linhas = tab->linhas;
    int cols = tab->colunas;
    int i, j;

    for (j = 0; j < cols; j++)
    {
        bool seen[MAX_SIDE] = {false};
        for (i = 0; i < linhas; i++)
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

    return ok;
}

// Regra 3
int verificarCelulasRiscadas(Tabuleiro *tab)
{
    int ok = 1;
    int linhas = tab->linhas;
    int cols = tab->colunas;
    int i, j, d;

    int dr[4] = {-1, 1, 0, 0};
    int dc[4] = {0, 0, -1, 1};

    for (i = 0; i < linhas; i++)
    {
        for (j = 0; j < cols; j++)
        {
            if (tab->grelha[i][j] == '#')
            {
                char self_col = 'a' + j;
                int self_linha = i + 1;
                for (d = 0; d < 4; d++)
                {
                    int ni = i + dr[d];
                    int nj = j + dc[d];
                    if (ni >= 0 && ni < linhas && nj >= 0 && nj < cols)
                    {
                        char nb = tab->grelha[ni][nj];
                        if (!(nb >= 'A' && nb <= 'Z'))
                        {
                            char neigh_col = 'a' + nj;
                            int neigh_linha = ni + 1;
                            printf("Violação: célula riscada em %c%d tem vizinho inválido em %c%d: '%c'\n",
                                   self_col, self_linha, neigh_col, neigh_linha, nb);
                            ok = 0;
                        }
                    }
                }
            }
        }
    }

    return ok;
}

void inicializarVisitadas(bool visitada[MAX_SIDE][MAX_SIDE], int linhas, int colunas)
{
    int i, j;
    for (i = 0; i < linhas; i++)
    {
        for (j = 0; j < colunas; j++)
        {
            visitada[i][j] = false;
        }
    }
}

bool encontrarCasaInicial(Tabuleiro *tab, int *linha, int *coluna)
{
    int i, j;
    for (i = 0; i < tab->linhas; i++)
    {
        for (j = 0; j < tab->colunas; j++)
        {
            if (tab->grelha[i][j] != '#')
            {
                *linha = i;
                *coluna = j;
                return true;
            }
        }
    }
    return false;
}

int contarCasasNaoRiscadas(Tabuleiro *tab)
{
    int total = 0;
    int i, j;
    for (i = 0; i < tab->linhas; i++)
    {
        for (j = 0; j < tab->colunas; j++)
        {
            if (tab->grelha[i][j] != '#')
            {
                total++;
            }
        }
    }
    return total;
}

bool BFS(Tabuleiro *tab, bool visitada[MAX_SIDE][MAX_SIDE], int linha_inicial, int coluna_inicial, int *visitados)
{
    Coord queue[MAX_SIDE * MAX_SIDE];
    int front = 0, rear = 0;
    queue[rear++] = (Coord){linha_inicial, coluna_inicial};
    visitada[linha_inicial][coluna_inicial] = true;

    *visitados = 1;

    int linhaDirs[] = {-1, 1, 0, 0};
    int colunaDirs[] = {0, 0, -1, 1};

    while (front < rear)
    {
        Coord current = queue[front++];

        for (int dir = 0; dir < 4; dir++)
        {
            int novalinha = current.ln + linhaDirs[dir];
            int novaColuna = current.col + colunaDirs[dir];

            if (novalinha >= 0 && novalinha < tab->linhas && novaColuna >= 0 && novaColuna < tab->colunas)
            {
                if (tab->grelha[novalinha][novaColuna] != '#' && !visitada[novalinha][novaColuna])
                {
                    visitada[novalinha][novaColuna] = true;
                    queue[rear++] = (Coord){novalinha, novaColuna};
                    (*visitados)++;
                }
            }
        }
    }

    return true;
}

int verificarConectividade(Tabuleiro *tab)
{
    bool visitada[MAX_SIDE][MAX_SIDE];
    int linha_inicial, coluna_inicial;
    int visitados;
    int total_nao_riscadas;

    inicializarVisitadas(visitada, tab->linhas, tab->colunas);

    if (!encontrarCasaInicial(tab, &linha_inicial, &coluna_inicial))
    {
        return 1;
    }

    total_nao_riscadas = contarCasasNaoRiscadas(tab);

    BFS(tab, visitada, linha_inicial, coluna_inicial, &visitados);

    if (visitados != total_nao_riscadas)
    {
        printf("Violação: nem todas as casas não riscadas estão conectadas (visitadas %d, esperadas %d)\n", visitados, total_nao_riscadas);
        return 0;
    }

    return 1;
}

int verificarRestricoes(Tabuleiro *tab)
{
    int ok = 1;

    if (!verificarLinhas(tab))
        ok = 0;

    if (!verificarColunas(tab))
        ok = 0;

    if (!verificarCelulasRiscadas(tab))
        ok = 0;

    if (!verificarConectividade(tab))
        ok = 0;

    return ok;
}
