#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "board.h"
#include "undo.h"
#include "game.h"

// Teste: Desfazer sem tabuleiro carregado
void test_desfazer_sem_tabuleiro(void)
{
    Historico hist = {0};
    Tabuleiro tab = {0}; // Tabuleiro não inicializado

    int resultado = desfazer(&hist, &tab);
    CU_ASSERT_EQUAL(resultado, 0); // Não deve ser possível desfazer
}

// Teste: Desfazer sem mudanças
void test_desfazer_sem_mudancas(void)
{
    Historico hist = {0};
    Tabuleiro tab = {
        .linhas = 3,
        .colunas = 3,
        .grelha = {
            "abc",
            "def",
            "ghi"}};

    int resultado = desfazer(&hist, &tab);
    CU_ASSERT_EQUAL(resultado, 0); // Não deve ser possível desfazer
}

// Teste: Desfazer com a última mudança tendo uma mudança anterior
void test_desfazer_com_mudanca_anterior(void)
{
    Historico hist = {0};
    Tabuleiro tab = {
        .linhas = 3,
        .colunas = 3,
        .grelha = {
            "abc",
            "def",
            "ghi"}};

    // Salva o estado inicial
    guardar_estado(&hist, &tab);

    // Realiza uma mudança
    modificarTabuleiro(&tab, &hist, 'b', "b2"); // Modifica 'e' -> 'E'

    // Realiza outra mudança
    modificarTabuleiro(&tab, &hist, 'r', "c3"); // Modifica 'i' -> '#'

    // Desfaz a última mudança
    int resultado = desfazer(&hist, &tab);
    CU_ASSERT_EQUAL(resultado, 1); 
    CU_ASSERT_STRING_EQUAL(tab.grelha[1], "dEf"); 
    CU_ASSERT_STRING_EQUAL(tab.grelha[2], "ghi"); 
}

// Teste: Desfazer com a última mudança não sendo o último comando
void test_desfazer_com_mudanca_nao_ultima(void)
{
    Historico hist = {0};
    Tabuleiro tab = {
        .linhas = 3,
        .colunas = 3,
        .grelha = {
            "abc",
            "def",
            "ghi"}};

    // Salva o estado inicial
    guardar_estado(&hist, &tab);

    // Realiza uma mudança
    modificarTabuleiro(&tab, &hist, 'b', "b2"); // Modifica 'e' -> 'E'

    // Realiza outra mudança
    modificarTabuleiro(&tab, &hist, 'r', "c3"); // Modifica 'i' -> '#'


    // Desfaz a última mudança
    int resultado = desfazer(&hist, &tab);
    CU_ASSERT_EQUAL(resultado, 1);
    CU_ASSERT_STRING_EQUAL(tab.grelha[1], "dEf"); 
    CU_ASSERT_STRING_EQUAL(tab.grelha[2], "ghi");
}

// Teste: Desfazer com intervalos entre as mudanças
void test_desfazer_com_intervalos(void)
{
    Historico hist = {0};
    Tabuleiro tab = {
        .linhas = 3,
        .colunas = 3,
        .grelha = {
            "abc",
            "def",
            "ghi"}};

    // Salva o estado inicial
    guardar_estado(&hist, &tab);

    // Realiza uma mudança
    modificarTabuleiro(&tab, &hist, 'r', "b2"); // Modifica 'e' -> '#'

    // Realiza outra mudança
    modificarTabuleiro(&tab, &hist, 'b', "c3"); // Modifica 'i' -> 'I'

    // Realiza outra mudança
    modificarTabuleiro(&tab, &hist, 'b', "a1"); // Modifica 'a' -> 'A'

    // Desfaz a última mudança
    int resultado = desfazer(&hist, &tab);
    CU_ASSERT_EQUAL(resultado, 1); 
    CU_ASSERT_STRING_EQUAL(tab.grelha[0], "abc"); 
    CU_ASSERT_STRING_EQUAL(tab.grelha[1], "d#f"); 
    CU_ASSERT_STRING_EQUAL(tab.grelha[2], "ghI"); 
}

int main()
{
    CU_initialize_registry();

    CU_pSuite suite = CU_add_suite("Testes_Undo", NULL, NULL);

    CU_add_test(suite, "Desfazer sem tabuleiro carregado", test_desfazer_sem_tabuleiro);
    CU_add_test(suite, "Desfazer sem mudanças", test_desfazer_sem_mudancas);
    CU_add_test(suite, "Desfazer com mudança anterior", test_desfazer_com_mudanca_anterior);
    CU_add_test(suite, "Desfazer com mudança não última", test_desfazer_com_mudanca_nao_ultima);
    CU_add_test(suite, "Desfazer com intervalos", test_desfazer_com_intervalos);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return 0;
}