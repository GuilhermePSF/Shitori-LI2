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
    Tabuleiro tabAtual;
    Tabuleiro tabIO;
    Historico hist = {.topo = 0};
    char cmd[256];
    bool a_correr = true;

    while (a_correr)
    {
        printf("> ");
        if (!fgets(cmd, sizeof(cmd), stdin))
        {
            printf("Erro ao ler comando.\n");
            a_correr = false;
            continue;
        }

        cmd[strcspn(cmd, "\n")] = '\0';

        if (cmd[0] == 'l')
        {
            char ficheiro[256];
            if (sscanf(cmd, "l %255s", ficheiro) == 1)
            {
                if (!carregarTabuleiro(&tabAtual, &tabIO, &hist, ficheiro))
                {
                    printf("Erro ao carregar o tabuleiro.\n");
                }
            }
            else
            {
                printf("Comando inválido. Uso: l <ficheiro>\n");
            }
        }
        else if (cmd[0] == 'g')
        {
            char ficheiro[256];
            if (sscanf(cmd, "g %255s", ficheiro) == 1)
            {
                if (!gravarTabuleiro(&tabAtual, ficheiro))
                {
                    printf("Erro ao gravar o tabuleiro.\n");
                }
                else
                {
                    printf("Tabuleiro gravado com sucesso.\n");
                }
            }
            else
            {
                printf("Comando inválido. Uso: g <ficheiro>\n");
            }
        }
        else if (cmd[0] == 'b' || cmd[0] == 'r')
        {
            char coord[50];
            if (sscanf(cmd, "%*c %49s", coord) == 1)
            {
                if (!modificarTabuleiro(&tabAtual, &hist, cmd[0], coord))
                {
                    printf("Falha ao modificar o tabuleiro.\n");
                }
            }
            else
            {
                printf("Comando inválido. Uso: %c <coordenada>\n", cmd[0]);
            }
        }
        else if (cmd[0] == 'd')
        {
            char cmdChar;
            char coord[50] = {0};
            int parsed = sscanf(cmd, " %c %49s", &cmdChar, coord);

            if (parsed == 2)
                desfazer(&hist, &tabAtual, &tabIO, coord);
            else if (parsed == 1)
                desfazer(&hist, &tabAtual, &tabIO, NULL);
            else
                printf("Comando inválido. Uso: d [<coordenada>]\n");
        }
        else if (cmd[0] == 'v')
        {
            if (verificarRestricoes(&tabAtual))
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