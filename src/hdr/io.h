
#ifndef IO_H
#define IO_H

#include "board.h"
#include "undo.h"

bool carregarTabuleiro(Tabuleiro *tabAtual, Tabuleiro *tabIO, Historico *hist, char *ficheiro);
bool gravarTabuleiro(Tabuleiro *tabAtual, char *ficheiro);

#endif // IO_H