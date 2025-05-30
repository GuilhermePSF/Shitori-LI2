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

    comando_a(&tabAtual, &hist);

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
            "ecadc",
            "dcdec",
            "bddce",
            "cdeeb",
            "accbb"
        }
    };
    Tabuleiro tabIO = tabAtual;
    Historico hist = {0};
    modificarTabuleiro(&tabAtual, &hist, 'r', "a1");
    comando_a(&tabAtual, &hist);

    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[0], "#Cad#");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[1], "D#deC");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[2], "BD#Ce");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[3], "c#E#B");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[4], "AcCBb");
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

    modificarTabuleiro(&tabAtual, &hist, 'r', "d7");
    comando_a(&tabAtual, &hist);

    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[0], "bbeegigldbch");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[1], "cbfhefjaeijb");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[2], "ekfcalfgidhj");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[3], "ejgligalflki");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[4], "aggbdcckbfbi");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[5], "ijkCjeb#Lagd");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[6], "eeC#KjaIjlea");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[7], "heaB#Cdekgli");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[8], "bldeHgeffkac");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[9], "hcbkl#Kcggjg");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[10], "kgiglFehcbdl");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[11], "dihjfkhbicge");
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

    comando_a(&tabAtual, &hist);

    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[0], "bbeegigldbch");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[1], "cbfhefjaeijb");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[2], "ekfcalfgidhj");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[3], "ejgligalflki");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[4], "aggbdcckbfbi");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[5], "ijkcjebclagd");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[6], "eeckkjaijlea");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[7], "heabbcdekgli");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[8], "Bldehgeffkac");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[9], "#Cbkl#K#G#J#"); 
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[10], "KGi#LFeHcBdl");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[11], "#IhJfkhb#Cge"); 
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

    comando_A(&tabAtual, &hist);

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

    comando_A(&tabAtual, &hist);

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

    modificarTabuleiro(&tabAtual, &hist, 'r', "a10");
    comando_A(&tabAtual, &hist);

    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[0], "#BE#GI#LD#CH");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[1], "C#FHE#JA#I#B");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[2], "EK#CALFGIDHJ");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[3], "#JGLI#A#F#K#");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[4], "AG#BDC#K#F#I");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[5], "I#K#JEBCLAGD");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[6], "#ECK#J#I#L#A");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[7], "H#A#B#DEKGL#");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[8], "BLDEHG#F#KAC");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[9], "#CB#L#K#G#J#");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[10], "K#IG#FEHCBDL");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[11], "DIHJFK#B#C#E");
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

    comando_A(&tabAtual, &hist);

    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[0], "#BE#GI#LD#CH");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[1], "C#FHE#JA#I#B");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[2], "EK#CALFGIDHJ");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[3], "#JGlI#A#F#K#");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[4], "A#gBdC#K#F#I");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[5], "IjK#JEBCLAGD");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[6], "#ECK#J#I#L#A");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[7], "H#A#B#DEKgL#");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[8], "BLdEHG#F#KAC");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[9], "#Cbkl#K#G#J#"); 
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[10], "KGI#LFEHCBDl");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[11], "#IhJfkhB#C#E"); 
}

int main()
{
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("Testes_Tip", NULL, NULL);

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