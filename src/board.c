#include <stdio.h>
#include "board.h"

void mostrarTabuleiro(const Tabuleiro *tab)
{
    printf("   ╔═══════════════════╗\n");
    printf("   ║      \033[1;3mSHITORI\033[0m      ║\n");
    printf("   ╚═══════════════════╝\n\n");

    printf("    ");
    for (int col = 0; col < tab->colunas; col++)
    {
        printf(" %c  ", 'a' + col);
    }
    printf("\n");

    printf("   ╔");
    for (int col = 0; col < tab->colunas; col++)
    {
        printf("═══");
        if (col < tab->colunas - 1)
            printf("╦");
    }
    printf("╗\n");

    for (int linha = 0; linha < tab->linhas; linha++)
    {
        printf("%2d ║", linha + 1);

        for (int col = 0; col < tab->colunas; col++)
        {
            char c = tab->grelha[linha][col];

            if (c >= 'a' && c <= 'z')
            {
                printf("\033[1;30m %c \033[0m", c );
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

        if (linha < tab->linhas - 1)
        {
            printf("   ╠");
            for (int col = 0; col < tab->colunas; col++)
            {
                printf("═══");
                if (col < tab->colunas - 1)
                    printf("╬");
            }
            printf("╣\n");
        }
        else
        {
            printf("   ╚");
            for (int col = 0; col < tab->colunas; col++)
            {
                printf("═══");
                if (col < tab->colunas - 1)
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
