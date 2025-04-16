#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "io.h"

#define BOARD_DIR "boards/"

int carregarTabuleiro(Tabuleiro *tab, Historico *hist, const char *ficheiro) {
    char caminho[512];
    snprintf(caminho, sizeof(caminho), "%s%s", BOARD_DIR, ficheiro);
    // Check if path was truncated
    if (strlen(BOARD_DIR) + strlen(ficheiro) >= sizeof(caminho)) {
        return -2; // Path too long
    }
    FILE *f = fopen(caminho, "r");
    if (!f) return -1;

    if (fscanf(f, "%d %d", &tab->linhas, &tab->colunas) != 2) {
        fclose(f);
        return -1;
    }
    
    // Validate dimensions
    if (tab->linhas <= 0 || tab->linhas > MAX_LINHAS || 
        tab->colunas <= 0 || tab->colunas > MAX_COLUNAS) {
        fclose(f);
        return -3; // Invalid dimensions
    }

    for (int i = 0; i < tab->linhas; i++) {
        if (fscanf(f, "%s", tab->grelha[i]) != 1) {
            fclose(f);
            return -1;
        }
        // Validate line length
        if (strlen(tab->grelha[i]) != tab->colunas) {
            fclose(f);
            return -4; // Inconsistent line length
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
    // Check if path was truncated
    if (strlen(BOARD_DIR) + strlen(ficheiro) >= sizeof(caminho)) {
        return -2; // Path too long
    }
    FILE *f = fopen(caminho, "w");
    if (!f) return -1;

    if (fprintf(f, "%d %d\n", tab->linhas, tab->colunas) < 0) {
        fclose(f);
        return -3; // Write error
    }
    for (int i = 0; i < tab->linhas; i++) {
        if (fprintf(f, "%s\n", tab->grelha[i]) < 0) {
            fclose(f);
            return -3; // Write error
        }
    }

    fclose(f);
    return 0;
}
