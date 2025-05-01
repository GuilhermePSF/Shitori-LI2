#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "undo.h"

bool modificarTabuleiro(Tabuleiro *tabAtual, Historico *hist, char cmd, const char *coord);

#endif // GAME_H
