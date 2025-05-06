#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "board.h"
#include "game.h"
#include "undo.h"

void test_modificarTabuleiro_pintardebranco(void)
{
    Tabuleiro tabAtual = {
        .linhas = 3,
        .colunas = 3,
        .grelha = {
            "abc",
            "def",
            "ghi"}};
    Historico hist;
    bool resultado = modificarTabuleiro(&tabAtual, &hist, 'b', "b2");
    CU_ASSERT_TRUE(resultado);
    CU_ASSERT_EQUAL(tabAtual.grelha[1][1], 'E');
}

void test_modificarTabuleiro_risca(void)
{
    Tabuleiro tabAtual = {
        .linhas = 3,
        .colunas = 3,
        .grelha = {
            "abc",
            "def",
            "ghi"}};
    Historico hist;
    bool resultado = modificarTabuleiro(&tabAtual, &hist, 'r', "c3");
    CU_ASSERT_TRUE(resultado);
    CU_ASSERT_EQUAL(tabAtual.grelha[2][2], '#');
}

void test_riscar_sem_tabuleiro(void)
{
    Tabuleiro tabAtual = {0};
    Historico hist;
    bool resultado = modificarTabuleiro(&tabAtual, &hist, 'r', "a1");
    CU_ASSERT_FALSE(resultado);
    CU_ASSERT_EQUAL(tabAtual.linhas, 0);
}

void test_riscar_coordenada_errada(void)
{
    Tabuleiro tabAtual = {
        .linhas = 3,
        .colunas = 3,
        .grelha = {
            "abc",
            "def",
            "ghi"}};
    Historico hist = {0};
    bool resultado = modificarTabuleiro(&tabAtual, &hist, 'r', "z9");
    CU_ASSERT_FALSE(resultado);
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[0], "abc");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[1], "def");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[2], "ghi");
}

void test_riscar_coordenada_branca (void)
{
    Tabuleiro tabAtual = {
        .linhas = 3,
        .colunas = 3,
        .grelha = {
            "abC",
            "def",
            "ghi"}};
        Historico hist = {0};
        bool resultado = modificarTabuleiro (&tabAtual, &hist, 'r', "c1");
        CU_ASSERT_FALSE(resultado);
        CU_ASSERT_STRING_EQUAL(tabAtual.grelha[0], "abC");
        CU_ASSERT_STRING_EQUAL(tabAtual.grelha[1], "def");
        CU_ASSERT_STRING_EQUAL(tabAtual.grelha[2], "ghi");
 }

void test_riscar_fora_do_tabuleiro(void)
{
    Tabuleiro tabAtual = {
        .linhas = 3,
        .colunas = 3,
        .grelha = {
            "abc",
            "def",
            "ghi"}};
    Historico hist = {0};
    bool resultado = modificarTabuleiro(&tabAtual, &hist, 'r', "d4");
    CU_ASSERT_FALSE(resultado);
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[0], "abc");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[1], "def");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[2], "ghi");
}

void test_riscar_ja_riscado(void)
{
    Tabuleiro tabAtual = {
        .linhas = 3,
        .colunas = 3,
        .grelha = {
            "abc",
            "d#f",
            "ghi"}};
    Historico hist = {0};
    bool resultado = modificarTabuleiro(&tabAtual, &hist, 'r', "b2");
    CU_ASSERT_TRUE(resultado);
    CU_ASSERT_EQUAL(tabAtual.grelha[1][1], '#');
}

void test_comando_invalido (void)
{
    Tabuleiro tabAtual = {
        .linhas = 3,
        .colunas = 3,
        .grelha = {
            "abc",
            "def",
            "ghi"}};
        Historico hist = {0};
        bool resultado = modificarTabuleiro (&tabAtual, &hist, 'l', "c1");
        CU_ASSERT_FALSE(resultado);
        CU_ASSERT_STRING_EQUAL(tabAtual.grelha[0], "abc");
        CU_ASSERT_STRING_EQUAL(tabAtual.grelha[1], "def");
        CU_ASSERT_STRING_EQUAL(tabAtual.grelha[2], "ghi");
 }

