#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "board.h"
#include "undo.h"
#include "game.h"

void test_desfazer_sem_tabuleiro(void)
{
    Historico hist = {0};
    Tabuleiro tabAtual = {0};
    Tabuleiro tabIO = {0};

    bool resultado = desfazer(&hist, &tabAtual, &tabIO, NULL);
    CU_ASSERT_FALSE(resultado);
}

void test_desfazer_sem_mudancas(void)
{
    Historico hist = {0};
    Tabuleiro tabAtual = {
        .linhas = 3,
        .colunas = 3,
        .grelha = { "abc", "def", "ghi" }};
    Tabuleiro tabIO = tabAtual;

    bool resultado = desfazer(&hist, &tabAtual, &tabIO, NULL);
    CU_ASSERT_FALSE(resultado);
}

void test_desfazer_coordenada_com_mudanca(void)
{
    Historico hist = {0};
    Tabuleiro tabAtual = {
        .linhas = 3,
        .colunas = 3,
        .grelha = { "abc", "dEf", "gh#" }};
    Tabuleiro tabIO = {
        .linhas = 3,
        .colunas = 3,
        .grelha = { "abc", "def", "ghi" }};

    guardar_estado(&hist, &tabAtual);

    bool resultado = desfazer(&hist, &tabAtual, &tabIO, "b2");
    CU_ASSERT_TRUE(resultado);
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[1], "def");
}

void test_desfazer_coordenada_sem_mudanca(void)
{
    Historico hist = {0};
    Tabuleiro tabAtual = {
        .linhas = 3,
        .colunas = 3,
        .grelha = { "abc", "def", "ghi" }};
    Tabuleiro tabIO = tabAtual;

    bool resultado = desfazer(&hist, &tabAtual, &tabIO, "a1");
    CU_ASSERT_FALSE(resultado);
}

void test_desfazer_coordenada_errada(void)
{
    Historico hist = {0};
    Tabuleiro tabAtual = {
        .linhas = 3,
        .colunas = 3,
        .grelha = { "abc", "def", "ghi" }};
    Tabuleiro tabIO = tabAtual;

    bool resultado = desfazer(&hist, &tabAtual, &tabIO, "z9");
    CU_ASSERT_FALSE(resultado);

    resultado = desfazer(&hist, &tabAtual, &tabIO, "1a");
    CU_ASSERT_FALSE(resultado);

    resultado = desfazer(&hist, &tabAtual, &tabIO, "");
    CU_ASSERT_FALSE(resultado);
}

int main()
{
    CU_initialize_registry();

    CU_pSuite suite = CU_add_suite("Testes_Undo", NULL, NULL);

    CU_add_test(suite, "Desfazer sem tabuleiro carregado", test_desfazer_sem_tabuleiro);
    CU_add_test(suite, "Desfazer sem mudanças", test_desfazer_sem_mudancas);
    CU_add_test(suite, "Desfazer coordenada com mudança", test_desfazer_coordenada_com_mudanca);
    CU_add_test(suite, "Desfazer coordenada sem mudança", test_desfazer_coordenada_sem_mudanca);
    CU_add_test(suite, "Desfazer coordenada errada", test_desfazer_coordenada_errada);
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return 0;
}