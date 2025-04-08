#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "board.h"

#define MAX_ROWS 26
#define MAX_COLS 126
#define BOARD_DIR "boards/"  // Diretório onde os arquivos de tabuleiro estão armazenados

int main() {
    Tabuleiro tab;
    char cmd[256];

    while (1) {
        printf("> ");
        if (!fgets(cmd, sizeof(cmd), stdin)) break;
        cmd[strcspn(cmd, "\n")] = '\0';

        if (cmd[0] == 'l') {
            char ficheiro[256];
            if (sscanf(cmd, "l %s", ficheiro) == 1) carregarTabuleiro(&tab, ficheiro);
        } else if (cmd[0] == 'g') {
            char ficheiro[256];
            if (sscanf(cmd, "g %s", ficheiro) == 1) gravarTabuleiro(&tab, ficheiro);
        } else if (cmd[0] == 'b' || cmd[0] == 'r') {
            char coord[50];
            if (sscanf(cmd, "%*c %s", coord) == 1) modificarTabuleiro(&tab, cmd[0], coord);
        } else if (cmd[0] == 's') {
            break;
        } else {
            printf("Comando inválido.\n");
        }
    }
    return 0;
}