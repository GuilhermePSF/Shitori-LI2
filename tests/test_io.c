#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "board.h"
#include "io.h"
#include "game.h"
#include "undo.h"

#define MAX_COLS 26 // máx. número de colunas úteis
#define MAX_LINHAS 128

void test_carregarTabuleiro_ficheiro_existente(void)
{
    Tabuleiro tab;
    Historico hist;
    int resultado = carregarTabuleiro(&tab, &hist, "teste.txt");
    CU_ASSERT_EQUAL(resultado, 0);
    CU_ASSERT(tab.linhas > 0 && tab.colunas > 0);
    CU_ASSERT(strlen(tab.grelha[0]) > 0);
}

void test_carregarTabuleiro_invalido(void)
{
    Tabuleiro tab;
    Historico hist;
    int resultado = carregarTabuleiro(&tab, &hist, "tabuleiroerrado.txt");
    CU_ASSERT_EQUAL(resultado, -1);
}

void test_carregar_ficheiro_inexistente(void)
{
    Tabuleiro tab;
    Historico hist;

    int resultado = carregarTabuleiro(&tab, &hist, "boards/inexistente.txt");
    CU_ASSERT_EQUAL(resultado, -1); // Deve retornar erro
}
void test_gravar_sem_carregar(void)
{
    Tabuleiro tab = {0}; // Tabuleiro não inicializado

    int resultado = gravarTabuleiro(&tab, "boards/saida_test.txt");
    CU_ASSERT_EQUAL(resultado, -1); // Deve retornar erro
}

void test_gravar_com_mudancas(void)
{
    Tabuleiro tab = {
        .linhas = 3,
        .colunas = 3,
        .grelha = {
            "abc",
            "def",
            "ghi"}};
    Historico hist;

    // Realiza algumas mudanças no tabuleiro
    modificarTabuleiro(&tab, &hist, 'b', "b2"); // Torna 'e' maiúsculo
    modificarTabuleiro(&tab, &hist, 'r', "c3"); // Substitui 'i' por '#'

    // Grava o tabuleiro modificado
    int resultado = gravarTabuleiro(&tab, "boards/saida_test.txt");
    CU_ASSERT_EQUAL(resultado, 0); // Deve gravar com sucesso

    // Verifica o conteúdo do ficheiro gravado
    FILE *f = fopen("boards/saida_test.txt", "r");
    CU_ASSERT_PTR_NOT_NULL(f);
    if (f)
    {
        char linha[10];
        fgets(linha, sizeof(linha), f);
        CU_ASSERT_STRING_EQUAL(linha, "3 3\n"); // Dimensões corretas
        fgets(linha, sizeof(linha), f);
        CU_ASSERT_STRING_EQUAL(linha, "abc\n"); // Primeira linha
        fgets(linha, sizeof(linha), f);
        CU_ASSERT_STRING_EQUAL(linha, "dEf\n"); // Segunda linha modificada
        fgets(linha, sizeof(linha), f);
        CU_ASSERT_STRING_EQUAL(linha, "gh#\n"); // Terceira linha modificada
        fclose(f);
    }
}
int main()
{
    CU_initialize_registry();

    CU_pSuite suite = CU_add_suite("Testes_Tabuleiro", NULL, NULL);

    // Testes para carregar
    CU_add_test(suite, "Carregar ficheiro existente", test_carregarTabuleiro_ficheiro_existente);
    CU_add_test(suite, "Carregar ficheiro inexistente", test_carregar_ficheiro_inexistente);
    CU_add_test(suite, "Carregar ficheiro com formato inválido", test_carregarTabuleiro_invalido);

    // Testes para gravar
    CU_add_test(suite, "Gravar sem carregar", test_gravar_sem_carregar);
    CU_add_test(suite, "Gravar com mudanças", test_gravar_com_mudancas);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}