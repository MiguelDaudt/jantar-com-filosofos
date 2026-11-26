#include <stdio.h>
#include <pthread.h>
#include <assert.h>
#include "filosofos.h"
#include "gerenciador.h"
#include "logger.h"

int main(void) {

    pthread_t threads[NUM_FILOSOFOS];

    Filosofo filosofos[NUM_FILOSOFOS];

    inicializarLogger();

    Gerenciador gerenciador;

    inicializarGerenciador(&gerenciador);

    for (int i = 0; i < NUM_FILOSOFOS; i++) {

        filosofos[i].id = i;

        filosofos[i].estado = PENSANDO;

        filosofos[i].refeicoes = 0;

        filosofos[i].garfoEsquerdo = i;

        filosofos[i].garfoDireito =
            (i + 1) % NUM_FILOSOFOS;

        filosofos[i].gerenciador = &gerenciador;

        filosofos[i].tempoEsperaTotal = 0.0;

        filosofos[i].maiorTempoEspera = 0.0;
    }

    for (int i = 0; i < NUM_FILOSOFOS; i++) {

        if (pthread_create(
                &threads[i],
                NULL,
                rotinaFilosofo,
                &filosofos[i]) != 0) {

            fprintf(stderr,
                    "Erro ao criar a thread %d.\n", i);

            // Aguarda as threads que já foram criadas.
            for (int j = 0; j < i; j++) {
                pthread_join(threads[j], NULL);
            }

            return 1;
                }
    }

    for (int i = 0; i < NUM_FILOSOFOS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("\n========== VALIDACAO ==========\n");

    int totalRefeicoes = 0;

    for (int i = 0; i < NUM_FILOSOFOS; i++) {

        assert(filosofos[i].refeicoes == NUM_REFEICOES);

        assert(gerenciador.garfos[i] == true);

        totalRefeicoes += filosofos[i].refeicoes;
    }

    assert(filaVazia(&gerenciador.fila));

    assert(
        totalRefeicoes == NUM_FILOSOFOS * NUM_REFEICOES
    );

    printf("Todos os filosofos completaram suas refeicoes.\n");
    printf("Todos os garfos foram liberados.\n");
    printf("Fila de espera vazia.\n");
    printf("Total de refeicoes: %d\n", totalRefeicoes);
    printf("Validacao concluida com sucesso.\n");

    printf("\n========== RESULTADO FINAL ==========\n");

    for (int i = 0; i < NUM_FILOSOFOS; i++) {

        double media = filosofos[i].refeicoes > 0
            ? filosofos[i].tempoEsperaTotal
              / filosofos[i].refeicoes
            : 0.0;

        printf("\nFilosofo %d\n", filosofos[i].id);

        printf("Refeicoes realizadas: %d\n",
               filosofos[i].refeicoes);

        printf("Tempo total de espera: %.3fs\n",
               filosofos[i].tempoEsperaTotal);

        printf("Tempo medio de espera: %.3fs\n",
               media);

        printf("Maior tempo de espera: %.3fs\n",
               filosofos[i].maiorTempoEspera);
    }

    printf("\nTempo total de execucao: %.3fs\n",
           tempoDecorrido());

    destruirGerenciador(&gerenciador);

    destruirLogger();

    return 0;
}

// #include <stdio.h>
// #include "filosofos.h"
// #include "gerenciador.h"
//
// int main(void) {
//
//     Gerenciador gerenciador;
//
//     inicializarGerenciador(&gerenciador);
//
//     Filosofo f0 = {
//         .id = 0,
//         .garfoEsquerdo = 0,
//         .garfoDireito = 1
//     };
//
//     Filosofo f1 = {
//         .id = 1,
//         .garfoEsquerdo = 1,
//         .garfoDireito = 2
//     };
//
//     Filosofo f3 = {
//         .id = 3,
//         .garfoEsquerdo = 3,
//         .garfoDireito = 4
//     };
//
//     // Insere os filosofos na fila.
//     inserirFila(&gerenciador.fila, f0.id);
//     inserirFila(&gerenciador.fila, f1.id);
//     inserirFila(&gerenciador.fila, f3.id);
//
//     printf("Primeiro da fila: %d\n",
//            primeiroFila(&gerenciador.fila));
//
//     // Verifica se F0 pode comer.
//     if (podeComer(&gerenciador, &f0)) {
//
//         reservarGarfos(&gerenciador, &f0);
//
//         removerFila(&gerenciador.fila);
//
//         printf("Filosofo 0 autorizado a comer.\n");
//     }
//
//     // F1 precisa de um garfo ocupado por F0.
//     printf("Filosofo 1 pode comer? %s\n",
//            podeComer(&gerenciador, &f1) ? "SIM" : "NAO");
//
//     // F3 tem garfos livres, mas nao e o primeiro.
//     printf("Filosofo 3 pode comer? %s\n",
//            podeComer(&gerenciador, &f3) ? "SIM" : "NAO");
//
//     // F0 termina sua refeicao.
//     liberarGarfos(&gerenciador, &f0);
//
//     printf("Filosofo 0 liberou seus garfos.\n");
//
//     printf("Filosofo 1 pode comer? %s\n",
//            podeComer(&gerenciador, &f1) ? "SIM" : "NAO");
//
//     return 0;
// }
