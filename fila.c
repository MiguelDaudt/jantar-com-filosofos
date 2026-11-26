//
// Created by mdaud on 24/11/2026.
//

#include "fila.h"

void inicializarFila(Fila *fila) {
    fila->inicio = 0;
    fila->fim = 0;
    fila->quantidade = 0;
}

bool filaVazia(Fila *fila) {
    return fila->quantidade == 0;
}

bool filaCheia(Fila *fila) {
    return fila->quantidade == NUM_FILOSOFOS;
}

bool inserirFila(Fila *fila, int id) {

    if (filaCheia(fila)) {
        return false;
    }

    fila->elementos[fila->fim] = id;

    fila->fim = (fila->fim + 1) % NUM_FILOSOFOS;

    fila->quantidade++;

    return true;
}

int removerFila(Fila *fila) {

    if (filaVazia(fila)) {
        return -1;
    }

    int id = fila->elementos[fila->inicio];

    fila->inicio =
        (fila->inicio + 1) % NUM_FILOSOFOS;

    fila->quantidade--;

    return id;
}

int primeiroFila(Fila *fila) {

    if (filaVazia(fila)) {
        return -1;
    }

    return fila->elementos[fila->inicio];
}