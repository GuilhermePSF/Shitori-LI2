#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include "board.h"
#include "io.h"
#include "game.h"
#include "undo.h"

void test_carregarTabuleiro_ficheiro_existente(void)
{
    Tabuleiro tabAtual, tabIO;
    Historico hist;
    bool resultado = carregarTabuleiro(&tabAtual, &tabIO, &hist, "tab5.txt");
    CU_ASSERT_TRUE(resultado);
    CU_ASSERT(tabAtual.linhas > 0 && tabAtual.colunas > 0);
    CU_ASSERT(strlen(tabAtual.grelha[0]) > 0);
}

void test_carregarTabuleiro_invalido(void)
{
    FILE *f = fopen("boards/tabuleiroerrado.txt", "w");
    if (f) {
        fprintf(f, "abc def\n");
        fclose(f);
    }

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

void test_nome_ficheiro_muito_longo(void)
{
    char nome[600];
    memset(nome, 'a', sizeof(nome) - 1);
    nome[sizeof(nome) - 1] = '\0';

    Tabuleiro t = {0};
    Historico h;
    Tabuleiro tIO;
    CU_ASSERT_FALSE(carregarTabuleiro(&t, &tIO, &h, nome));
    CU_ASSERT_FALSE(gravarTabuleiro(&t, nome));
}

void test_fgets_falha(void)
{
    FILE *f = fopen("boards/fgets_falha.txt", "w");
    if (f) {
        fprintf(f, "3 3\nabc\ndef\n"); 
        fclose(f);
    }

    Tabuleiro t1, t2;
    Historico h;
    CU_ASSERT_FALSE(carregarTabuleiro(&t1, &t2, &h, "fgets_falha.txt"));
}

void test_linha_tamanho_errado(void)
{
    FILE *f = fopen("boards/linha_curta.txt", "w");
    if (f) {
        fprintf(f, "2 3\nabc\nde\n");
    }

    Tabuleiro t1, t2;
    Historico h;
    CU_ASSERT_FALSE(carregarTabuleiro(&t1, &t2, &h, "linha_curta.txt"));
}

void test_gravar_falha_abrir_ficheiro(void)
{
    Tabuleiro t = {.linhas = 1, .colunas = 3};
    strcpy(t.grelha[0], "abc");

    CU_ASSERT_FALSE(gravarTabuleiro(&t, "/root/saida.txt"));

}