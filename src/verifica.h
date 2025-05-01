#ifndef VERIFICA_H
#define VERIFICA_H

#include "board.h"

typedef struct
{
    int ln, col;
} Coord;

int verificarRestricoes(Tabuleiro *tabAtual);

#endif // VERIFICA_H
