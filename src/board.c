#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "board.h"

#define BOARD_DIR "boards/"

void mostrarTabuleiro(const Tabuleiro *tab) {
    for (int i = 0; i < tab->linhas; i++) {
        printf("%s\n", tab->grelha[i]);
    }
}

void guardar_estado(Historico *hist, const Tabuleiro *atual) {
    if (hist->topo < MAX_HISTORY) {
        hist->estados[hist->topo++] = *atual;
    }
}

int carregarTabuleiro(Tabuleiro *tab, Historico *hist, const char *ficheiro) {
    char caminho[512];
    snprintf(caminho, sizeof(caminho), "%s%s", BOARD_DIR, ficheiro);
    FILE *f = fopen(caminho, "r");
    if (!f) return -1;

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
    hist->topo = 0;
    mostrarTabuleiro(tab);
    return 0;
}

int gravarTabuleiro(const Tabuleiro *tab, const char *ficheiro) {
    char caminho[512];
    snprintf(caminho, sizeof(caminho), "%s%s", BOARD_DIR, ficheiro);
    FILE *f = fopen(caminho, "w");
    if (!f) return -1;

    fprintf(f, "%d %d\n", tab->linhas, tab->colunas);
    for (int i = 0; i < tab->linhas; i++) {
        fprintf(f, "%s\n", tab->grelha[i]);
    }
    fclose(f);
    return 0;
}

void modificarTabuleiro(Tabuleiro *tab, Historico *hist, char cmd, const char *coord) {
    int linha = atoi(&coord[1]) - 1;
    int coluna = tolower(coord[0]) - 'a';

    if (linha < 0 || linha >= tab->linhas || coluna < 0 || coluna >= tab->colunas) {
        printf("Coordenada inválida.\n");
        return;
    }

    guardar_estado(hist, tab);

    if (cmd == 'b') {
        tab->grelha[linha][coluna] = toupper(tab->grelha[linha][coluna]);
    } else if (cmd == 'r') {
        tab->grelha[linha][coluna] = '#';
    }

    mostrarTabuleiro(tab);
}

int desfazer(Historico *hist, Tabuleiro *atual) {
    if (hist->topo == 0) {
        printf("Nada para desfazer.\n");
        return 0;
    }

    *atual = hist->estados[--hist->topo];
    mostrarTabuleiro(atual);
    return 1;
}
