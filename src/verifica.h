#ifndef VERIFICA_H
#define VERIFICA_H

#include "board.h"

typedef struct
{
    int ln, col;
} Coord;

int verificarConectividade(Tabuleiro *tabAtual, char modo);
int verificarRestricoes(Tabuleiro *tabAtual);

#endif // VERIFICA_H
