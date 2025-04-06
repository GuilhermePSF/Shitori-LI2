#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_ROWS 26
#define MAX_COLS 126

char board[MAX_ROWS][MAX_COLS];
int rows = 0, cols = 0;

// Função para imprimir o tabuleiro
void printBoard()
{
    int i, j;
    printf("Tabuleiro atual:\n");
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Função para carregar o tabuleiro de um ficheiro
int loadBoard(const char *filename)
{
    FILE *pf = fopen(filename, "r");
    if (pf == NULL)
    {
        perror("Erro ao abrir o ficheiro");
        return -1;
    }

    rows = 0;
    char line[256];
    while (fgets(line, sizeof(line), pf) && rows < MAX_ROWS)
    {
        // Remove o '\n' se existir
        line[strcspn(line, "\n")] = '\0';
        cols = strlen(line);
        // Copia os caracteres para o tabuleiro
        for (int j = 0; j < cols; j++)
        {
            board[rows][j] = line[j];
        }
        rows++;
    }

    fclose(pf);
    return 0;
}

int main()
{
    char command[256];

    printf("Comandos disponíveis:\n");
    printf("  l <ficheiro>       Carregar tabuleiro\n");
    printf("  b <linha,coluna>   Colocar letra em maiúscula\n");
    printf("  r <linha,coluna>   Colocar '#' na posição\n");
    printf("Digite os comandos:\n\n");

    while (fgets(command, sizeof(command), stdin) != NULL)
    {
        // Remove o '\n'
        command[strcspn(command, "\n")] = '\0';

        // Se o comando for para carregar o tabuleiro
        if (command[0] == 'l')
        {
            char filename[256];
            if (sscanf(command, "l %s", filename) == 1)
            {
                if (loadBoard(filename) == 0)
                {
                    printf("Tabuleiro carregado a partir de %s\n", filename);
                    printBoard();
                }
            }
            else
            {
                printf("Formato do comando inválido. Use: l <ficheiro>\n");
            }
        }
        // Se o comando for para pintar (b)
        else if (command[0] == 'b')
        {
            int r_idx, c_idx;
            char coord[50];
            if (sscanf(command, "b %s", coord) == 1)
            {
                if (sscanf(coord, "%d,%d", &r_idx, &c_idx) == 2)
                {
                    if (r_idx >= 0 && r_idx < rows && c_idx >= 0 && c_idx < cols)
                    {
                        board[r_idx][c_idx] = toupper(board[r_idx][c_idx]);
                        printBoard();
                    }
                    else
                    {
                        printf("Coordenada fora dos limites do tabuleiro.\n");
                    }
                }
                else
                {
                    printf("Formato da coordenada inválido. Use: linha,coluna\n");
                }
            }
        }
        // Se o comando for para riscar (r)
        else if (command[0] == 'r')
        {
            int r_idx, c_idx;
            char coord[50];
            if (sscanf(command, "r %s", coord) == 1)
            {
                if (sscanf(coord, "%d,%d", &r_idx, &c_idx) == 2)
                {
                    if (r_idx >= 0 && r_idx < rows && c_idx >= 0 && c_idx < cols)
                    {
                        board[r_idx][c_idx] = '#';
                        printBoard();
                    }
                    else
                    {
                        printf("Coordenada fora dos limites do tabuleiro.\n");
                    }
                }
                else
                {
                    printf("Formato da coordenada inválido. Use: linha,coluna\n");
                }
            }
        }
        // Se o comando não for reconhecido
        else
        {
            printf("Comando não reconhecido.\n");
        }
    }

    return 0;
}
