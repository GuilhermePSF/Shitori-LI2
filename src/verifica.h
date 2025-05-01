#ifndef VERIFICA_H
#define VERIFICA_H

#include "board.h"
#include <stdbool.h>

typedef struct
{
    int ln, col;
} Coord;

bool verificarRestricoes(Tabuleiro *tabAtual);

#endif // VERIFICA_H
