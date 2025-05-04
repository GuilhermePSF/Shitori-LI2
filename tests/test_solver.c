#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "board.h"
#include "game.h"
#include "undo.h"
#include "solver.h"

void test_comando_R_simples_12x12(void)
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
    guardar_estado(&hist, &tabAtual);
    comando_R(&tabAtual, &tabIO, &hist);

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

// vou riscar onde deveria estar branco para testar o "desfazer" e pintar onde deveria estar riscado
void test_comando_R_com_modificacoes_12x12(void)
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

    modificarTabuleiro(&tabAtual, &hist, 'b', "a10"); 
    modificarTabuleiro(&tabAtual, &hist, 'r', "i1");  

    comando_R(&tabAtual, &tabIO, &hist);

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

int main()
{
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("Testes_Solver", NULL, NULL);
    CU_add_test(suite, "Comando R - Simples", test_comando_R_simples_12x12);
    CU_add_test(suite, "Comando R - Com Modificações", test_comando_R_com_modificacoes_12x12);
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return 0;
}