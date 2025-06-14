#include <stdio.h>
#include <stdbool.h>
#include <board.h>
#include <ctype.h>
#include "verifica.h"

bool verificarLinhas(Tabuleiro *tabAtual, bool mostrarViolacoes)
{
    int linhas = tabAtual->linhas;
    int cols = tabAtual->colunas;

    for (int i = 0; i < linhas; i++)
    {
        bool seen[MAX_SIDE] = {false};
        for (int j = 0; j < cols; j++)
        {
            char c = tabAtual->grelha[i][j];
            if (c >= 'A' && c <= 'Z')
            {
                int idx = c - 'A';
                if (seen[idx])
                {
                    if (mostrarViolacoes)
                    {
                        char col_label = 'a' + j;
                        printf("\033[1;33m 💡 Violação: letra '%c' repetida na linha %d, coluna %c 💡\n\n\033[0m", c, i + 1, col_label);
                    }
                    return false;
                }
                seen[idx] = true;
            }
        }
    }

    return true;
}

bool verificarColunas(Tabuleiro *tabAtual, bool mostrarViolacoes)
{
    int linhas = tabAtual->linhas;
    int cols = tabAtual->colunas;

    for (int j = 0; j < cols; j++)
    {
        bool seen[MAX_SIDE] = {false};
        for (int i = 0; i < linhas; i++)
        {
            char c = tabAtual->grelha[i][j];
            if (c >= 'A' && c <= 'Z')
            {
                int idx = c - 'A';
                if (seen[idx])
                {
                    if (mostrarViolacoes)
                    {
                        char col_label = 'a' + j;
                        printf("\033[1;33m 💡 Violação: letra '%c' repetida na coluna %c, linha %d 💡\n\n\033[0m", c, col_label, i + 1);
                    }
                    return false;
                }
                seen[idx] = true;
            }
        }
    }

    return true;
}

bool verificarCelulasRiscadas(Tabuleiro *tabAtual, bool mostrarViolacoes)
{
    int linhas = tabAtual->linhas;
    int cols = tabAtual->colunas;

    int dr[4] = {-1, 1, 0, 0};
    int dc[4] = {0, 0, -1, 1};
    bool valido = true;

    for (int i = 0; i < linhas; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (tabAtual->grelha[i][j] == '#')
            {
                char self_col = 'a' + j;
                int self_linha = i + 1;
                for (int d = 0; d < 4; d++)
                {
                    int ni = i + dr[d];
                    int nj = j + dc[d];
                    if (ni >= 0 && ni < linhas && nj >= 0 && nj < cols)
                    {
                        char nb = tabAtual->grelha[ni][nj];
                        if (!(isupper(nb)))
                        {
                            if (mostrarViolacoes)
                            {
                                char neigh_col = 'a' + nj;
                                int neigh_linha = ni + 1;
                                printf("\033[1;33m 💡 Violação: célula riscada em %c%d tem vizinho inválido em %c%d: '%c' 💡\n\n\033[0m",
                                       self_col, self_linha, neigh_col, neigh_linha, nb);
                            }
                            valido = false;
                        }
                    }
                }
            }
        }
    }

    return valido;
}

void inicializarVisitadas(bool visitada[MAX_SIDE][MAX_SIDE], int linhas, int colunas)
{
    for (int i = 0; i < linhas; i++)
    {
        for (int j = 0; j < colunas; j++)
        {
            visitada[i][j] = false;
        }
    }
}

bool encontrarCasaInicial(Tabuleiro *tabAtual, int *linha, int *coluna)
{
    for (int i = 0; i < tabAtual->linhas; i++)
    {
        for (int j = 0; j < tabAtual->colunas; j++)
        {
            if (tabAtual->grelha[i][j] != '#')
            {
                *linha = i;
                *coluna = j;
                return true;
            }
        }
    }
    return false;
}

int contarCasasNaoRiscadas(Tabuleiro *tabAtual)
{
    int total = 0;
    for (int i = 0; i < tabAtual->linhas; i++)
    {
        for (int j = 0; j < tabAtual->colunas; j++)
        {
            if (tabAtual->grelha[i][j] != '#')
            {
                total++;
            }
        }
    }
    return total;
}

bool BFS(Tabuleiro *tabAtual, bool visitada[MAX_SIDE][MAX_SIDE], int linha_inicial, int coluna_inicial, int *visitados)
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

            if (novalinha >= 0 && novalinha < tabAtual->linhas && novaColuna >= 0 && novaColuna < tabAtual->colunas)
            {
                if (tabAtual->grelha[novalinha][novaColuna] != '#' && !visitada[novalinha][novaColuna])
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

bool verificarConectividade(Tabuleiro *tabAtual, char modo)
{
    bool visitada[MAX_SIDE][MAX_SIDE];
    int linha_inicial, coluna_inicial;
    int visitados;
    int total_nao_riscadas;

    inicializarVisitadas(visitada, tabAtual->linhas, tabAtual->colunas);

    if (!encontrarCasaInicial(tabAtual, &linha_inicial, &coluna_inicial))
    {
        return true;
    }

    total_nao_riscadas = contarCasasNaoRiscadas(tabAtual);

    BFS(tabAtual, visitada, linha_inicial, coluna_inicial, &visitados);

    if (visitados != total_nao_riscadas)
    {
        if (modo == 'w')
        {
            printf("\033[1;33m 💡 Violação: nem todas as casas não riscadas estão conectadas (visitadas %d, esperadas %d) 💡\n\n\033[0m", visitados, total_nao_riscadas);
        }
        return false;
    }

    return true;
}

bool verificarRestricoes(Tabuleiro *tabAtual, bool mostrarViolacoes)
{
    int ok = true;

    if (!verificarLinhas(tabAtual, mostrarViolacoes))
        ok = false;

    if (!verificarColunas(tabAtual, mostrarViolacoes))
        ok = false;

    if (!verificarCelulasRiscadas(tabAtual, mostrarViolacoes))
        ok = false;

    if (!verificarConectividade(tabAtual, mostrarViolacoes ? 'w' : 's'))
        ok = false;

    return ok;
}
