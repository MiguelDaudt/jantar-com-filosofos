//
// Created by mdaud on 24/11/2026.
//

#include <stdio.h>
#include <windows.h>
#include "gerenciador.h"
#include "filosofos.h"
#include "logger.h"

void pensar(Filosofo *filosofo) {

    filosofo->estado = PENSANDO;

    registrarLog(filosofo->id, "PENSANDO");

Sleep(TEMPO_PENSANDO);
}

void tentarComer(Filosofo *filosofo) {

    filosofo->estado = TENTANDO_COMER;

    registrarLog(filosofo->id, "TENTANDO COMER");

    double inicioEspera = tempoDecorrido();

    solicitarGarfos(
        filosofo->gerenciador,
        filosofo
    );

    double espera =
        tempoDecorrido() - inicioEspera;

    filosofo->tempoEsperaTotal += espera;

    if (espera > filosofo->maiorTempoEspera) {

        filosofo->maiorTempoEspera = espera;
    }

    registrarLog(
        filosofo->id,
        "Tempo de espera: %.3fs",
        espera
    );
}

void comer(Filosofo *filosofo) {

    filosofo->estado = COMENDO;

    registrarLog(filosofo->id, "COMENDO");

    Sleep(TEMPO_COMENDO);
    filosofo->refeicoes++;

    devolverGarfos(
        filosofo->gerenciador,
        filosofo
    );
}

void *rotinaFilosofo(void *arg) {

    Filosofo *filosofo = (Filosofo *) arg;

    while (filosofo->refeicoes < NUM_REFEICOES) {

        pensar(filosofo);

        tentarComer(filosofo);

        comer(filosofo);
    }

    filosofo->estado = PENSANDO;

    registrarLog(
    filosofo->id,
    "Terminou suas %d refeicoes.",
    filosofo->refeicoes
);

    return NULL;
}