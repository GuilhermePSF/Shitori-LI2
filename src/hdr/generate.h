// generate.h
#ifndef GENERATE_H
#define GENERATE_H

#include <stdbool.h>
#include "board.h"

char random_letra_minuscula(int side);

void inicializarGerador(Tabuleiro *tab);

bool ser_resolvivel(Tabuleiro *tab, int l, int c, char sub);

bool generate(Tabuleiro *tab, Tabuleiro *tabIO /*, int l, int c*/);

#endif // GENERATE_H
