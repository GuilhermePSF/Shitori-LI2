#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "board.h"
#include "verifica.h"

// Teste: Tabuleiro válido (sem violações)
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

// Teste: Violação da Regra 1 (letras maiúsculas repetidas na mesma linha)
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

// Teste: Violação da Regra 2 (letras maiúsculas repetidas na mesma coluna)
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

// Teste: Violação da Regra 3 (para cada célula riscada todas as casas vizinhas ortogonais têm que estar pintadas a branco)
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

// Teste: Célula riscada com vizinhos válidos
void test_verificarRestricoes_riscada_valida(void)
{
    Tabuleiro tabAtual = {
        .linhas = 3,
        .colunas = 3,
        .grelha = {
            "A#B",
            "CDE",
            "FGH"}};

    // Ajusta os vizinhos da célula riscada para serem válidos
    tabAtual.grelha[0][0] = 'A'; 
    tabAtual.grelha[0][2] = 'B';
    bool resultado = verificarRestricoes(&tabAtual);
    CU_ASSERT_TRUE(resultado);
}

// Teste: Violação da Regra 4 (casas não riscadas desconectadas)
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