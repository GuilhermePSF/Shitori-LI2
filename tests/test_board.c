#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
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

    freopen("boards/output.txt", "w", stdout);
    mostrarTabuleiro(&tabAtual);
    freopen("/dev/tty", "w", stdout);

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

    freopen("boards/output.txt", "w", stdout);
    mostrarTabuleiro(&tabAtual);
    freopen("/dev/tty", "w", stdout);

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

int main()
{
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("Testes_Tabuleiro", NULL, NULL);

    CU_add_test(suite, "Mostrar tabuleiro sem mudanças", test_mostrarTabuleiro_sem_mudancas);
    CU_add_test(suite, "Mostrar tabuleiro com mudanças", test_mostrarTabuleiro_com_mudancas);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return 0;
}
