//
// Created by mdaud on 25/11/2026.
//

#include "logger.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <pthread.h>
#include <windows.h>

static LARGE_INTEGER inicio;

static LARGE_INTEGER frequencia;

static pthread_mutex_t mutexLog;

void inicializarLogger(void) {

    if (!QueryPerformanceFrequency(&frequencia) ||
        !QueryPerformanceCounter(&inicio)) {

        fprintf(stderr, "Erro ao inicializar contador.\n");
        exit(EXIT_FAILURE);
        }

    if (pthread_mutex_init(&mutexLog, NULL) != 0) {

        fprintf(stderr, "Erro ao inicializar logger.\n");
        exit(EXIT_FAILURE);
    }
}

double tempoDecorrido(void) {

    LARGE_INTEGER atual;

    QueryPerformanceCounter(&atual);

    return
        (double)(atual.QuadPart - inicio.QuadPart)
        / (double)frequencia.QuadPart;
}

void registrarLog(int id, const char *formato, ...) {

    pthread_mutex_lock(&mutexLog);

    printf("[%.3fs] Filosofo %d: ",
           tempoDecorrido(), id);

    va_list argumentos;

    va_start(argumentos, formato);

    vprintf(formato, argumentos);

    va_end(argumentos);

    printf("\n");

    fflush(stdout);

    pthread_mutex_unlock(&mutexLog);
}

void destruirLogger(void) {

    pthread_mutex_destroy(&mutexLog);
}
