#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "board.h"

// Teste: Mostrar tabuleiro sem estar carregado
void test_mostrarTabuleiro_sem_carregar(void)
{
    Tabuleiro tabAtual = {0}; // Tabuleiro não inicializado

    // Redireciona a saída padrão para um arquivo temporário
    freopen("boards/output.txt", "w", stdout);
    mostrarTabuleiro(&tabAtual);
    freopen("/dev/tty", "w", stdout); // Restaura a saída padrão

    // Verifica o conteúdo do arquivo
    FILE *file = fopen("boards/output.txt", "r");
    CU_ASSERT_PTR_NOT_NULL(file);
    if (file)
    {
        char linha[10];
        CU_ASSERT_PTR_NULL(fgets(linha, sizeof(linha), file));
        fclose(file);
    }
}

// Teste: Mostrar tabuleiro sem mudanças do original
void test_mostrarTabuleiro_sem_mudancas(void)
{
    Tabuleiro tabAtual = {
        .linhas = 3,
        .colunas = 3,
        .grelha = {
            "abc",
            "def",
            "ghi"}};

    // Redireciona a saída padrão para um arquivo temporário
    freopen("output.txt", "w", stdout);
    mostrarTabuleiro(&tabAtual);
    freopen("/dev/tty", "w", stdout); // Restaura a saída padrão

    // Verifica o conteúdo do arquivo
    FILE *file = fopen("output.txt", "r");
    CU_ASSERT_PTR_NOT_NULL(file);
    if (file)
    {
        char linha[10];
        fgets(linha, sizeof(linha), file);
        CU_ASSERT_STRING_EQUAL(linha, "abc\n");
        fgets(linha, sizeof(linha), file);
        CU_ASSERT_STRING_EQUAL(linha, "def\n");
        fgets(linha, sizeof(linha), file);
        CU_ASSERT_STRING_EQUAL(linha, "ghi\n");
        fclose(file);
    }
}

// Teste: Mostrar tabuleiro com mudanças do original
void test_mostrarTabuleiro_com_mudancas(void)
{
    Tabuleiro tabAtual = {
        .linhas = 3,
        .colunas = 3,
        .grelha = {
            "abc",
            "d#f",
            "gHi"}};

    // Redireciona a saída padrão para um arquivo temporário
    freopen("output.txt", "w", stdout);
    mostrarTabuleiro(&tabAtual);
    freopen("/dev/tty", "w", stdout);

    // Verifica o conteúdo do arquivo
    FILE *file = fopen("output.txt", "r");
    CU_ASSERT_PTR_NOT_NULL(file);
    if (file)
    {
        char linha[10];
        fgets(linha, sizeof(linha), file);
        CU_ASSERT_STRING_EQUAL(linha, "abc\n");
        fgets(linha, sizeof(linha), file);
        CU_ASSERT_STRING_EQUAL(linha, "d#f\n");
        fgets(linha, sizeof(linha), file);
        CU_ASSERT_STRING_EQUAL(linha, "gHi\n");
        fclose(file);
    }
}

int main()
{
    CU_initialize_registry();

    CU_pSuite suite = CU_add_suite("Testes_Tabuleiro", NULL, NULL);

    CU_add_test(suite, "Mostrar tabuleiro sem mudanças", test_mostrarTabuleiro_sem_mudancas);
    CU_add_test(suite, "Mostrar tabuleiro com mudanças", test_mostrarTabuleiro_com_mudancas);
    CU_add_test(suite, "Mostrar tabuleiro sem carregar", test_mostrarTabuleiro_sem_carregar);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return 0;
}