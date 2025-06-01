#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <ctype.h>
#include <time.h>
#include "board.h"
#include "io.h"
#include "game.h"
#include "undo.h"
#include "verifica.h"
#include "solver.h"
#include "tip.h"
#include "generate.h"

int main()
{
    Tabuleiro tabAtual = {0};
    Tabuleiro tabIO = {0};
    Historico hist = {.topo = 0};
    char cmd[256];
    bool a_correr = true;
    bool ganho = false;
    bool loaded = false;
    bool jogado = false;

    srand(time(NULL));

    printf("\n\033[1;96m📖 LISTA DE COMANDOS DISPONÍVEIS 📖\033[0m\n");
    printf("──────────────────────────────────────────────\n");

    mostrarAjuda();

    while (a_correr && !ganho)
    {
        if (cmd[0] == 'G' && !loaded)
        {
            int size = atoi(&cmd[2]);
            if (size < 1 || size > 26)
            {
                printf("\033[1;31m ⚠ Tamanho inválido. Escolhe um valor entre 1 e 26. ⚠ \n\n\033[0m");
            }
            else
            {
                if (system("clear"))
                    printf("\033[1;31m ⚠ Falha ao limpar o ecrã ⚠ \n\n\033[0m");

                Tabuleiro tab = {.linhas = size, .colunas = size};
                generate(&tab, &tabIO);
                mostrarTabuleiro(&tab);
                guardar_estado(&hist, &tab);
                copiar_tabuleiro_para(&tab, &tabAtual);
                loaded = true;
            }
        }
        else if (cmd[0] == '?')
        {
            if (system("clear"))
                printf("\033[1;31m ⚠ Falha ao limpar o ecrã ⚠ \n\n\033[0m");

            if (loaded)
                mostrarTabuleiro(&tabAtual);
            else
            {
                printf("\n\033[1;96m📖 LISTA DE COMANDOS DISPONÍVEIS 📖\033[0m\n");
                printf("──────────────────────────────────────────────\n");
            }
            mostrarAjuda();
        }
        else if (cmd[0] == 'l')
        {
            char ficheiro[256];
            if ((system("clear")))
                printf("\033[1;31m ⚠ failed to clean ⚠ \n\n\033[0m");

            if (sscanf(cmd, "l %255s", ficheiro) == 1)
            {
                if (carregarTabuleiro(&tabAtual, &tabIO, &hist, ficheiro))
                {
                    mostrarTabuleiro(&tabAtual);
                    printf("\033[1;92m ✓ Tabuleiro carregado com sucesso. ✓\n\n\033[0m");
                    guardar_estado(&hist, &tabAtual);
                    loaded = true;
                }
                else
                {
                    if (loaded)
                        mostrarTabuleiro(&tabAtual);
                    printf("\033[1;31m ⚠ Erro ao carregar o tabuleiro. ⚠ \n\n\033[0m");
                }
            }
            else
            {
                if (loaded)
                    mostrarTabuleiro(&tabAtual);
                printf("\033[1;33m 💡 Comando inválido. Uso: l <ficheiro> 💡\n\n\033[0m");
            }

            if (!loaded)
            {
                if ((system("clear")))
                    printf("\033[1;31m ⚠ failed to clean ⚠ \n\n\033[0m");
                printf("\033[1;31m ⚠ Carrega um tabuleiro! Usa: l <ficheiro> ⚠ \n\033[0m");
                printf("\033[1;31m ⚠ Comando 's' para sair do programa. ⚠ \n\n\033[0m");
            }
        }
        else if (cmd[0] == 's')
        {
            if ((system("clear")))
                    printf("\033[1;31m ⚠ failed to clean ⚠ \n\n\033[0m");
            a_correr = false;
        }
        else if (loaded)
        {
            if ((system("clear")))
                printf("\033[1;31m ⚠ failed to clean ⚠ \n\n\033[0m");

            if (cmd[0] == 'g')
            {
                if (hist.topo == MAX_HISTORY)
                {
                    mostrarTabuleiro(&tabAtual);
                    printf("\033[1;31m ⚠ Aviso: Histórico cheio, não é possível guardar mais estados. ⚠ \n\n\033[0m");
                }

                char ficheiro[256];
                if (sscanf(cmd, "g %255s", ficheiro) == 1)
                {
                    if (gravarTabuleiro(&tabAtual, ficheiro))
                    {
                        mostrarTabuleiro(&tabAtual);
                        printf("\033[1;92m ✓ Tabuleiro gravado com sucesso. ✓\n\n\033[0m");
                    }
                    else
                    {
                        mostrarTabuleiro(&tabAtual);
                        printf("\033[1;31m ⚠ Erro ao gravar o tabuleiro. ⚠ \n\n\033[0m");
                    }
                }
                else
                {
                    mostrarTabuleiro(&tabAtual);
                    printf("\033[1;33m 💡 Comando inválido. Uso: g <ficheiro> 💡\n\n\033[0m");
                }
            }
            else if (cmd[0] == 'b' || cmd[0] == 'r')
            {
                char coord[50];
                if (sscanf(cmd, "%*c %49s", coord) == 1)
                {
                    int linha = atoi(&coord[1]) - 1;
                    int coluna = tolower(coord[0]) - 'a';

                    if (linha < 0 || linha >= tabAtual.linhas || coluna < 0 || coluna >= tabAtual.colunas)
                    {
                        mostrarTabuleiro(&tabAtual);
                        printf("\033[1;31m ⚠ Coordenada inválida. ⚠ \n\n\033[0m");
                    }

                    else if (tabAtual.grelha[linha][coluna] == '#' || isupper(tabAtual.grelha[linha][coluna]))
                    {
                        mostrarTabuleiro(&tabAtual);
                        printf("\033[1;31m ⚠ Erro: Não é possível pintar uma posição que já está riscada. ⚠ \n\n\033[0m");
                    }

                    else if (modificarTabuleiro(&tabAtual, &hist, cmd[0], coord))
                    {
                        mostrarTabuleiro(&tabAtual);
                    }
                    else
                    {
                        mostrarTabuleiro(&tabAtual);
                        printf("\033[1;31m ⚠ Erro ao modificar o tabuleiro.⚠ \n\n\033[0m");
                    }
                }
                else
                {
                    mostrarTabuleiro(&tabAtual);
                    printf("\033[1;33m 💡 Comando inválido. Uso: %c <coordenada> 💡\n\n\033[0m", cmd[0]);
                }
            }
            else if (cmd[0] == 'd')
            {
                char cmdChar;
                char coord[50] = {0};
                int parsed = sscanf(cmd, " %c %49s", &cmdChar, coord);

                if (hist.topo == 0)
                {
                    mostrarTabuleiro(&tabAtual);
                    printf("\033[1;92m ✓ Não há movimentos para desfazer.  ✓\n\n\033[0m");
                }
                else if (parsed == 1)
                {
                    desfazer(&hist, &tabAtual, &tabIO, NULL);
                    mostrarTabuleiro(&tabAtual);
                }
                else if (parsed == 2)
                {
                    int col = tolower(coord[0]) - 'a';
                    int row = atoi(coord + 1) - 1;
                    if ((strlen(coord) < 2 || !isalpha(coord[0]) || !isdigit(coord[1])) && parsed == 2)
                    {
                        printf("\033[1;31m ⚠ Coordenada inválida. ⚠ \n\n\033[0m");
                    }
                    else if ((row < 0 || row >= tabAtual.linhas || col < 0 || col >= tabAtual.colunas) && parsed == 2)
                    {
                        printf("\033[1;31m ⚠ Coordenada fora dos limites. ⚠ \n\n\033[0m");
                    }
                    else
                    {
                        desfazer(&hist, &tabAtual, &tabIO, coord);
                        mostrarTabuleiro(&tabAtual);
                    }
                }
                else
                {
                    mostrarTabuleiro(&tabAtual);
                    printf("\033[1;33m 💡 Comando inválido. Uso: d [<coordenada>] 💡\n\n\033[0m");
                }
            }
            else if (cmd[0] == 'v')
            {
                mostrarTabuleiro(&tabAtual);
                if (verificarRestricoes(&tabAtual, true))
                {
                    printf("\033[1;92m ✓ Todas as restrições estão satisfeitas. ✓\n\n\033[0m");
                }
                else
                {
                    printf("\033[1;31m ⚠ Existem restrições violadas.⚠ \n\n\033[0m");
                }
            }
            else if (cmd[0] == 'D')
            {
                hist.topo = 0;
                copiar_tabuleiro_para(&tabIO, &tabAtual);
                mostrarTabuleiro(&tabAtual);
            }
            else if (cmd[0] == 'a')
            {
                comando_a(&tabAtual, &hist);
                mostrarTabuleiro(&tabAtual);
            }
            else if (cmd[0] == 'A')
            {
                comando_A(&tabAtual, &hist);
                mostrarTabuleiro(&tabAtual);
            }
            else if (cmd[0] == 'R')
            {
                guardar_estado(&hist, &tabAtual);
                if (comando_R(&tabAtual, &hist, false))
                {
                    mostrarTabuleiro(&tabAtual);
                    printf("\033[1;92m ✓ RESOLVIDO COM SUCESSIUM! ✓\n\n\033[0m");
                    sleep(1);
                }
                else
                {
                    mostrarTabuleiro(&tabAtual);
                    printf("\033[1;31m ⚠ Falhou, nao consegue resolver.... ⚠ \n\n\033[0m");
                    sleep(1);
                }
            }
            else if (cmd[0] == 'P')
            {
                comando_R(&tabAtual, &hist, true);
            }
            else if (cmd[0] == 't')
            {
                tecnicas_iniciais(&tabAtual, &hist);
                mostrarTabuleiro(&tabAtual);
            }
            else if (cmd[0] == 'S')
            {
                solve(&tabAtual, 0, 0, false);
                mostrarTabuleiro(&tabAtual);
            }
            else
            {
                if (jogado)
                {
                    if (loaded)
                        mostrarTabuleiro(&tabAtual);
                    printf("\033[1;31m ⚠ Comando inválido. ⚠ \n\n\033[0m");
                }
            }
        }
        else
        {
            if (jogado)
            {
                if (loaded)
                    mostrarTabuleiro(&tabAtual);
                if ((system("clear")))
                    printf("\033[1;31m ⚠ failed to clean ⚠ \n\n\033[0m");
                printf("\033[1;31m ⚠ Comando inválido. ⚠ \n\n\033[0m");
            }
        }

        if (loaded && ganhou(&tabAtual) && !system("clear"))
        {
            mostrarTabuleiro(&tabAtual);
            printf("Pressione Enter para continuar ou d/D para voltar a um estado anterior ...\n> ");

            char buffer[10];
            if (!fgets(buffer, sizeof(buffer), stdin))
            {
                printf("\033[1;31m ⚠ Erro ao ler comando.⚠ \n\n\033[0m");
                a_correr = false;
            }
            else
            {
                if ((system("clear")))
                    printf("\033[1;31m ⚠ failed to clean ⚠ \n\n\033[0m");

                buffer[strcspn(buffer, "\n")] = 0;

                if (buffer[0] == 'd')
                {
                    if (hist.topo == 0)
                    {
                        hist.topo = 0;
                        copiar_tabuleiro_para(&tabIO, &tabAtual);
                        mostrarTabuleiro(&tabAtual);
                    }
                    else
                    {
                        desfazer(&hist, &tabAtual, &tabIO, NULL);
                        mostrarTabuleiro(&tabAtual);
                    }
                }
                else if (buffer[0] == 'D')
                {
                    hist.topo = 0;
                    copiar_tabuleiro_para(&tabIO, &tabAtual);
                    mostrarTabuleiro(&tabAtual);
                }
                else
                {
                    ganho = true;
                    a_correr = false;
                }
            }
        }

        jogado = true;
        if (a_correr && !ganho)
        {
            printf("> ");

            if (!fgets(cmd, sizeof(cmd), stdin))
            {
                printf("\033[1;31m ⚠ Erro ao ler comando.⚠ \n\n\033[0m");
                a_correr = false;
            }
        }
        cmd[strcspn(cmd, "\n")] = '\0';

        if (ganho && !system("clear"))
        {
            printf("\033[1;92m ██╗░░░██╗░█████╗░██╗░░░██╗  ░██╗░░░░░░░██╗██╗███╗░░██╗██╗ \033[0m\n");
            printf("\033[1;92m ╚██╗░██╔╝██╔══██╗██║░░░██║  ░██║░░██╗░░██║██║████╗░██║██║ \033[0m\n");
            printf("\033[1;92m ░╚████╔╝░██║░░██║██║░░░██║  ░╚██╗████╗██╔╝██║██╔██╗██║██║ \033[0m\n");
            printf("\033[1;92m ░░╚██╔╝░░██║░░██║██║░░░██║  ░░████╔═████║░██║██║╚████║╚═╝ \033[0m\n");
            printf("\033[1;92m ░░░██║░░░╚█████╔╝╚██████╔╝  ░░╚██╔╝░╚██╔╝░██║██║░╚███║██╗ \033[0m\n");
            printf("\033[1;92m ░░░╚═╝░░░░╚════╝░░╚═════╝░  ░░░╚═╝░░░╚═╝░░╚═╝╚═╝░░╚══╝╚═╝ \033[0m\n");
            return 0;
        }
    }
}