void test_pintar_ja_riscado(void)
{
    Tabuleiro tabAtual = {
        .linhas = 3,
        .colunas = 3,
        .grelha = {
            "abc",
            "d#f",
            "ghi"}};
    Historico hist = {0};
    bool resultado = modificarTabuleiro(&tabAtual, &hist, 'b', "b2");
    CU_ASSERT_FALSE(resultado);
    CU_ASSERT_EQUAL(tabAtual.grelha[1][1], '#');
}

void test_pintar_ja_pintado(void)
{
    Tabuleiro tabAtual = {
        .linhas = 3,
        .colunas = 3,
        .grelha = {
            "abc",
            "dEf",
            "ghi"}};
    Historico hist = {0};
    bool resultado = modificarTabuleiro(&tabAtual, &hist, 'b', "b2");
    CU_ASSERT_TRUE(resultado);
    CU_ASSERT_EQUAL(tabAtual.grelha[1][1], 'E');
}

void test_pintar_fora_do_tabuleiro(void)
{
    Tabuleiro tabAtual = {
        .linhas = 3,
        .colunas = 3,
        .grelha = {
            "abc",
            "def",
            "ghi"}};
    Historico hist = {0};
    bool resultado = modificarTabuleiro(&tabAtual, &hist, 'b', "d4");
    CU_ASSERT_FALSE(resultado);
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[0], "abc");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[1], "def");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[2], "ghi");
}

void test_nao_ganhou(void) {
    Tabuleiro tabAtual = {
        .linhas = 10,
        .colunas = 10,
        .grelha = {
            "#BFG#HD#Eb",
            "CDHEAFIJ#B",
            "EK#gaL#IDH",
            "#JGL#BAF#I",
            "AG#DC#K#B#",
            "I#KCJEBAGD",
            "eIC#KJa#LE",
            "#EAB#DeK#L",
            "BLD#HGF#KC",
            "H#BKL#GC#J"
        }
    };
    CU_ASSERT_FALSE(ganhou(&tabAtual));
}

void test_ganhou (void) {
    Tabuleiro tabAtual = {
        .linhas = 9,
        .colunas = 9,
        .grelha = {
            "IDA#E#FG#",
            "H#CIDEB#F",
            "GB#DH#AFE",
            "#AF#BHGE#",
            "DG#F#B#HC",
            "E#BGCFI#D",
            "#FE#GI#AB",
            "FE#HAGC#I",
            "B#HE#ADI#"
                }
    };
    CU_ASSERT_TRUE (ganhou(&tabAtual));
}


int main()
{
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("Testes_Game", NULL, NULL);

    CU_add_test(suite, "Pintar de branco", test_modificarTabuleiro_pintardebranco);
    CU_add_test(suite, "Risca", test_modificarTabuleiro_risca);
    CU_add_test(suite, "Riscar sem tabuleiro", test_riscar_sem_tabuleiro);
    CU_add_test(suite, "Riscar coordenada branca", test_riscar_coordenada_branca);
    CU_add_test(suite, "Riscar coordenada errada", test_riscar_coordenada_errada);
    CU_add_test(suite, "Riscar fora do tabuleiro", test_riscar_fora_do_tabuleiro);
    CU_add_test(suite, "Comando Inválido", test_comando_invalido);
    CU_add_test(suite, "Riscar já riscado", test_riscar_ja_riscado);
    CU_add_test(suite, "Pintar já riscado", test_pintar_ja_riscado);
    CU_add_test(suite, "Pintar já pintado", test_pintar_ja_pintado);
    CU_add_test(suite, "Pintar fora do tabuleiro", test_pintar_fora_do_tabuleiro);
    CU_add_test(suite, "Não Ganhou", test_nao_ganhou);
    CU_add_test(suite, "Ganhou", test_ganhou);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}