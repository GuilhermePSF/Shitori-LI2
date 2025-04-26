#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "game.h"

void modificarTabuleiro(Tabuleiro *tab, Historico *hist, char cmd, char *coord)
{
    int linha = atoi(&coord[1]) - 1;
    int coluna = tolower(coord[0]) - 'a';

    // Verifica se a coordenada está dentro dos limites do tabuleiro
    if (linha < 0 || linha >= tab->linhas || coluna < 0 || coluna >= tab->colunas)
    {
        printf("Coordenada inválida.\n");
        return;
    }

    // Salva o estado atual do tabuleiro no histórico
    guardar_estado(hist, tab);

    if (cmd == 'b') // Pintar de branco
    {
        if (tab->grelha[linha][coluna] == '#')
        {
            printf("Erro: Não é possível pintar uma posição que já está riscada.\n");
            return;
        }
        tab->grelha[linha][coluna] = toupper(tab->grelha[linha][coluna]);
    }
    else if (cmd == 'r') // Riscar
    {
        if (isupper(tab->grelha[linha][coluna]))
        {
            printf("Erro: Não é possível riscar uma posição que já está em branco.\n");
            return;
        }
        tab->grelha[linha][coluna] = '#';
    }

    // Mostra o tabuleiro atualizado
    mostrarTabuleiro(tab);
}