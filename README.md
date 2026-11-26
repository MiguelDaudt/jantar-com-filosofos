# Jantar dos Filósofos — TPE 2

Projeto acadêmico de Sistemas Operacionais, implementado em C para simular o problema do Jantar dos Filósofos com POSIX Threads, mutexes, variáveis de condição e fila circular FIFO.

## Funcionamento

Cinco filósofos alternam entre pensar, tentar comer e comer. Um gerenciador central reserva os dois garfos juntos, evitando posse e espera, e atende as solicitações em ordem FIFO, evitando ultrapassagens. A ausência de starvation pressupõe refeições finitas e progresso das threads.

## Compilação

Requer Windows, CMake 4.2 ou superior e uma toolchain C11 com pthreads (por exemplo, MinGW-w64 com suporte POSIX).

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
```

Execute o binário JantarComFilosofosTPE2.exe produzido no diretório de compilação. Também é possível abrir o CMakeLists.txt no CLion.

## Estrutura

- `main.c`: inicialização, criação das threads e validação final.
- `filosofos.c/.h`: estados e rotina dos filósofos.
- `fila.c/.h`: fila circular FIFO.
- `gerenciador.c/.h`: controle dos garfos e sincronização.
- `logger.c/.h`: logs temporais e medição de espera.

A configuração padrão simula cinco filósofos com dez refeições cada. O programa apresenta logs e estatísticas de espera; as verificações com assert permanecem ativas em Debug.

## Apoio de IA

O ChatGPT foi utilizado para orientação técnica, exemplos de código, apoio à implementação, logs, testes e documentação. A integração e execução local do projeto foram realizadas pelo autor.
