#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include "board.h"
#include "io.h"
#include "game.h"
#include "undo.h"
#include "verifica.h"
#include "solver.h"
#include "tip.h"

int main()
{
    Tabuleiro tabAtual = {0};
    Tabuleiro tabIO = {0};
    Historico hist = {.topo = 0};
    char cmd[256];
    bool a_correr = true;
    bool ganho = false;
    bool loaded = false;

    while (a_correr && !ganho)
    {
        printf("> ");
        if (!fgets(cmd, sizeof(cmd), stdin))
        {
            printf("\033[1;31m ⚠ Erro ao ler comando.\n ⚠ \n\033[0m");
            a_correr = false;
            continue;
        }
        if ((system("clear")))
            printf("\033[1;31m ⚠ failed to clean ⚠ \n\033[0m");

        cmd[strcspn(cmd, "\n")] = '\0';

        if (cmd[0] == 'l')
        {
            char ficheiro[256];
            if (sscanf(cmd, "l %255s", ficheiro) == 1)
            {
                if (carregarTabuleiro(&tabAtual, &tabIO, &hist, ficheiro))
                {
                    printf("Tabuleiro carregado com sucesso.\n");
                    guardar_estado(&hist, &tabAtual);
                    mostrarTabuleiro(&tabAtual);
                    loaded = true;
                }
                else
                {
                    printf("\033[1;31m ⚠ Erro ao carregar o tabuleiro.\n ⚠ \n\033[0m");
                }
            }
            else
            {
                printf("Comando inválido. Uso: l <ficheiro>\n");
            }
        }
        else if (loaded)
        {
            mostrarTabuleiro(&tabAtual);
            if (cmd[0] == 'g')
            {
                char ficheiro[256];
                if (sscanf(cmd, "g %255s", ficheiro) == 1)
                {
                    if (gravarTabuleiro(&tabAtual, ficheiro))
                    {
                        printf("Tabuleiro gravado com sucesso.\n");
                    }
                    else
                    {
                        printf("\033[1;31m ⚠ Erro ao gravar o tabuleiro.\n ⚠ \n\033[0m");
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
                    if (modificarTabuleiro(&tabAtual, &hist, cmd[0], coord))
                    {
                    }
                    else
                    {
                        printf("\033[1;31m ⚠ Erro ao modificar o tabuleiro.\n ⚠ \n\033[0m");
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
                {
                    desfazer(&hist, &tabAtual, &tabIO, coord);
                }

                else if (parsed == 1)
                {
                    desfazer(&hist, &tabAtual, &tabIO, NULL);
                }
                else
                {
                    printf("Comando inválido. Uso: d [<coordenada>]\n");
                }
            }
            else if (cmd[0] == 'v')
            {
                if (verificarRestricoes(&tabAtual))
                {
                    printf("Todas as restrições estão satisfeitas.\n");
                }
                else
                {
                    printf("\033[1;31m ⚠ Existem restrições violadas.\n ⚠ \n\033[0m");
                }
            }
            else if (cmd[0] == 'D')
            {
                bool continuar = true;
                while (continuar)
                {
                    continuar = desfazer(&hist, &tabAtual, &tabIO, NULL);
                }
                if ((system("clear")))
                    printf("\033[1;31m ⚠ failed to clean ⚠ \n\033[0m");
            }
            else if (cmd[0] == 'a')
            {
                comando_a(&tabAtual, &tabIO, &hist);
            }
            else if (cmd[0] == 'A')
            {
                comando_A(&tabAtual, &tabIO, &hist);
            }
            else if (cmd[0] == 'R')
            {
                comando_R(&tabAtual, &tabIO, &hist);
            }
            else if (cmd[0] == 't')
            {
                tecnicas_iniciais(&tabAtual, &tabIO, &hist);
            }
            else if (cmd[0] == 'S')
            {
                solve(&tabAtual, 0, 0);
            }
            else if (loaded)
            {
                printf("\033[1;31m ⚠ Comando inválido.\n ⚠ \n\033[0m");
            }
        }
        else if (cmd[0] == 's')
        {
            a_correr = false;
        }
        else
        {
            printf("\033[1;31m ⚠ Carrega um tabuleiro! Usa: l <ficheiro> ⚠ \n\033[0m");
            printf("\033[1;31m ⚠ Comando 's' para sair do programa. ⚠ \n\n\033[0m");
        }
        if (loaded && ganhou(&tabAtual))
        {
            mostrarTabuleiro(&tabAtual);
            sleep(3);
            ganho = true;
        }
    }

    if (ganho && !system("clear"))
    {
        printf("\033[1;3m ██╗░░░██╗░█████╗░██╗░░░██╗  ░██╗░░░░░░░██╗██╗███╗░░██╗██╗ \033[0m\n");
        printf("\033[1;3m ╚██╗░██╔╝██╔══██╗██║░░░██║  ░██║░░██╗░░██║██║████╗░██║██║ \033[0m\n");
        printf("\033[1;3m ░╚████╔╝░██║░░██║██║░░░██║  ░╚██╗████╗██╔╝██║██╔██╗██║██║ \033[0m\n");
        printf("\033[1;3m ░░╚██╔╝░░██║░░██║██║░░░██║  ░░████╔═████║░██║██║╚████║╚═╝ \033[0m\n");
        printf("\033[1;3m ░░░██║░░░╚█████╔╝╚██████╔╝  ░░╚██╔╝░╚██╔╝░██║██║░╚███║██╗ \033[0m\n");
        printf("\033[1;3m ░░░╚═╝░░░░╚════╝░░╚═════╝░  ░░░╚═╝░░░╚═╝░░╚═╝╚═╝░░╚══╝╚═╝ \033[0m\n");
    }
    return 0;
}