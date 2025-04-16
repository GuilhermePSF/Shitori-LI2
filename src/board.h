#ifndef BOARD_H
#define BOARD_H

#define MAX_ROWS 26
#define MAX_COLS 126

typedef struct {
    char grelha[MAX_ROWS][MAX_COLS];
    int linhas, colunas;
} Tabuleiro;

void mostrarTabuleiro(const Tabuleiro *tab);

#endif
