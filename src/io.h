
#ifndef IO_H
#define IO_H

#include "board.h"
#include "undo.h"

int carregarTabuleiro(Tabuleiro *tab, Historico *hist, char *ficheiro);
int gravarTabuleiro(Tabuleiro *tab, char *ficheiro);

#endif
