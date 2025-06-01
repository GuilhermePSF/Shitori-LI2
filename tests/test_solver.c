#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "board.h"
#include "game.h"
#include "undo.h"
#include "solver.h"
#include <stdlib.h>

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
            "dihjfkhbicge"}};
    Historico hist = {0};
    guardar_estado(&hist, &tabAtual);
    comando_R(&tabAtual, &hist, 'A');

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
    CU_ASSERT_TRUE(ganhou(&tabAtual));
}

void test_comando_R_tabuleiro_maisculas(void)
{
    Tabuleiro tabAtual = {
        .linhas = 12,
        .colunas = 12,
        .grelha = {
            "BBEegigldbch",
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
            "dihjfkhbicge"}};
    Historico hist = {0};
    guardar_estado(&hist, &tabAtual);
    comando_R(&tabAtual, &hist, 'A');
    CU_ASSERT_PTR_NOT_NULL(tabAtual.grelha);
    CU_ASSERT_FALSE(ganhou(&tabAtual));
}

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
            "dihjfkhbicge"}};
    Tabuleiro tabIO = tabAtual;
    Historico hist = {0};

    modificarTabuleiro(&tabAtual, &hist, 'b', "a10");
    modificarTabuleiro(&tabAtual, &hist, 'r', "i1");
    desfazer(&hist, &tabAtual, &tabIO, NULL);

    comando_R(&tabAtual, &hist, 'A');

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
    CU_ASSERT_TRUE(ganhou(&tabAtual));
}

void test_comando_R_com_tabuleiro_sem_solucao(void)
{
    Tabuleiro tabAtual = {
        .linhas = 10,
        .colunas = 10,
        .grelha = {
            "abfgchdieb",
            "cdheafijgb",
            "ekcgalfidh",
            "gjglibafki",
            "aggdcbkfbi",
            "ijkcjebagd",
            "eickkjaile",
            "heabbdekgl",
            "bldehgffkc",
            "hcbklcgcgj"}};
    Historico hist = {0};
    guardar_estado(&hist, &tabAtual);
    comando_R(&tabAtual, &hist, 'A');
    CU_ASSERT_FALSE(ganhou(&tabAtual));
}

void test_comando_R_com_tabuleiro_20x20(void)
{
    Tabuleiro tabAtual = {
        .linhas = 20,
        .colunas = 20,
        .grelha = {
            "qbnjtjmsfmkdophomalr",
            "lgdhctmionqojjgbrspf",
            "tlldjrsqjgmgacbhoeqi",
            "eerjabfjsdjqrnntpimh",
            "aahklmecbldspndqpomg",
            "srmaqebgkqnjklmngctd",
            "fcatgrdkbolamiqrjeng",
            "ilednckpoqjrdifhlbha",
            "jppihffstscbrkrjbmgd",
            "bgjorqlghrkmdseainnt",
            "klpfiohamdsregehhdrf",
            "smkcfbtgeialqnjihpsk",
            "gfhmnihbebdkcqnpksal",
            "mtmkospnecqhkdieqjfm",
            "cmibnajfgsrpnosmslnq",
            "aornscpeahgtlbijmmqc",
            "mqscjdklpaffchjnerin",
            "fngsmhrclobafeckeijo",
            "oempnnbrckhsibadfqqj",
            "rjtrldomkeqpsdacpkdp"}};
    Historico hist = {0};
    modificarTabuleiro(&tabAtual, &hist, 'b', "a10");
    modificarTabuleiro(&tabAtual, &hist, 'r', "f7");
    modificarTabuleiro(&tabAtual, &hist, 'b', "c15");
    modificarTabuleiro(&tabAtual, &hist, 'r', "i1");
    comando_R(&tabAtual, &hist, 'A');

    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[0], "QBN#TJM#F#KD#PHO#ALR");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[1], "L#DHCT#IONQ#J#GBRSP#");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[2], "TL#D#RSQJ#MGACB#OE#I");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[3], "E#R#ABF#SDJQ#N#TP#MH");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[4], "#AHK#MEC#L#SP#DQ#O#G");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[5], "SR#AQEB#K#NJ#LM#GCTD");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[6], "FCATG#DKBOL#MIQRJ#N#");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[7], "I#E#NCKP#Q#RD#F#LBHA");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[8], "#P#IHF#ST#CBRK#J#MG#");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[9], "BGJO#QL#HR#M#SEAIN#T");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[10], "K#P#IO#AM#S#EG#H#DRF");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[11], "#MKCF#TG#IALQ#J#HPS#");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[12], "GF#M#IH#EBD#CQNPK#AL");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[13], "#TM#OS#N#C#HKD#EQJF#");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[14], "C#IB#AJFG#R#NOSM#L#Q");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[15], "AO#NS#PE#HGTL#I#M#QC");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[16], "MQS#JD#LPA#F#H#NERI#");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[17], "#NGSMHR#L#BAFECK#IJO");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[18], "OE#P#N#RCKH#IB#DFQ#J");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[19], "#JTRL#OM#E#PS#AC#KD#");
    CU_ASSERT_TRUE(ganhou(&tabAtual));
}