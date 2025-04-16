#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "game.h"

/**
 * @brief Modifies a board cell based on a command and coordinate.
 *
 * Updates the specified cell on the board according to the command: converts the cell to uppercase if the command is 'b', or replaces it with '#' if the command is 'r'. The current board state is saved to history before modification. If the coordinate is invalid, an error message is displayed and no changes are made.
 *
 * @param cmd Command character ('b' for uppercase, 'r' for replacement).
 * @param coord Coordinate string indicating the target cell (e.g., "a1").
 */
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
