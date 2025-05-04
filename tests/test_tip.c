#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdbool.h>
#include "tip.h"
#include "board.h"
#include "io.h"
#include "game.h"

void test_comando_a_sem_modificacoes(void)
{
    Tabuleiro tabAtual = {
        .linhas = 3,
        .colunas = 3,
        .grelha = {
            "ABC",
            "DEF",
            "GHI"
        }
    };
    Tabuleiro tabIO = tabAtual;
    Historico hist = {0};

    comando_a(&tabAtual, &tabIO, &hist);

    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[0], "ABC");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[1], "DEF");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[2], "GHI");
}

void test_comando_a_com_tabuleiro5x5(void)
{
    Tabuleiro tabAtual = {
        .linhas = 5,
        .colunas = 5,
        .grelha = {
            "ecadC",
            "dcdec",
            "bddce",
            "cdeeb",
            "accbb"
        }
    };
    Tabuleiro tabIO = tabAtual;
    Historico hist = {0};

    comando_a(&tabAtual, &tabIO, &hist);

    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[0], "E#ADC");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[1], "DC#E#");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[2], "BdDCE");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[3], "Cde#B");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[4], "A#CB#");
}

void test_comando_a_com_tabuleiro_12x12(void)
{
    Tabuleiro tabAtual = {
        .linhas = 12,
        .colunas = 12,
        .grelha = {
            "bbeegigldbch",
            "cbfhefjaeijb",
            "ekfcalfgidhj",
            "ejgligalflki",
            "aggbdcckbfbi",
            "ijkcjebclagd",
            "eeckkjaijlea",
            "heabbcdekgli",
            "bldehgeffkac",
            "hcbklckcggjg",
            "kgiglfehcbdl",
            "dihjfkhbicge"
        }
    };
    Tabuleiro tabIO = tabAtual;
    Historico hist = {0};

    comando_a(&tabAtual, &tabIO, &hist);

    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[0], "bbeegIglDbCH");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[1], "CbfHefjAeIjb");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[2], "eKfcALfGiDHJ");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[3], "ejgligalflKi");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[4], "AggbDccKbFbi");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[5], "IjKcjEBcLAgD");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[6], "eeCkkjaIjlea");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[7], "heAbbcDeKgLi");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[8], "bLDeHgeffKAC");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[9], "hcBklckcggjg");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[10], "KgIglfeHCbDl");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[11], "DihJFKhBiCgE");
}

void test_comando_a_com_tabuleiro_apos_riscar(void)
{
    Tabuleiro tabAtual = {
        .linhas = 12,
        .colunas = 12,
        .grelha = {
            "bbeegigldbch",
            "cbfhefjaeijb",
            "ekfcalfgidhj",
            "ejgligalflki",
            "aggbdcckbfbi",
            "ijkcjebclagd",
            "eeckkjaijlea",
            "heabbcdekgli",
            "bldehgeffkac",
            "hcbklckcggjg",
            "kgiglfehcbdl",
            "dihjfkhbicge"
        }
    };
    Tabuleiro tabIO = tabAtual;
    Historico hist = {0};

    modificarTabuleiro(&tabAtual, &hist, 'r', "a10");
    modificarTabuleiro(&tabAtual, &hist, 'r', "a12");

    comando_a(&tabAtual, &tabIO, &hist);

    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[0], "bbeegIglDbCH");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[1], "CbfHefjAeIjb");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[2], "eKfcALfGiDHJ");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[3], "ejgligalflKi");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[4], "AggbDccKbFbi");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[5], "IjKcjEBcLAgD");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[6], "eeCkkjaIjlea");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[7], "HeAbbcDeKgLi");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[8], "BLDeHgeffKAC");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[9], "#CBkl#K#G#J#"); 
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[10], "KGI#LFeHCBDl");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[11], "#IhJFKhB#CgE"); 
}

void test_comando_A_sem_modificacoes(void)
{
    Tabuleiro tabAtual = {
        .linhas = 3,
        .colunas = 3,
        .grelha = {
            "ABC",
            "DEF",
            "GHI"
        }
    };
    Tabuleiro tabIO = tabAtual;
    Historico hist = {0};

    comando_A(&tabAtual, &tabIO, &hist);

    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[0], "ABC");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[1], "DEF");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[2], "GHI");
}

