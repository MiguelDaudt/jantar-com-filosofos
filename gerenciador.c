//
// Created by mdaud on 24/11/2026.
//

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "gerenciador.h"
#include "logger.h"

void inicializarGerenciador(Gerenciador *gerenciador) {

    inicializarFila(&gerenciador->fila);

    for (int i = 0; i < NUM_FILOSOFOS; i++) {
        gerenciador->garfos[i] = true;
    }

    // Inicializa o mutex.
    if (pthread_mutex_init(&gerenciador->mutex, NULL) != 0) {
        fprintf(stderr, "Erro ao inicializar mutex.\n");
        exit(EXIT_FAILURE);
    }

    if (pthread_cond_init(&gerenciador->condicao, NULL) != 0) {

        pthread_mutex_destroy(&gerenciador->mutex);

        fprintf(stderr, "Erro ao inicializar condicao.\n");
        exit(EXIT_FAILURE);
    }
}

bool garfosDisponiveis(
    Gerenciador *gerenciador,
    Filosofo *filosofo
) {

    return
        gerenciador->garfos[filosofo->garfoEsquerdo]
        &&
        gerenciador->garfos[filosofo->garfoDireito];
}

bool podeComer(
    Gerenciador *gerenciador,
    Filosofo *filosofo
) {

    return
        primeiroFila(&gerenciador->fila) == filosofo->id
        &&
        garfosDisponiveis(gerenciador, filosofo);
}

void reservarGarfos(
    Gerenciador *gerenciador,
    Filosofo *filosofo
) {

    assert(garfosDisponiveis(gerenciador, filosofo));

    assert(
        primeiroFila(&gerenciador->fila) == filosofo->id
    );


    gerenciador->garfos[filosofo->garfoEsquerdo] = false;

    gerenciador->garfos[filosofo->garfoDireito] = false;
}

void liberarGarfos(
    Gerenciador *gerenciador,
    Filosofo *filosofo
) {

    assert(
        !gerenciador->garfos[filosofo->garfoEsquerdo]
    );

    assert(
        !gerenciador->garfos[filosofo->garfoDireito]
    );

    gerenciador->garfos[filosofo->garfoEsquerdo] = true;

    gerenciador->garfos[filosofo->garfoDireito] = true;
}

void solicitarGarfos(
    Gerenciador *gerenciador,
    Filosofo *filosofo
) {

    pthread_mutex_lock(&gerenciador->mutex);

    if (!inserirFila(&gerenciador->fila, filosofo->id)) {

        pthread_mutex_unlock(&gerenciador->mutex);

        fprintf(stderr, "Erro: fila cheia.\n");
        exit(EXIT_FAILURE);
    }

    registrarLog(
        filosofo->id,
        "Entrou na fila. Posicao: %d",
        gerenciador->fila.quantidade
    );

    while (!podeComer(gerenciador, filosofo)) {

        pthread_cond_wait(
            &gerenciador->condicao,
            &gerenciador->mutex
        );
    }

    reservarGarfos(gerenciador, filosofo);

    removerFila(&gerenciador->fila);

    registrarLog(
        filosofo->id,
        "Reservou G%d e G%d",
        filosofo->garfoEsquerdo,
        filosofo->garfoDireito
    );

    pthread_cond_broadcast(&gerenciador->condicao);

    pthread_mutex_unlock(&gerenciador->mutex);
}

void devolverGarfos(
    Gerenciador *gerenciador,
    Filosofo *filosofo
) {

    pthread_mutex_lock(&gerenciador->mutex);

    liberarGarfos(gerenciador, filosofo);

    filosofo->estado = PENSANDO;

    registrarLog(
        filosofo->id,
        "Liberou G%d e G%d. Refeicoes: %d. PENSANDO",
        filosofo->garfoEsquerdo,
        filosofo->garfoDireito,
        filosofo->refeicoes
    );

    pthread_cond_broadcast(&gerenciador->condicao);

    pthread_mutex_unlock(&gerenciador->mutex);
}

void destruirGerenciador(Gerenciador *gerenciador) {

    pthread_cond_destroy(&gerenciador->condicao);

    pthread_mutex_destroy(&gerenciador->mutex);
}