#include <stdio.h>
#include "board.h"
#include "undo.h"

void guardar_estado(Historico *hist, const Tabuleiro *atual)
{
    if (hist == NULL || atual == NULL)
    {
        return;
    }

    if (hist->topo < MAX_HISTORY)
    {
        hist->estados[hist->topo++] = *atual;
    }
    else
    {
        printf("Aviso: Histórico cheio, não é possível guardar mais estados.\n");
    }
}

int desfazer(Historico *hist, Tabuleiro *atual)
{
    if (hist == NULL || atual == NULL)
    {
        printf("Erro: Ponteiros inválidos.\n");
        return 0;
    }

    if (hist->topo == 0)
    {
        printf("Nada para desfazer.\n");
        return 0;
    }

    *atual = hist->estados[--hist->topo];
    mostrarTabuleiro(atual);
    return 1;
}
