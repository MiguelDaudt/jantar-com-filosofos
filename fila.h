//
// Created by mdaud on 24/11/2026.
//

#ifndef FILA_H
#define FILA_H

#include <stdbool.h>
#include "filosofos.h"

typedef struct {
    int elementos[NUM_FILOSOFOS];
    int inicio;
    int fim;
    int quantidade;
} Fila;

void inicializarFila(Fila *fila);

bool filaVazia(Fila *fila);

bool filaCheia(Fila *fila);

bool inserirFila(Fila *fila, int id);

int removerFila(Fila *fila);

int primeiroFila(Fila *fila);

#endif
