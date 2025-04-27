#ifndef BOARD_H
#define BOARD_H

#define MAX_SIDE 26

typedef struct
{
    char grelha[MAX_SIDE][MAX_SIDE];
    int linhas, colunas;
} Tabuleiro;

void mostrarTabuleiro(const Tabuleiro *tab);

#endif
