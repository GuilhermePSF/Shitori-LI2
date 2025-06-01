#include <stdio.h>
#include <stdbool.h>
#include "board.h"

void centrarLabel(int colunas)
{
    for (int i = 0; i < colunas * 2 - 10; i++)
    {
        printf(" ");
    }
}

void mostrarAjuda()
{
    printf(" ?                - Mostra tabela de ajuda\n");
    printf(" l <ficheiro>     - Carrega um tabuleiro de um ficheiro\n");
    printf(" G <tamanho>      - Gera um tabuleiro aleatório (1 a 26)\n");
    printf(" g <ficheiro>     - Grava o tabuleiro atual para um ficheiro\n");
    printf(" b <coord>        - Pinta uma célula em branco (ex: b a3)\n");
    printf(" r <coord>        - Risca uma célula (ex: r b4)\n");
    printf(" d                - Desfaz o último movimento\n");
    printf(" d <coord>        - Desfaz um movimento numa coordenada específica\n");
    printf(" D                - Reverte o tabuleiro para o estado inicial\n");
    printf(" a                - Aplica ajuda)\n");
    printf(" A                - Aplica todas as ajudas possiveis\n");
    printf(" v                - Verifica todas as restrições\n");
    printf(" R                - Resolve o tabuleiro automaticamente\n");
    printf(" s                - Sai do jogo\n");
}

void mostrarTabuleiro(const Tabuleiro *tabAtual)
{
    centrarLabel(tabAtual->colunas);
    printf("   ╔═══════════════════╗\n");
    centrarLabel(tabAtual->colunas);
    printf("   ║      \033[1;3mSHITORI\033[0m      ║\n");
    centrarLabel(tabAtual->colunas);
    printf("   ╚═══════════════════╝\n\n");

    printf("    ");
    for (int col = 0; col < tabAtual->colunas; col++)
    {
        printf(" %c  ", 'a' + col);
    }
    printf("\n");

    printf("   ╔");
    for (int col = 0; col < tabAtual->colunas; col++)
    {
        printf("═══");
        if (col < tabAtual->colunas - 1)
            printf("╦");
    }
    printf("╗\n");

    for (int linha = 0; linha < tabAtual->linhas; linha++)
    {
        printf("%2d ║", linha + 1);

        for (int col = 0; col < tabAtual->colunas; col++)
        {
            char c = tabAtual->grelha[linha][col];

            if (c >= 'a' && c <= 'z')
            {
                printf("\033[1;30m %c \033[0m", c);
            }
            else if (c == '#')
            {
                printf("\033[1;31m # \033[0m");
            }
            else
            {
                printf(" %c ", c);
            }

            printf("║");
        }
        printf("\n");

        if (linha < tabAtual->linhas - 1)
        {
            printf("   ╠");
            for (int col = 0; col < tabAtual->colunas; col++)
            {
                printf("═══");
                if (col < tabAtual->colunas - 1)
                    printf("╬");
            }
            printf("╣\n");
        }
        else
        {
            printf("   ╚");
            for (int col = 0; col < tabAtual->colunas; col++)
            {
                printf("═══");
                if (col < tabAtual->colunas - 1)
                    printf("╩");
            }
            printf("╝\n");
        }
    }

    printf("\n");
    printf("Comandos disponíveis:\n");
    mostrarAjuda();
}

Tabuleiro copiar_tabuleiro(Tabuleiro *orig)
{
    Tabuleiro copia;
    copia.linhas = orig->linhas;
    copia.colunas = orig->colunas;

    for (int i = 0; i < copia.linhas; i++)
        for (int j = 0; j < copia.colunas; j++)
            copia.grelha[i][j] = orig->grelha[i][j];

    return copia;
}

void copiar_tabuleiro_para(Tabuleiro *orig, Tabuleiro *dest)
{
    if (orig == NULL || dest == NULL)
    {
        return;
    }

    dest->linhas = orig->linhas;
    dest->colunas = orig->colunas;

    for (int i = 0; i < orig->linhas; i++)
        for (int j = 0; j < orig->colunas; j++)
            dest->grelha[i][j] = orig->grelha[i][j];
}

/* bool compara_tabuleiros(Tabuleiro *tabA, Tabuleiro *tabB)
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
*/