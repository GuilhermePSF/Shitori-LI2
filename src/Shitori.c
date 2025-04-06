#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_ROWS 26
#define MAX_COLS 126
#define BOARD_DIR "boards/"  // Diretório onde os arquivos de tabuleiro estão armazenados

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
    // Criar o caminho completo para o ficheiro
    char fullPath[512];
    snprintf(fullPath, sizeof(fullPath), "%s%s", BOARD_DIR, filename);

    FILE *pf = fopen(fullPath, "r");
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

// Função para converter letra para índice de coluna
int letterToColumn(char letter)
{
    return tolower(letter) - 'a';
}

int main()
{
    char command[256];

    printf("Comandos disponíveis:\n");
    printf("  l <ficheiro>       Carregar tabuleiro\n");
    printf("  b <coordenada>     Colocar letra em maiúscula\n");
    printf("  r <coordenada>     Colocar '#' na posição\n");
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
            char coord[50];
            if (sscanf(command, "b %s", coord) == 1)
            {
                if (strlen(coord) > 1) 
                {
                    // A primeira letra é a coluna e o número é a linha
                    char col_char = coord[0];
                    int row_idx = atoi(&coord[1]); // Convertendo o número para índice (começando de 0)
                    int col_idx = letterToColumn(col_char); // Convertendo a letra para índice

                    // Verificando se as coordenadas estão dentro dos limites
                    if (row_idx >= 0 && row_idx < rows && col_idx >= 0 && col_idx < cols)
                    {
                        board[row_idx][col_idx] = toupper(board[row_idx][col_idx]);
                        printBoard();
                    }
                    else
                    {
                        printf("Coordenada fora dos limites do tabuleiro.\n");
                    }
                }
                else
                {
                    printf("Formato da coordenada inválido. Use: letra<número>\n");
                }
            }
        }
        // Se o comando for para riscar (r)
        else if (command[0] == 'r')
        {
            char coord[50];
            if (sscanf(command, "r %s", coord) == 1)
            {
                if (strlen(coord) > 1)
                {
                    // A primeira letra é a coluna e o número é a linha
                    char col_char = coord[0];
                    int row_idx = atoi(&coord[1]); // Convertendo o número para índice (começando de 0)
                    int col_idx = letterToColumn(col_char); // Convertendo a letra para índice

                    // Verificando se as coordenadas estão dentro dos limites
                    if (row_idx >= 0 && row_idx < rows && col_idx >= 0 && col_idx < cols)
                    {
                        board[row_idx][col_idx] = '#';
                        printBoard();
                    }
                    else
                    {
                        printf("Coordenada fora dos limites do tabuleiro.\n");
                    }
                }
                else
                {
                    printf("Formato da coordenada inválido. Use: letra<número>\n");
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
