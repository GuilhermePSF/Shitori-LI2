
#ifndef IO_H
#define IO_H

#include "board.h"
#include "undo.h"

int carregarTabuleiro(Tabuleiro *tabAtual, Tabuleiro *tabIO, Historico *hist, char *ficheiro);
int gravarTabuleiro(Tabuleiro *tabAtual, char *ficheiro);

#endif
