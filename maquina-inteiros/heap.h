//
// Created by fabio on 23/08/2019.
//
// Struct que armazena um célula
// utilizada na heap
//
// Funcoes que gerenciam a heap
//
// Aloca os combinadores base
//

#ifndef PROJETO_DE_COMPILADORES_HEAP_H
#define PROJETO_DE_COMPILADORES_HEAP_H

#include <stdio.h>
#include <stdlib.h>


typedef struct reg {
    int tipo;
    char gb;
    struct reg *dir;
    struct reg *esq;
} noh;
typedef noh* node;

int H = 1000; //Tamanho da Heap
static noh* heap;
static int heapIndex = 0;
static node rootGrafo;

//Atribui um caracter para o tipo (@ ou combinador)
//Atribui o estado de 'O' ao node, indicanod qu está ocupado
//Atribui NULL, para os ponteiros esquerda e direita
//Retorna um dos nodes da heap
node alocarNode(int tipo) {
    if(heapIndex == H) {
        printf("Heap Cheia\n");
        exit(0);
    }
    heap[heapIndex].tipo = tipo;
    heap[heapIndex].gb = 'O';
    heap[heapIndex].esq = heap[heapIndex].dir = NULL;
    return &heap[heapIndex++];
}

//Atribui o estado 'L' a todos
//os nodes da heap, indicando
//que estão Livres para serem
//alocados
void inicializarHeap(int sizeHeap) {
    H = sizeHeap;
    heap = (noh*) malloc(sizeof(noh) * H);
    int i = 0;
    while(i < H) {
        heap[i++].gb = 'L';
    }
}

#endif //PROJETO_DE_COMPILADORES_HEAP_H
