#ifndef UNDO_H
#define UNDO_H

#include "board.h"

#define MAX_HISTORY 100

typedef struct
{
    Tabuleiro estados[MAX_HISTORY];
    int topo;
} Historico;

void guardar_estado(Historico *hist, Tabuleiro *tabAtual);
int desfazer(Historico *hist, Tabuleiro *atual, Tabuleiro *tabIO);

#endif
