//
// Created by mdaud on 25/11/2026.
//

#ifndef LOGGER_H
#define LOGGER_H

void inicializarLogger(void);

void destruirLogger(void);

double tempoDecorrido(void);

void registrarLog(int id, const char *formato, ...);

#endif
