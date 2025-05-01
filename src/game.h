#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "undo.h"

#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "undo.h"
#include <stdbool.h>

bool modificarTabuleiro(Tabuleiro *tabAtual, Historico *hist, char cmd, const char *coord);

#endif // GAME_H

#endif
