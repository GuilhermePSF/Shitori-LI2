#ifndef SOLVER_H
#define SOLVER_H

#include "board.h"
#include "undo.h"
#include <stdbool.h>

bool regra1_horizontal(Tabuleiro *tabAtual, int linha, int coluna);
bool regra1_vertical(Tabuleiro *tabAtual, int linha, int coluna);
void aplicar_regra1(Tabuleiro *tabAtual, Tabuleiro *tabIO, Historico *hist);

bool regra2_horizontal(Tabuleiro *tabAtual, int linha, int coluna);
bool regra2_vertical(Tabuleiro *tabAtual, int linha, int coluna);
void aplicar_regra2(Tabuleiro *tabAtual, Tabuleiro *tabIO, Historico *hist);

bool regra3_horizontal(Tabuleiro *tabAtual, int linha, int coluna);
bool regra3_vertical(Tabuleiro *tabAtual, int linha, int coluna);
void aplicar_regra3(Tabuleiro *tabAtual, Tabuleiro *tabIO, Historico *hist);

void tecnicas_iniciais(Tabuleiro *tabAtual, Tabuleiro *tabIO, Historico *hist);
bool solve(Tabuleiro *tabAtual, int l, int c);
void comando_R(Tabuleiro *tabAtual, Tabuleiro *tabIO, Historico *hist);

#endif
