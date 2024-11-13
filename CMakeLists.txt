cmake_minimum_required(VERSION 3.27)
project(projet2 C)

set(CMAKE_C_STANDARD 11)

add_executable(projet2 main.c
        loc.c
        map.c
        moves.c
        queue.c
        stack.c
)
