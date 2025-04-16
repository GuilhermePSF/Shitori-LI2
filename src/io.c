#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "io.h"

#define BOARD_DIR "boards/"

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
