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
    printf("  g <ficheiro>   - gravar o estado atual do jogo num ficheiro\n");
    printf("  l <ficheiro>   - ler o estado do jogo de um ficheiro\n");
    printf("  <coord>        - jogar numa coordenada (ex: b3)\n");
    printf("  b <coord>      - pintar a letra da casa como branca (ex: b b3)\n");
    printf("  r <coord>      - riscar a casa (colocar # no local da letra)\n");
    printf("  v              - verificar restrições do tabuleiro\n");
    printf("  a              - aplicar ajuda (inferência simples)\n");
    printf("  A              - aplicar ajuda até não haver alterações\n");
    printf("  R              - resolver o jogo automaticamente\n");
    printf("  d              - desfazer o último comando\n");
    printf("  s              - sair do programa\n");
    printf("\n");
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