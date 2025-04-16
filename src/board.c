#include <stdio.h>
#include "board.h"

/**
 * @brief Prints the current state of the board to standard output.
 *
 * Each row of the board is printed on a separate line.
 *
 * @param tab Pointer to the board structure containing the grid to display.
 */
void mostrarTabuleiro(const Tabuleiro *tab) {
    for (int i = 0; i < tab->linhas; i++) {
        printf("%s\n", tab->grelha[i]);
    }
}
