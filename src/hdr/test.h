#ifndef TEST_H
#define TEST_H

#include "board.h"
#include "undo.h"

void remover_ansi(char *dest, const char *src);
void test_mostrarTabuleiro_sem_mudancas(void);
void test_mostrarTabuleiro_com_mudancas(void);
void test_centrarLabel(void);
void test_mostrarAjuda(void);
void test_modificarTabuleiro_pintardebranco(void);
void test_modificarTabuleiro_risca(void);
void test_riscar_sem_tabuleiro(void);
void test_riscar_coordenada_errada(void);
void test_riscar_coordenada_branca (void);
void test_riscar_fora_do_tabuleiro(void);
void test_riscar_ja_riscado(void);
void test_comando_invalido (void);
void test_pintar_ja_riscado(void);
void test_pintar_ja_pintado(void);
void test_pintar_fora_do_tabuleiro(void);
void test_nao_ganhou(void);
void test_ganhou (void);
void test_random_letra_minuscula(void); 
void test_inicializarGerador(void);
void test_preencherGerador(void);
void test_ser_resolvivel(void);
void test_generate(void);
void test_carregarTabuleiro_ficheiro_existente(void);
void test_carregarTabuleiro_invalido(void);
void test_carregar_ficheiro_inexistente(void);
void test_gravar_sem_carregar(void);
void test_gravar_com_mudancas(void);
void test_nome_ficheiro_muito_longo(void);
void test_fgets_falha(void);
void test_linha_tamanho_errado(void);
void test_gravar_falha_abrir_ficheiro(void);
void test_comando_R_simples_12x12(void);
void test_comando_R_tabuleiro_maisculas(void);
void test_comando_R_com_modificacoes_12x12(void);
void test_comando_R_com_tabuleiro_sem_solucao(void);
void test_comando_R_com_tabuleiro_20x20(void);
void test_comando_a_sem_modificacoes(void);
void test_comando_a_com_tabuleiro5x5(void);
void test_comando_a_com_tabuleiro_12x12(void);
void test_comando_a_com_tabuleiro_apos_riscar(void);
void test_comando_A_sem_modificacoes(void);
void test_comando_A_com_tabuleiro5x5(void);
void test_comando_A_com_tabuleiro_12x12(void);
void test_comando_A_com_tabuleiro_apos_riscar(void);
void test_desfazer_sem_tabuleiro(void);
void test_desfazer_sem_mudancas(void);
void test_desfazer_coordenada_com_mudanca(void);
void test_desfazer_coordenada_sem_mudanca(void);
void test_desfazer_coordenada_errada(void);
void test_verificarRestricoes_valido(void);
void test_verificarRestricoes_regra1(void);
void test_verificarRestricoes_regra2(void);
void test_verificarRestricoes_regra3(void);
void test_verificarRestricoes_riscada_valida(void);
void test_verificarRestricoes_regra4(void);

#endif
