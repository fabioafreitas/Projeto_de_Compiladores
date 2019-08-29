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

#define H 1000000 //Tamanho da Heap

// Estrutura de um noh da memoria
// tipo pode ser @ ou combinador (S, K, I, B, C, D, E ou F)
// status pode ser L = Livre ou O = Ocupada
typedef struct reg {
    char tipo;
    char status;
    struct reg *dir;
    struct reg *esq;
} noh;
typedef noh* node;

static noh heap[H];
static int heapIndex = 0;

//Retorna um dos nodes da heap
//TODO utilizar o status do node
node alocarNode(char tipo) {
    if(heapIndex == H) {
        printf("Heap Cheia\n");
        exit(0);
    }
    heap[heapIndex].tipo = tipo;
    heap[heapIndex].esq = heap[heapIndex].dir = NULL;
    return &heap[heapIndex++];
}

#endif //PROJETO_DE_COMPILADORES_HEAP_H
