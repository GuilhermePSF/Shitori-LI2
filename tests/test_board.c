#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "board.h"

void remover_ansi(char *dest, const char *src)
{
    while (*src)
    {
        if (*src == '\033')
        {
            while (*src && *src != 'm')
                src++;
            if (*src)
                src++;
        }
        else
        {
            *dest++ = *src++;
        }
    }
    *dest = '\0';
}

void test_mostrarTabuleiro_sem_mudancas(void)
{
    Tabuleiro tabAtual = {
        .linhas = 3,
        .colunas = 3,
        .grelha = {
            "abc",
            "def",
            "ghi"}};

    if (freopen("boards/output.txt", "w", stdout) == NULL)
    {
        return;
    }
    mostrarTabuleiro(&tabAtual);
    if (freopen("/dev/tty", "w", stdout) == NULL)
    {
        return;
    }

    FILE *file = fopen("boards/output.txt", "r");
    CU_ASSERT_PTR_NOT_NULL(file);

    if (file)
    {
        char buffer[8192];
        char limpo[8192];
        size_t len = fread(buffer, 1, sizeof(buffer) - 1, file);
        buffer[len] = '\0';
        remover_ansi(limpo, buffer);

        CU_ASSERT_PTR_NOT_NULL(strstr(limpo, "SHITORI"));
        CU_ASSERT_PTR_NOT_NULL(strstr(limpo, "1 ║ a ║ b ║ c ║"));
        CU_ASSERT_PTR_NOT_NULL(strstr(limpo, "2 ║ d ║ e ║ f ║"));
        CU_ASSERT_PTR_NOT_NULL(strstr(limpo, "3 ║ g ║ h ║ i ║"));

        fclose(file);
    }
}

void test_mostrarTabuleiro_com_mudancas(void)
{
    Tabuleiro tabAtual = {
        .linhas = 3,
        .colunas = 3,
        .grelha = {
            "abc",
            "d#f",
            "gHi"}};

    if (freopen("boards/output.txt", "w", stdout) == NULL)
    {
        return;
    }
    mostrarTabuleiro(&tabAtual);
    if (freopen("/dev/tty", "w", stdout) == NULL)
    {
        return;
    }

    FILE *file = fopen("boards/output.txt", "r");
    CU_ASSERT_PTR_NOT_NULL(file);

    if (file)
    {
        char buffer[8192];
        char limpo[8192];
        size_t len = fread(buffer, 1, sizeof(buffer) - 1, file);
        buffer[len] = '\0';
        remover_ansi(limpo, buffer);

        CU_ASSERT_PTR_NOT_NULL(strstr(limpo, "SHITORI"));
        CU_ASSERT_PTR_NOT_NULL(strstr(limpo, "2 ║ d ║ # ║ f ║"));
        CU_ASSERT_PTR_NOT_NULL(strstr(limpo, "3 ║ g ║ H ║ i ║"));

        fclose(file);
    }
}

void test_centrarLabel(void)
{
    FILE *file = freopen("boards/output_centrarLabel.txt", "w", stdout);
    CU_ASSERT_PTR_NOT_NULL_FATAL(file);

    centrarLabel(10);
    centrarLabel(5);

    if (freopen("/dev/tty", "w", stdout) == NULL)
    {
        return;
    }

    file = fopen("boards/output_centrarLabel.txt", "r");
    CU_ASSERT_PTR_NOT_NULL_FATAL(file);

    char buffer[256];
    size_t len = fread(buffer, 1, sizeof(buffer) - 1, file);
    buffer[len] = '\0';
    fclose(file);
    CU_ASSERT_STRING_EQUAL(buffer, "          ");
}

void test_mostrarAjuda(void)
{
    FILE *file = freopen("boards/output_ajuda.txt", "w", stdout);
    CU_ASSERT_PTR_NOT_NULL_FATAL(file);

    mostrarAjuda();

    if (freopen("/dev/tty", "w", stdout) == NULL)
    {
        return;
    }

    file = fopen("boards/output_ajuda.txt", "r");
    CU_ASSERT_PTR_NOT_NULL_FATAL(file);

    char buffer[1024];
    size_t len = fread(buffer, 1, sizeof(buffer) - 1, file);
    buffer[len] = '\0';
    fclose(file);

    CU_ASSERT_PTR_NOT_NULL(strstr(buffer, "l <ficheiro>     - Carrega um tabuleiro de um ficheiro"));
    CU_ASSERT_PTR_NOT_NULL(strstr(buffer, "G <tamanho>      - Gera um tabuleiro aleatório (1 a 26)"));
    CU_ASSERT_PTR_NOT_NULL(strstr(buffer, "g <ficheiro>     - Grava o tabuleiro atual para um ficheiro"));
    CU_ASSERT_PTR_NOT_NULL(strstr(buffer, "b <coord>        - Pinta uma célula em branco (ex: b a3)"));
    CU_ASSERT_PTR_NOT_NULL(strstr(buffer, "r <coord>        - Risca uma célula (ex: r b4)"));
    CU_ASSERT_PTR_NOT_NULL(strstr(buffer, "d                - Desfaz o último movimento"));
    CU_ASSERT_PTR_NOT_NULL(strstr(buffer, "d <coord>        - Desfaz um movimento numa coordenada específica"));
    CU_ASSERT_PTR_NOT_NULL(strstr(buffer, "D                - Reverte o tabuleiro para o estado inicial"));
    CU_ASSERT_PTR_NOT_NULL(strstr(buffer, "a                - Aplica ajuda"));
    CU_ASSERT_PTR_NOT_NULL(strstr(buffer, "A                - Aplica todas as ajudas possiveis"));
    CU_ASSERT_PTR_NOT_NULL(strstr(buffer, "v                - Verifica todas as restrições"));
    CU_ASSERT_PTR_NOT_NULL(strstr(buffer, "R                - Resolve o tabuleiro automaticamente"));
    CU_ASSERT_PTR_NOT_NULL(strstr(buffer, "s                - Sai do jogo"));
    CU_ASSERT_PTR_NOT_NULL(strstr(buffer, "──────────────────────────────────────────────\n\n"));
}