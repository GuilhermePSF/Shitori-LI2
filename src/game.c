#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include "game.h"

bool modificarTabuleiro(Tabuleiro *tabAtual, Historico *hist, char cmd, const char *coord)
{
    int linha = atoi(&coord[1]) - 1;
    int coluna = tolower(coord[0]) - 'a';

    if (linha < 0 || linha >= tabAtual->linhas || coluna < 0 || coluna >= tabAtual->colunas)
    {
        printf("Coordenada inválida.\n");
        return false;
    }

    if (!guardar_estado(hist, tabAtual)) {
        printf("Erro ao guardar estado do tabuleiro.\n");
    return false;
    
    }
    if (cmd == 'b') // Pintar de branco
    {
        if (tabAtual->grelha[linha][coluna] == '#')
        {
            printf("Erro: Não é possível pintar uma posição que já está riscada.\n");
            return false;
        }
        tabAtual->grelha[linha][coluna] = toupper(tabAtual->grelha[linha][coluna]);
    }
    else if (cmd == 'r') // Riscar
    {
        if (isupper(tabAtual->grelha[linha][coluna]))
        {
            printf("Erro: Não é possível riscar uma posição que já está em branco.\n");
            return false;
        }
        tabAtual->grelha[linha][coluna] = '#';
    }
    else
    {
        printf("Comando inválido.\n");
        return false;
    }

    mostrarTabuleiro(tabAtual);
    return true;
}