#ifndef UNDO_H
#define UNDO_H

#include "board.h"

#define MAX_HISTORY 100

typedef struct
{
    Tabuleiro estados[MAX_HISTORY];
    int topo;
} Historico;

void guardar_estado(Historico *hist, const Tabuleiro *atual);
int desfazer(Historico *hist, Tabuleiro *atual);

#endif
