#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include "generate.h"
#include "board.h"
#include "io.h"
#include "game.h"
#include "undo.h"

void test_random_letra_minuscula(void) {
    srand(0);  
    for (int i = 1; i <= 5; i++) {
        char letra = random_letra_minuscula(i);
        CU_ASSERT_TRUE(letra >= 'a' && letra < ('a' + i));
    }
}

void test_inicializarGerador(void) {
    Tabuleiro tab;
    tab.linhas = 3;
    tab.colunas = 3;

    inicializarGerador(&tab);

    for (int i = 0; i < tab.linhas; i++) {
        for (int j = 0; j < tab.colunas; j++) {
            CU_ASSERT_EQUAL(tab.grelha[i][j], '-');
        }
    }
}

void test_preencherGerador(void) {
    Tabuleiro tab;
    tab.linhas = 3;
    tab.colunas = 3;

    preencherGerador(&tab);

    for (int i = 0; i < tab.linhas; i++) {
        for (int j = 0; j < tab.colunas; j++) {
            CU_ASSERT_TRUE(tab.grelha[i][j] >= 'a' && tab.grelha[i][j] <= 'z');
        }
    }
}


void test_valida_quatro(void) {
    Tabuleiro tab;
    tab.linhas = 4;
    tab.colunas = 4;
    inicializarGerador(&tab);

    tab.grelha[0][2] = 'b';
    tab.grelha[1][2] = 'b';
    tab.grelha[2][2] = 'b';

    // Agora vamos testar a posição (3, 2), que está na coluna com 3 letras 'b'
    CU_ASSERT_FALSE(valida_quatro(&tab, 3, 2, 'b'));
}


void test_ser_resolvivel(void) {
    Tabuleiro tab;
    tab.linhas = 3;
    tab.colunas = 3;

    inicializarGerador(&tab);

    CU_ASSERT_TRUE(ser_resolvivel(&tab, 1, 1, 'a')); 
}

bool test_generate(void) {
    Tabuleiro tab;
    tab.linhas = 4;
    tab.colunas = 4;

    Tabuleiro tabIO;
    tabIO.linhas = 4;
    tabIO.colunas = 4;

    generate(&tab, &tabIO);

    for (int i = 0; i < tab.linhas; i++) {
        for (int j = 0; j < tab.colunas; j++) {
            CU_ASSERT_TRUE(tab.grelha[i][j] >= 'a' && tab.grelha[i][j] <= 'z');

    
        }
    }
}


int main()
{
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("Testes_Generate", NULL, NULL);

    CU_add_test(suite, "Random letra minuscula", test_random_letra_minuscula);
    CU_add_test(suite, "Inicializar gerador", test_inicializarGerador);
    CU_add_test(suite, "Preencher gerador", test_preencherGerador);
    CU_add_test(suite, "Valida quatro", test_valida_quatro);
    CU_add_test(suite, "Ser resolvível", test_ser_resolvivel);
    CU_add_test(suite, "Generate Tabuleiro", test_generate);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return 0;
}