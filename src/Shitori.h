#ifndef SHITORI_H
#define SHITORI_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_ROWS 26
#define MAX_COLS 126
#define BOARD_DIR "boards/" 

extern char board[MAX_ROWS][MAX_COLS];
extern int rows, cols;

void printBoard();
int loadBoard(const char *filename);
int letterToColumn(char letter);

#endif 