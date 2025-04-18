#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "board.h"
#include "verifica.h"

// Teste: Tabuleiro válido (sem violações)
void test_verificarRestricoes_valido(void)
{
    Tabuleiro tab = {
        .linhas = 3,
        .colunas = 3,
        .grelha = {
            "ArB",
            "CDE",
            "FGH"}};

    int resultado = verificarRestricoes(&tab);
    CU_ASSERT_EQUAL(resultado, 1);
}

// Teste: Violação da Regra 1 (letras maiúsculas repetidas na mesma linha)
void test_verificarRestricoes_regra1(void)
{
    Tabuleiro tab = {
        .linhas = 3,
        .colunas = 3,
        .grelha = {
            "A#A",
            "cde",
            "fgh"}};

    int resultado = verificarRestricoes(&tab);
    CU_ASSERT_EQUAL(resultado, 0);
}

// Teste: Violação da Regra 2 (letras maiúsculas repetidas na mesma coluna)
void test_verificarRestricoes_regra2(void)
{
    Tabuleiro tab = {
        .linhas = 3,
        .colunas = 3,
        .grelha = {
            "A#B",
            "A#E",
            "fgh"}};

    int resultado = verificarRestricoes(&tab);
    CU_ASSERT_EQUAL(resultado, 0);
}

// Teste: Violação da Regra 3 (para cada célula riscada todas as casas vizinhas ortogonais têm que estar pintadas a branco)
void test_verificarRestricoes_regra3(void)
{
    Tabuleiro tab = {
        .linhas = 3,
        .colunas = 3,
        .grelha = {
            "A#b",  // <- '#' tem vizinho 'b' à direita (minúscula)
            "CDE",
            "FGH"}};

    int resultado = verificarRestricoes(&tab);
    CU_ASSERT_EQUAL(resultado, 0);
}

// Teste: Célula riscada com vizinhos válidos
void test_verificarRestricoes_riscada_valida(void)
{
    Tabuleiro tab = {
        .linhas = 3,
        .colunas = 3,
        .grelha = {
            "A#B",
            "CDE",
            "FGH"}};

    // Ajusta os vizinhos da célula riscada para serem válidos
    tab.grelha[0][0] = 'A'; // Vizinho esquerdo
    tab.grelha[0][2] = 'B'; // Vizinho direito

    int resultado = verificarRestricoes(&tab);
    CU_ASSERT_EQUAL(resultado, 1);
}

// Teste: Tabuleiro vazio
void test_verificarRestricoes_tabuleiro_vazio(void)
{
    Tabuleiro tab = {
        .linhas = 0,
        .colunas = 0,
        .grelha = {""}};

    int resultado = verificarRestricoes(&tab);
    CU_ASSERT_EQUAL(resultado, 1);
}


int main()
{
    CU_initialize_registry();

    CU_pSuite suite = CU_add_suite("Testes_VerificarRestricoes", NULL, NULL);

    CU_add_test(suite, "Tabuleiro válido", test_verificarRestricoes_valido);
    CU_add_test(suite, "Violação da Regra 1", test_verificarRestricoes_regra1);
    CU_add_test(suite, "Violação da Regra 2", test_verificarRestricoes_regra2);
    CU_add_test(suite, "Violação da Regra 3", test_verificarRestricoes_regra3);
    CU_add_test(suite, "Célula riscada com vizinhos válidos", test_verificarRestricoes_riscada_valida);
    CU_add_test(suite, "Tabuleiro vazio", test_verificarRestricoes_tabuleiro_vazio);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return 0;
}