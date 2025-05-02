#ifndef UNDO_H
#define UNDO_H
#include <stdbool.h>
#include "board.h"

#define MAX_HISTORY 1000

typedef struct
{
    Tabuleiro estados[MAX_HISTORY];
    int topo;
} Historico;

bool guardar_estado(Historico *hist, Tabuleiro *tabAtual);
bool desfazer(Historico *hist, Tabuleiro *tabAtual, Tabuleiro *tabIO, const char *coord);

#endif
