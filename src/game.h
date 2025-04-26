#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "undo.h"

void modificarTabuleiro(Tabuleiro *tab, Historico *hist, char cmd, char *coord);

#endif
