#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "board.h"
#include "undo.h"
#include "game.h"
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <string.h>
#include "board.h"
#include "undo.h"

// Teste: Desfazer sem tabuleiro carregado
void test_desfazer_sem_tabuleiro(void)
{
    Historico hist = {0};
    Tabuleiro tabAtual = {0};
    Tabuleiro tabIO = {0};

    int resultado = desfazer(&hist, &tabAtual, &tabIO, NULL);
    CU_ASSERT_EQUAL(resultado, -1); // Deve falhar porque o histórico está vazio
}

// Teste: Desfazer sem mudanças
void test_desfazer_sem_mudancas(void)
{
    Historico hist = {0};
    Tabuleiro tabAtual = {
        .linhas = 3,
        .colunas = 3,
        .grelha = { "abc", "def", "ghi" }};
    Tabuleiro tabIO = tabAtual;

    int resultado = desfazer(&hist, &tabAtual, &tabIO, NULL);
    CU_ASSERT_EQUAL(resultado, -1); // Também deve falhar, pois não há histórico
}

// Teste: Desfazer célula com mudança
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

    // guarda estado antes da modificação
    guardar_estado(&hist, &tabAtual);

    // desfaz célula modificada 'E' -> 'e'
    int resultado = desfazer(&hist, &tabAtual, &tabIO, "b2");
    CU_ASSERT_EQUAL(resultado, 0);
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[1], "def");
}

// Teste: Desfazer célula sem mudança
void test_desfazer_coordenada_sem_mudanca(void)
{
    Historico hist = {0};
    Tabuleiro tabAtual = {
        .linhas = 3,
        .colunas = 3,
        .grelha = { "abc", "def", "ghi" }};
    Tabuleiro tabIO = tabAtual;

    int resultado = desfazer(&hist, &tabAtual, &tabIO, "a1"); // 'a' == 'a'
    CU_ASSERT_EQUAL(resultado, 1); // Nada para desfazer
}

int main()
{
    CU_initialize_registry();

    CU_pSuite suite = CU_add_suite("Testes_Undo", NULL, NULL);

    CU_add_test(suite, "Desfazer sem tabuleiro carregado", test_desfazer_sem_tabuleiro);
    CU_add_test(suite, "Desfazer sem mudanças", test_desfazer_sem_mudancas);
    CU_add_test(suite, "Desfazer coordenada com mudança", test_desfazer_coordenada_com_mudanca);
    CU_add_test(suite, "Desfazer coordenada sem mudança", test_desfazer_coordenada_sem_mudanca);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return 0;
}