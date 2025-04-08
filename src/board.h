#ifndef TABULEIRO_H
#define TABULEIRO_H

#define MAX_ROWS 26
#define MAX_COLS 126

typedef struct {
    char grelha[MAX_ROWS][MAX_COLS];
    int linhas, colunas;
} Tabuleiro;

int carregarTabuleiro(Tabuleiro *tab, const char *ficheiro);
int gravarTabuleiro(Tabuleiro *tab, const char *ficheiro);
void modificarTabuleiro(Tabuleiro *tab, char acao, char *coord);
void mostrarTabuleiro(Tabuleiro *tab);

#endif
