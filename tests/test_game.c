#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "board.h"
#include "io.h"
#include "game.h"
#include "undo.h"

void test_modificarTabuleiro_pintardebranco(void) {
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

void test_modificarTabuleiro_risca(void) {
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

int main (){
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("Testes_Tabuleiro", NULL, NULL);
    CU_add_test(suite, "Modificar tabuleiro - pintardebranco", test_modificarTabuleiro_pintardebranco);
    CU_add_test(suite, "Modificar tabuleiro - risca", test_modificarTabuleiro_risca);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}
