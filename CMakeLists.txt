cmake_minimum_required(VERSION 4.2)
project(JantarComFilosofosTPE2 C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable(JantarComFilosofosTPE2
        main.c
        filosofos.c
        filosofos.h
        fila.c
        fila.h
        gerenciador.c
        gerenciador.h
        logger.c
        logger.h
)

target_link_libraries(
        JantarComFilosofosTPE2
        PRIVATE Threads::Threads
)