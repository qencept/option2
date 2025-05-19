cmake_minimum_required(VERSION 3.28)
project(option2 C)

set(CMAKE_C_STANDARD 23)

set(CMAKE_BUILD_TYPE Release)

add_executable(option2 src/main.c
        src/source.c
        src/source.h
        src/flow.c
        src/flow.h
        src/comb.c
        src/comb.h
        src/csv.c
        src/csv.h
        src/processor.c
        src/processor.h
        src/hashmap.c
        src/hashmap.h)