void test_comando_A_com_tabuleiro5x5(void)
{
    Tabuleiro tabAtual = {
        .linhas = 5,
        .colunas = 5,
        .grelha = {
            "ecadC",
            "dcdec",
            "bddce",
            "cdeeb",
            "accbb"
        }
    };
    Tabuleiro tabIO = tabAtual;
    Historico hist = {0};

    comando_A(&tabAtual, &tabIO, &hist);

    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[0], "E#ADC");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[1], "DC#E#");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[2], "B#DCE");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[3], "CDE#B");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[4], "A#CB#");
}

void test_comando_A_com_tabuleiro_12x12(void)
{
    Tabuleiro tabAtual = {
        .linhas = 12,
        .colunas = 12,
        .grelha = {
            "bbeegigldbch",
            "cbfhefjaeijb",
            "ekfcalfgidhj",
            "ejgligalflki",
            "aggbdcckbfbi",
            "ijkcjebclagd",
            "eeckkjaijlea",
            "heabbcdekgli",
            "bldehgeffkac",
            "hcbklckcggjg",
            "kgiglfehcbdl",
            "dihjfkhbicge"
        }
    };
    Tabuleiro tabIO = tabAtual;
    Historico hist = {0};

    comando_A(&tabAtual, &tabIO, &hist);

    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[0], "bbeegIglDbCH");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[1], "CbfHefjAeIjb");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[2], "eKfcALfGiDHJ");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[3], "ejgligalflKi");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[4], "AggbDccKbFbi");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[5], "IjKcjEBcLAgD");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[6], "eeCkkjaIjlea");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[7], "heAbbcDeKgLi");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[8], "bLDeHgeffKAC");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[9], "hcBklckcggjg");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[10], "KgIglfeHCbDl");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[11], "DihJFKhBiCgE");

}

void test_comando_A_com_tabuleiro_apos_riscar(void)
{
    Tabuleiro tabAtual = {
        .linhas = 12,
        .colunas = 12,
        .grelha = {
            "bbeegigldbch",
            "cbfhefjaeijb",
            "ekfcalfgidhj",
            "ejgligalflki",
            "aggbdcckbfbi",
            "ijkcjebclagd",
            "eeckkjaijlea",
            "heabbcdekgli",
            "bldehgeffkac",
            "hcbklckcggjg",
            "kgiglfehcbdl",
            "dihjfkhbicge"
        }
    };
    Tabuleiro tabIO = tabAtual;
    Historico hist = {0};

    modificarTabuleiro(&tabAtual, &hist, 'r', "a10");
    modificarTabuleiro(&tabAtual, &hist, 'r', "a12");

    comando_A(&tabAtual, &tabIO, &hist);

    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[0], "#BE#GI#LD#CH");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[1], "C#FHE#JA#I#B");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[2], "EK#CALFGIDHJ");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[3], "#JGLI#A#F#K#");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[4], "A#gBDC#K#F#I");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[5], "IjK#JEBCLAGD");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[6], "#ECK#J#I#L#A");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[7], "H#A#B#DEKGL#");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[8], "BLDEHG#F#KAC");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[9], "#CBkl#K#G#J#"); 
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[10], "KGI#LFEHCBDl");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[11], "#IhJFKhB#C#E"); 
}

int main()
{
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("Testes_Comandos", NULL, NULL);

    CU_add_test(suite, "Comando a - Sem Modificações", test_comando_a_sem_modificacoes);
    CU_add_test(suite, "Comando a - tabuleiro 5x5", test_comando_a_com_tabuleiro5x5);
    CU_add_test(suite, "Comando A - Sem Modificações", test_comando_A_sem_modificacoes);
    CU_add_test(suite, "Comando A - Conflitos Resolvidos", test_comando_A_com_tabuleiro5x5);
    CU_add_test(suite, "Comando a - Tabuleiro Complexo", test_comando_a_com_tabuleiro_12x12);    
    CU_add_test(suite, "Comando A - Tabuleiro Complexo", test_comando_A_com_tabuleiro_12x12);
    CU_add_test(suite, "Modificar Tabuleiro - Riscar Posições", test_comando_a_com_tabuleiro_apos_riscar);
    CU_add_test(suite, "Comando A - Após Riscar", test_comando_A_com_tabuleiro_apos_riscar);


    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return 0;
}