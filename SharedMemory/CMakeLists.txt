cmake_minimum_required(VERSION 3.8)
project(SharedMemory)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES main.c headers/imports.h
                        headers/inicializador.h     sources/inicializador.c
                        headers/productor.h         sources/productor.c
                        headers/espia.h             sources/espia.c
                        headers/finalizador.h       sources/finalizador.c
                        headers/herramientas.h      sources/herramientas.c
                        headers/pagina.h            sources/pagina.c
        headers/segmento.h          sources/segmento.c)


find_package( Threads REQUIRED )

add_executable( inic ${SOURCE_FILES})
target_link_libraries( inic Threads::Threads )

add_executable( prod ${SOURCE_FILES})
target_link_libraries( prod Threads::Threads )


add_executable( espia ${SOURCE_FILES} headers/herramientas.h)
target_link_libraries( espia Threads::Threads )


add_executable(fin ${SOURCE_FILES})
target_link_libraries( fin Threads::Threads )