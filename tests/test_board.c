#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "board.h"

// Função auxiliar para remover sequências ANSI
void remover_ansi(char *dest, const char *src) {
    while (*src) {
        if (*src == '\033') {
            while (*src && *src != 'm') src++;
            if (*src) src++;
        } else {
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

    if (freopen("boards/output.txt", "w", stdout) == NULL) {
        return;
    }
    mostrarTabuleiro(&tabAtual);
    if (freopen("/dev/tty", "w", stdout) == NULL) {
        return;
    }

    FILE *file = fopen("boards/output.txt", "r");
    CU_ASSERT_PTR_NOT_NULL(file);

    if (file) {
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

    if (freopen("boards/output.txt", "w", stdout) == NULL) {
        return;
    }
    mostrarTabuleiro(&tabAtual);
    if (freopen("/dev/tty", "w", stdout) == NULL) {
        return;
    }

    FILE *file = fopen("boards/output.txt", "r");
    CU_ASSERT_PTR_NOT_NULL(file);

    if (file) {
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

    if (freopen("/dev/tty", "w", stdout) == NULL) {
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