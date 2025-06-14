#ifndef TIP_H
#define TIP_H

#include "board.h"
#include "undo.h"

bool tem_riscado_adjacente(const Tabuleiro *tab);
bool tem_riscado_adjacente_coord(const Tabuleiro *tab, int linha, int coluna);
bool existe_maiuscula_igual_na_linha_ou_coluna(Tabuleiro *tab, int linha, int coluna);
bool existe_igual_na_linha_ou_coluna(Tabuleiro *tab, int linha, int coluna);
bool necessaria_para_conectividade(Tabuleiro *tabAtual, int linha, int coluna);
void comando_a(Tabuleiro *tabAtual, Historico *hist);
void comando_A(Tabuleiro *tabAtual, Historico *hist);

#endif
