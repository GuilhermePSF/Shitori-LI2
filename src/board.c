#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_ROWS 26
#define MAX_COLS 126
#define BOARD_DIR "boards/"  // Diretório onde os arquivos de tabuleiro estão armazenados

typedef struct {
    char grelha[MAX_ROWS][MAX_COLS];
    int linhas, colunas;
} Tabuleiro;

void mostrarTabuleiro(Tabuleiro *tab) {
    for (int i = 0; i < tab->linhas; i++) {
        printf("%s\n", tab->grelha[i]);
    }
}

int carregarTabuleiro(Tabuleiro *tab, const char *ficheiro) {
    char caminho[512];
    snprintf(caminho, sizeof(caminho), "%s%s", BOARD_DIR, ficheiro);
    FILE *f = fopen(caminho, "r");
    if (f == NULL) return -1;

    if (fscanf(f, "%d %d", &tab->linhas, &tab->colunas) != 2) {
    fclose(f);
    return -1;
}

    for (int i = 0; i < tab->linhas; i++) {
    if (fscanf(f, "%s", tab->grelha[i]) != 1) {
        fclose(f);
        return -1;
    }
}

    fclose(f);
    mostrarTabuleiro(tab);
    return 0;
}

int gravarTabuleiro(Tabuleiro *tab, const char *ficheiro) {
    char caminho[512];
    snprintf(caminho, sizeof(caminho), "%s%s", BOARD_DIR, ficheiro);
    FILE *f = fopen(caminho, "w");
    if (f == NULL) return -1;

    fprintf(f, "%d %d\n", tab->linhas, tab->colunas);
    for (int i = 0; i < tab->linhas; i++) {
        fprintf(f, "%s\n", tab->grelha[i]);
    }
    fclose(f);
    return 0;
}

void modificarTabuleiro(Tabuleiro *tab, char acao, char *coord) {
    int linha = atoi(&coord[1]) - 1;
    int coluna = tolower(coord[0]) - 'a';

    if (linha < 0 || linha >= tab->linhas || coluna < 0 || coluna >= tab->colunas) {
        printf("Coordenada inválida.\n");
        return;
    }

    tab->grelha[linha][coluna] = (acao == 'b') ? toupper(tab->grelha[linha][coluna]) : '#';
    mostrarTabuleiro(tab);
}

