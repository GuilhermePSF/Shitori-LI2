#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "game.h"

void modificarTabuleiro(Tabuleiro *tabAtual, Historico *hist, char cmd, const char *coord)
{
    int linha = atoi(&coord[1]) - 1;
    int coluna = tolower(coord[0]) - 'a';

    // Verifica se a coordenada está dentro dos limites do tabuleiro
    if (linha < 0 || linha >= tabAtual->linhas || coluna < 0 || coluna >= tabAtual->colunas)
    {
        printf("Coordenada inválida.\n");
        return;
    }

    // Salva o estado atual do tabuleiro no histórico
    guardar_estado(hist, tabAtual);

    if (cmd == 'b') // Pintar de branco
    {
        if (tabAtual->grelha[linha][coluna] == '#')
        {
            printf("Erro: Não é possível pintar uma posição que já está riscada.\n");
            return;
        }
        tabAtual->grelha[linha][coluna] = toupper(tabAtual->grelha[linha][coluna]);
    }
    else if (cmd == 'r') // Riscar
    {
        if (isupper(tabAtual->grelha[linha][coluna]))
        {
            printf("Erro: Não é possível riscar uma posição que já está em branco.\n");
            return;
        }
        tabAtual->grelha[linha][coluna] = '#';
    }

    // Mostra o tabuleiro atualizado
    mostrarTabuleiro(tabAtual);
}