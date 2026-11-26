//
// Created by mdaud on 24/11/2026.
//

#ifndef GERENCIADOR_H
#define GERENCIADOR_H

#include <stdbool.h>
#include <pthread.h>
#include "fila.h"
#include "filosofos.h"

typedef struct Gerenciador {

    Fila fila;

    bool garfos[NUM_FILOSOFOS];

    pthread_mutex_t mutex;

    pthread_cond_t condicao;

} Gerenciador;

void inicializarGerenciador(Gerenciador *gerenciador);

bool garfosDisponiveis(
    Gerenciador *gerenciador, Filosofo *filosofo
);

bool podeComer(
    Gerenciador *gerenciador, Filosofo *filosofo
);

void reservarGarfos(
    Gerenciador *gerenciador, Filosofo *filosofo
);

void liberarGarfos(
    Gerenciador *gerenciador, Filosofo *filosofo
);

void destruirGerenciador(Gerenciador *gerenciador);

void solicitarGarfos(
    Gerenciador *gerenciador,
    Filosofo *filosofo
);

void devolverGarfos(
    Gerenciador *gerenciador,
    Filosofo *filosofo
);

#endif
