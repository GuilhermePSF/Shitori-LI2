#ifndef BOARD_H
#define BOARD_H

#define MAX_ROWS 26
#define MAX_COLS 126
#define MAX_HISTORY 100

typedef struct
{
    char grelha[MAX_ROWS][MAX_COLS];
    int linhas, colunas;
} Tabuleiro;

typedef struct
{
    Tabuleiro estados[MAX_HISTORY];
    int topo;
} Historico;

void mostrarTabuleiro(const Tabuleiro *tab);
int carregarTabuleiro(Tabuleiro *tab, Historico *hist, const char *ficheiro);
int gravarTabuleiro(const Tabuleiro *tab, const char *ficheiro);
void modificarTabuleiro(Tabuleiro *tab, Historico *hist, char acao, const char *coord);
int desfazer(Historico *hist, Tabuleiro *atual);

#endif
