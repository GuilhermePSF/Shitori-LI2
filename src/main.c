#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "board.h"
#include "io.h"
#include "game.h"
#include "undo.h"
#include "verifica.h"

int main()
{
    Tabuleiro tab;
    Historico hist = {.topo = 0};
    char cmd[256];
    bool a_correr = true;

    while (a_correr)
    {
        printf("> ");
        if (!fgets(cmd, sizeof(cmd), stdin))
            break;
        cmd[strcspn(cmd, "\n")] = '\0';

        if (cmd[0] == 'l')
        {
            char ficheiro[256];
            if (sscanf(cmd, "l %s", ficheiro) == 1)
            {
                if (carregarTabuleiro(&tab, &hist, ficheiro) == -1)
                {
                    printf("Erro ao carregar o tabuleiro.\n");
                }
            }
        }
        else if (cmd[0] == 'g')
        {
            char ficheiro[256];
            if (sscanf(cmd, "g %s", ficheiro) == 1)
            {
                if (gravarTabuleiro(&tab, ficheiro) == -1)
                {
                    printf("Erro ao gravar o tabuleiro.\n");
                }
                else
                {
                    printf("Tabuleiro gravado com sucesso.\n");
                }
            }
        }
        else if (cmd[0] == 'b' || cmd[0] == 'r')
        {
            char coord[50];
            if (sscanf(cmd, "%*c %s", coord) == 1)
                modificarTabuleiro(&tab, &hist, cmd[0], coord);
        }
        else if (cmd[0] == 'd')
        {
            desfazer(&hist, &tab);
        }
        else if (cmd[0] == 'v')
        {
            if (verificarRestricoes(&tab))
            {
                printf("Todas as restrições estão satisfeitas.\n");
            }
            else
            {
                printf("Existem restrições violadas.\n");
            }
        }
        else if (cmd[0] == 's')
        {
            a_correr = false;
        }
        else
        {
            printf("Comando inválido.\n");
        }
    }

    return 0;
}
