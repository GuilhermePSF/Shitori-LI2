#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "test_board.c"
#include "test_game.c"
#include "test_generate.c"
#include "test_io.c"
#include "test_solver.c"
#include "test_tip.c"
#include "test_undo.c"
#include "test_verifica.c"
#include "test.h"

int main()
{
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("Testes_Tabuleiro", NULL, NULL);

    CU_add_test(suite, "Mostrar tabuleiro sem mudanças", test_mostrarTabuleiro_sem_mudancas);
    CU_add_test(suite, "Mostrar tabuleiro com mudanças", test_mostrarTabuleiro_com_mudancas);
    CU_add_test(suite, "Centrar Label", test_centrarLabel);
    CU_add_test(suite, "Mostrar ajuda", test_mostrarAjuda);

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

    CU_add_test(suite, "Random letra minuscula", test_random_letra_minuscula);
    CU_add_test(suite, "Inicializar gerador", test_inicializarGerador);
    CU_add_test(suite, "Preencher gerador", test_preencherGerador);
    CU_add_test(suite, "Ser resolvível", test_ser_resolvivel);
    CU_add_test(suite, "Generate Tabuleiro", test_generate);

    CU_add_test(suite, "Carregar ficheiro existente", test_carregarTabuleiro_ficheiro_existente);
    CU_add_test(suite, "Carregar ficheiro inexistente", test_carregar_ficheiro_inexistente);
    CU_add_test(suite, "Carregar ficheiro com formato inválido", test_carregarTabuleiro_invalido);
    CU_add_test(suite, "Gravar sem carregar", test_gravar_sem_carregar);
    CU_add_test(suite, "Gravar com mudanças", test_gravar_com_mudancas);
    CU_add_test(suite, "Nome de ficheiro muito longo", test_nome_ficheiro_muito_longo);
    CU_add_test(suite, "Falha na leitura de linha com fgets", test_fgets_falha);
    CU_add_test(suite, "Linha com tamanho errado", test_linha_tamanho_errado);
    CU_add_test(suite, "Falha ao abrir ficheiro para gravar", test_gravar_falha_abrir_ficheiro);

    CU_add_test(suite, "Comando R - Simples", test_comando_R_simples_12x12);
    CU_add_test(suite, "Comando R - Com Modificações", test_comando_R_com_modificacoes_12x12);
    CU_add_test(suite, "Comando R - Tabuleiro Sem Solução", test_comando_R_com_tabuleiro_sem_solucao);
    CU_add_test(suite, "Comando R - Tabuleiro 20x20", test_comando_R_com_tabuleiro_20x20);
    CU_add_test(suite, "Comando R - Regra 1", test_comando_R_tabuleiro_maisculas);

    CU_add_test(suite, "Comando a - Sem Modificações", test_comando_a_sem_modificacoes);
    CU_add_test(suite, "Comando a - tabuleiro 5x5", test_comando_a_com_tabuleiro5x5);
    CU_add_test(suite, "Comando A - Sem Modificações", test_comando_A_sem_modificacoes);
    CU_add_test(suite, "Comando A - Conflitos Resolvidos", test_comando_A_com_tabuleiro5x5);
    CU_add_test(suite, "Comando a - Tabuleiro Complexo", test_comando_a_com_tabuleiro_12x12);
    CU_add_test(suite, "Comando A - Tabuleiro Complexo", test_comando_A_com_tabuleiro_12x12);
    CU_add_test(suite, "Modificar Tabuleiro - Riscar Posições", test_comando_a_com_tabuleiro_apos_riscar);
    CU_add_test(suite, "Comando A - Após Riscar", test_comando_A_com_tabuleiro_apos_riscar);

    CU_add_test(suite, "Desfazer sem tabuleiro carregado", test_desfazer_sem_tabuleiro);
    CU_add_test(suite, "Desfazer sem mudanças", test_desfazer_sem_mudancas);
    CU_add_test(suite, "Desfazer coordenada com mudança", test_desfazer_coordenada_com_mudanca);
    CU_add_test(suite, "Desfazer coordenada sem mudança", test_desfazer_coordenada_sem_mudanca);
    CU_add_test(suite, "Desfazer coordenada errada", test_desfazer_coordenada_errada);

    CU_add_test(suite, "Tabuleiro válido", test_verificarRestricoes_valido);
    CU_add_test(suite, "Violação da Regra 1", test_verificarRestricoes_regra1);
    CU_add_test(suite, "Violação da Regra 2", test_verificarRestricoes_regra2);
    CU_add_test(suite, "Violação da Regra 3", test_verificarRestricoes_regra3);
    CU_add_test(suite, "Célula riscada com vizinhos válidos", test_verificarRestricoes_riscada_valida);
    CU_add_test(suite, "Violação da Regra 4", test_verificarRestricoes_regra4);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return 0;
}