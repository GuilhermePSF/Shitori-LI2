
#ifndef IO_H
#define IO_H

#include "board.h"
#include "undo.h"

int carregarTabuleiro(Tabuleiro *tab, Historico *hist, const char *ficheiro);
int gravarTabuleiro(const Tabuleiro *tab, const char *ficheiro);

#endif
