#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "board.h"
#include "verifica.h"

void test_verificarRestricoes_valido(void)
{
    Tabuleiro tabAtual = {
        .linhas = 3,
        .colunas = 3,
        .grelha = {
            "ArB",
            "CDE",
            "FGH"}};

    bool resultado = verificarRestricoes(&tabAtual);
    CU_ASSERT_TRUE(resultado);
}

void test_verificarRestricoes_regra1(void)
{
    Tabuleiro tabAtual = {
        .linhas = 3,
        .colunas = 3,
        .grelha = {
            "A#A",
            "cde",
            "fgh"}};

    bool resultado = verificarRestricoes(&tabAtual);
    CU_ASSERT_FALSE(resultado);
}

void test_verificarRestricoes_regra2(void)
{
    Tabuleiro tabAtual = {
        .linhas = 3,
        .colunas = 3,
        .grelha = {
            "A#B",
            "A#E",
            "fgh"}};

    bool resultado = verificarRestricoes(&tabAtual);
    CU_ASSERT_FALSE(resultado);
}

void test_verificarRestricoes_regra3(void)
{
    Tabuleiro tabAtual = {
        .linhas = 3,
        .colunas = 3,
        .grelha = {
            "A#b",
            "CDE",
            "FGH"}};

    bool resultado = verificarRestricoes(&tabAtual);
    CU_ASSERT_FALSE(resultado);
}

void test_verificarRestricoes_riscada_valida(void)
{
    Tabuleiro tabAtual = {
        .linhas = 3,
        .colunas = 3,
        .grelha = {
            "A#B",
            "CDE",
            "FGH"}};

    tabAtual.grelha[0][0] = 'A'; 
    tabAtual.grelha[0][2] = 'B';
    bool resultado = verificarRestricoes(&tabAtual);
    CU_ASSERT_TRUE(resultado);
}

void test_verificarRestricoes_regra4(void)
{
    Tabuleiro tabAtual = {
        .linhas = 3,
        .colunas = 3,
        .grelha = {
            "A#B",
            "###",
            "CDE"}};

    bool resultado = verificarRestricoes(&tabAtual);
    CU_ASSERT_FALSE(resultado); 
}