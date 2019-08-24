//
// Created by fabio on 23/08/2019.
//
// Struct que armazena um célula
// utilizada na heap
//

#ifndef PROJETO_DE_COMPILADORES_HEAP_H
#define PROJETO_DE_COMPILADORES_HEAP_H

#define H 1000000 //Tamanho da Heap

// Estrutura de um noh da memoria
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
node criarNode(char tipo) {
    if(heapIndex == H) {
        printf("Heap Cheia\n");
        return NULL;
    }
    heap[heapIndex].tipo = tipo;
    heap[heapIndex].esq = heap[heapIndex].dir = NULL;
    return &heap[heapIndex++];
}


#endif //PROJETO_DE_COMPILADORES_HEAP_H
