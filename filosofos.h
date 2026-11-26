#ifndef FILOSOFOS_H
#define FILOSOFOS_H

#define NUM_FILOSOFOS 5
#define NUM_REFEICOES 10

#define TEMPO_PENSANDO 1000
#define TEMPO_COMENDO 1000

typedef enum {
    PENSANDO,
    TENTANDO_COMER,
    COMENDO
} Estado;

typedef struct {
    int id;
    Estado estado;
    int refeicoes;
    int garfoEsquerdo;
    int garfoDireito;
    struct Gerenciador *gerenciador;
    double tempoEsperaTotal;
    double maiorTempoEspera;
} Filosofo;

struct Gerenciador;

void pensar(Filosofo *filosofo);

void tentarComer(Filosofo *filosofo);

void comer(Filosofo *filosofo);

void *rotinaFilosofo(void *arg);

#endif

