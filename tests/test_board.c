#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "board.h"
#include "io.h"
#include "game.h"
#include "undo.h"


/**
 * @brief Unit test for loading a valid board from file.
 *
 * Verifies that carregarTabuleiro successfully loads a board from "teste.txt" and that the resulting board has valid dimensions and a non-empty first row.
 */
void test_carregarTabuleiro_valido(void)
{
    Tabuleiro tab;
    Historico hist;
    int resultado = carregarTabuleiro(&tab, &hist, "teste.txt");
    CU_ASSERT_EQUAL(resultado, 0);
    CU_ASSERT(tab.linhas > 0 && tab.colunas > 0);
    CU_ASSERT(strlen(tab.grelha[0]) > 0);
}

/**
 * @brief Unit test for loading an invalid board file.
 *
 * Verifies that carregarTabuleiro returns -1 when attempting to load an invalid board from "tabuleiroerrado.txt", and asserts that the board's dimensions and first row are set to nonzero and non-empty values.
 */
void test_carregarTabuleiro_invalido(void)
{
    Tabuleiro tab;
    Historico hist;
    int resultado = carregarTabuleiro(&tab, &hist, "tabuleiroerrado.txt");
    CU_ASSERT_EQUAL(resultado, -1);
    CU_ASSERT(tab.linhas > 0 && tab.colunas > 0);
    CU_ASSERT(strlen(tab.grelha[0]) > 0);
}

/**
 * @brief Unit test for blocking a cell on the board using modificarTabuleiro.
 *
 * Initializes a 3x3 board, applies the block operation to cell "b2", and asserts that the targeted cell is converted to uppercase.
 */
void test_modificarTabuleiro_bloquear(void)
{
    Tabuleiro tab = {
        .linhas = 3,
        .colunas = 3,
        .grelha = {
            "abc",
            "def",
            "ghi"}};
    Historico hist;
    modificarTabuleiro(&tab, &hist, 'b', "b2"); // Deveria tornar 'e' maiúsculo
    CU_ASSERT_EQUAL(tab.grelha[1][1], 'E');
}

/**
 * @brief Unit test for removing a cell from the board using modificarTabuleiro.
 *
 * Initializes a 3x3 board, applies the remove operation at position "c3", and asserts that the cell is replaced by '#'.
 */
void test_modificarTabuleiro_remover(void)
{
    Tabuleiro tab = {
        .linhas = 3,
        .colunas = 3,
        .grelha = {
            "abc",
            "def",
            "ghi"}};
    Historico hist;
    modificarTabuleiro(&tab, &hist, 'r', "c3"); // Deveria substituir 'i' por '#'
    CU_ASSERT_EQUAL(tab.grelha[2][2], '#');
}

/**
 * @brief Unit test for saving a board to a file.
 *
 * Verifies that gravarTabuleiro correctly writes the board dimensions to the specified file and that the file can be opened and read as expected.
 */
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
        fgets(linha, sizeof(linha), f);
        CU_ASSERT_STRING_EQUAL(linha, "2 3\n");
        fclose(f);
    }
}

/**
 * @brief Runs all unit tests for board and history operations using the CUnit framework.
 *
 * Initializes the CUnit test registry, adds test cases for board loading, modification, and saving, executes the tests in verbose mode, and cleans up the registry.
 *
 * @return int Always returns 0.
 */
int main()
{
    CU_initialize_registry();

    CU_pSuite suite = CU_add_suite("Testes_Tabuleiro", NULL, NULL);

    CU_add_test(suite, "Carregar tabuleiro válido", test_carregarTabuleiro_valido);
    CU_add_test(suite, "Carregar tabuleiro inválido", test_carregarTabuleiro_invalido);
    CU_add_test(suite, "Modificar tabuleiro - bloquear", test_modificarTabuleiro_bloquear);
    CU_add_test(suite, "Modificar tabuleiro - remover", test_modificarTabuleiro_remover);
    CU_add_test(suite, "Gravar tabuleiro", test_gravarTabuleiro);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}
