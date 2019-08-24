cmake_minimum_required(VERSION 3.14)
project(Projeto_de_Compiladores C)

set(CMAKE_C_STANDARD 99)

add_executable(Projeto_de_Compiladores main.c headers/grafo.h headers/combinadores.h headers/heap.h)