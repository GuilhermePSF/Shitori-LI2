#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "io.h"

#define BOARD_DIR "boards/"

/**
 * @brief Loads a game board from a file and initializes the board and history.
 *
 * Reads the board dimensions and grid data from a file in the "boards/" directory, resets the history stack, and displays the loaded board.
 *
 * @param tab Pointer to the board structure to populate.
 * @param hist Pointer to the history structure to reset.
 * @param ficheiro Name of the file to load (relative to the "boards/" directory).
 * @return 0 on success, -1 if the file cannot be opened or the format is invalid.
 */
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

/**
 * @brief Saves the current game board to a file.
 *
 * Writes the board's dimensions and grid data to a file in the predefined boards directory.
 *
 * @param ficheiro Name of the file to save the board to, relative to the boards directory.
 * @return int Returns 0 on success, or -1 if the file cannot be opened for writing.
 */
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
