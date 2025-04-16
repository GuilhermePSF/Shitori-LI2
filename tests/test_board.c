#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdio.h>
#include <string.h>
#include "board.h"

void test_carregarTabuleiro_valido(void) {
    Tabuleiro tab;
    int resultado = carregarTabuleiro(&tab, "teste.txt");  
    CU_ASSERT_EQUAL(resultado, 0);
    CU_ASSERT(tab.linhas > 0 && tab.colunas > 0);
    CU_ASSERT(strlen(tab.grelha[0]) > 0);
}

void test_carregarTabuleiro_invalido(void) {
    Tabuleiro tab;
    int resultado = carregarTabuleiro(&tab, "tabuleiroerrado.txt");
    CU_ASSERT_EQUAL(resultado, -1);
}

void test_modificarTabuleiro_pintardebranco(void) {
    Tabuleiro tab = {
        .linhas = 3,
        .colunas = 3,
        .grelha = {
            "abc",
            "def",
            "ghi"
        }
    };
    modificarTabuleiro(&tab, 'b', "b2"); // Deveria tornar 'e' maiúsculo
    CU_ASSERT_EQUAL(tab.grelha[1][1], 'E');
}

void test_modificarTabuleiro_risca(void) {
    Tabuleiro tab = {
        .linhas = 3,
        .colunas = 3,
        .grelha = {
            "abc",
            "def",
            "ghi"
        }
    };
    modificarTabuleiro(&tab, 'r', "c3"); // Deveria substituir 'i' por '#'
    CU_ASSERT_EQUAL(tab.grelha[2][2], '#');
}

void test_gravarTabuleiro(void) {
    Tabuleiro tab = {
        .linhas = 2,
        .colunas = 3,
        .grelha = {
            "abc",
            "def"
        }
    };

    int resultado = gravarTabuleiro(&tab, "saida_test.txt");
    CU_ASSERT_EQUAL(resultado, 0);

    FILE *f = fopen("boards/saida_test.txt", "r");
    CU_ASSERT_PTR_NOT_NULL(f);
    if (f) {
        char linha[10];
        fgets(linha, sizeof(linha), f);
        CU_ASSERT_STRING_EQUAL(linha, "2 3\n");
        fclose(f);
    }
}

int main() {
    CU_initialize_registry();

    CU_pSuite suite = CU_add_suite("Testes_Tabuleiro", NULL, NULL);

    CU_add_test(suite, "Carregar tabuleiro válido", test_carregarTabuleiro_valido);
    CU_add_test(suite, "Carregar tabuleiro inválido", test_carregarTabuleiro_invalido);
    CU_add_test(suite, "Modificar tabuleiro - pintardebranco", test_modificarTabuleiro_pintardebranco);
    CU_add_test(suite, "Modificar tabuleiro - risca", test_modificarTabuleiro_risca);
    CU_add_test(suite, "Gravar tabuleiro", test_gravarTabuleiro);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}
