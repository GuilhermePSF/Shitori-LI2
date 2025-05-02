#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "board.h"
#include "io.h"
#include "game.h"
#include "undo.h"

void test_carregarTabuleiro_ficheiro_existente(void)
{
    Tabuleiro tabAtual, tabIO;
    Historico hist;
    bool resultado = carregarTabuleiro(&tabAtual, &tabIO, &hist, "teste.txt");
    CU_ASSERT_TRUE(resultado);
    CU_ASSERT(tabAtual.linhas > 0 && tabAtual.colunas > 0);
    CU_ASSERT(strlen(tabAtual.grelha[0]) > 0);
}

void test_carregarTabuleiro_invalido(void)
{
    Tabuleiro tabAtual, tabIO;
    Historico hist;
    bool resultado = carregarTabuleiro(&tabAtual, &tabIO, &hist, "tabuleiroerrado.txt");
    CU_ASSERT_FALSE(resultado);
}

void test_carregar_ficheiro_inexistente(void)
{
    Tabuleiro tabAtual, tabIO;
    Historico hist;
    bool resultado = carregarTabuleiro(&tabAtual, &tabIO, &hist, "inexistente.txt");
    CU_ASSERT_FALSE(resultado);
}

void test_gravar_sem_carregar(void)
{
    Tabuleiro tabAtual = {0};
    bool resultado = gravarTabuleiro(&tabAtual, "boards/saida_test.txt");
    CU_ASSERT_FALSE(resultado);
}

void test_gravar_com_mudancas(void)
{
    Tabuleiro tabAtual = {
        .linhas = 3,
        .colunas = 3,
        .grelha = {
            "abc",
            "def",
            "ghi"
        }
    };

    tabAtual.grelha[1][1] = 'E';
    tabAtual.grelha[2][2] = '#';

    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[1], "dEf");
    CU_ASSERT_STRING_EQUAL(tabAtual.grelha[2], "gh#");

    const char *nomeFicheiro = "saida_test.txt";
    bool resultado = gravarTabuleiro(&tabAtual, (char*)nomeFicheiro);
    CU_ASSERT_TRUE_FATAL(resultado);

    char caminho[512];
    snprintf(caminho, sizeof(caminho), "%s%s", "boards/", nomeFicheiro);
    FILE *f = fopen(caminho, "r");
    CU_ASSERT_PTR_NOT_NULL_FATAL(f);

    if (f) {
        char linha[64];
        CU_ASSERT_PTR_NOT_NULL_FATAL(fgets(linha, sizeof(linha), f));
        CU_ASSERT_STRING_EQUAL(linha, "3 3\n");
        CU_ASSERT_PTR_NOT_NULL_FATAL(fgets(linha, sizeof(linha), f));
        CU_ASSERT_STRING_EQUAL(linha, "abc\n");
        CU_ASSERT_PTR_NOT_NULL_FATAL(fgets(linha, sizeof(linha), f));
        CU_ASSERT_STRING_EQUAL(linha, "dEf\n");
        CU_ASSERT_PTR_NOT_NULL_FATAL(fgets(linha, sizeof(linha), f));
        CU_ASSERT_STRING_EQUAL(linha, "gh#\n");
        fclose(f);
    }
}

int main()
{
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("Testes_Tabuleiro", NULL, NULL);
    CU_add_test(suite, "Carregar ficheiro existente", test_carregarTabuleiro_ficheiro_existente);
    CU_add_test(suite, "Carregar ficheiro inexistente", test_carregar_ficheiro_inexistente);
    CU_add_test(suite, "Carregar ficheiro com formato inválido", test_carregarTabuleiro_invalido);
    CU_add_test(suite, "Gravar sem carregar", test_gravar_sem_carregar);
    CU_add_test(suite, "Gravar com mudanças", test_gravar_com_mudancas);
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}