#include <stdio.h>
#include "board.h"
#include "undo.h"

/**
 * @brief Saves the current board state to the history stack if space is available.
 *
 * If the history is not full, stores a copy of the current board state in the next available slot and advances the history pointer.
 */
void guardar_estado(Historico *hist, const Tabuleiro *atual)
{
    if (hist->topo < MAX_HISTORY)
    {
        hist->estados[hist->topo++] = *atual;
    }
}

/**
 * @brief Restores the previous board state from history to undo the last move.
 *
 * If there are saved states in the history, reverts the current board to the most recent previous state and displays it. If no states are available to undo, prints a message and does nothing.
 *
 * @return int Returns 1 if the undo was successful, or 0 if there was nothing to undo.
 */
int desfazer(Historico *hist, Tabuleiro *atual)
{
    if (hist->topo == 0)
    {
        printf("Nada para desfazer.\n");
        return 0;
    }

    *atual = hist->estados[--hist->topo];
    mostrarTabuleiro(atual);
    return 1;
}
