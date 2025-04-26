#ifndef BOARD_H
#define BOARD_H

#define MAX_ROWS 26
#define MAX_COLS 26

typedef struct
{
    char grelha[MAX_ROWS][MAX_COLS];
    int linhas, colunas;
} Tabuleiro;

void mostrarTabuleiro(Tabuleiro *tab);

#endif
