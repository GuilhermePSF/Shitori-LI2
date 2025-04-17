#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "board.h"
#include "io.h"
#include "game.h"
#include "undo.h"

void test_carregarTabuleiro_valido(void)
{
    Tabuleiro tab;
    Historico hist;
    int resultado = carregarTabuleiro(&tab, &hist, "teste.txt");
    CU_ASSERT_EQUAL(resultado, 0);
    CU_ASSERT(tab.linhas > 0 && tab.colunas > 0);
    CU_ASSERT(strlen(tab.grelha[0]) > 0);
}

void test_carregarTabuleiro_invalido(void)
{
    Tabuleiro tab;
    Historico hist;
    int resultado = carregarTabuleiro(&tab, &hist, "tabuleiroerrado.txt");
    CU_ASSERT_EQUAL(resultado, -1);
}

void test_gravarTabuleiro(void)
{
    Tabuleiro tab = {
        .linhas = 2,
        .colunas = 3,
        .grelha = {
            "abc",
            "def"}};

    int resultado = gravarTabuleiro(&tab, "saida_test.txt");
    CU_ASSERT_EQUAL(resultado, 0);

    FILE *f = fopen("boards/saida_test.txt", "r");
    CU_ASSERT_PTR_NOT_NULL(f);
    if (f)
    {
        char linha[10];
        if (fgets(linha, sizeof(linha), f) == NULL)
        {
            fprintf(stderr, "Erro ao ler linha do arquivo\n");
        }

        CU_ASSERT_STRING_EQUAL(linha, "2 3\n");
        fclose(f);
    }
}

int main()
{
    CU_initialize_registry();

    CU_pSuite suite = CU_add_suite("Testes_Tabuleiro", NULL, NULL);

    CU_add_test(suite, "Carregar tabuleiro válido", test_carregarTabuleiro_valido);
    CU_add_test(suite, "Carregar tabuleiro inválido", test_carregarTabuleiro_invalido);
    CU_add_test(suite, "Gravar tabuleiro", test_gravarTabuleiro);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}
