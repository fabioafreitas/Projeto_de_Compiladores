//
// Created by fabio on 23/08/2019.
//
// Armazena a Struct das celulas da heap
//
// Armazena o algoritmo de garbage collection, mark scan
//

#ifndef PROJETO_DE_COMPILADORES_HEAP_H
#define PROJETO_DE_COMPILADORES_HEAP_H

#include <stdio.h>
#include <stdlib.h>
#define H 100000000 //Tamanho da Heap

typedef struct reg {
    int tipo;
    char gb;
    struct reg *dir;
    struct reg *esq;
} noh;
typedef noh* node;

static node heap;
static node freeList;

//Cria uma lista de celulas livres
//as celulas podem ser utilizadas
//a partir do ponteiro freeList
void inicializarHeap() {
    int aux = 0;
    heap = (node) malloc(sizeof(noh) * H);
    freeList = (node) malloc(sizeof(noh));
    freeList->esq = NULL;
    while(aux < H) {
        node celula = &heap[aux];
        celula->esq = freeList->esq;
        celula->gb = 'L';
        freeList->esq = celula;
        aux++;
    }
}

//Devolve as celulas em desuso para a freeList
void markScan() {
    int i = 0;
    freeList->esq = NULL;
    while(i < H) {
        if(heap[i].gb == 'L') {
            node celula = &heap[i];
            celula->esq = freeList->esq;
            freeList->esq = celula;
        }
    }
}



//Atribui um caracter para o tipo (@ ou combinador)
//Atribui o estado de 'O' ao node, indicanod qu está ocupado
//Atribui NULL, para os ponteiros esquerda e direita
//Retorna um dos nodes da heap
node alocarNode(int tipo) {
    if(freeList->esq == NULL) { //Heap Cheia
        printf("\nChamando Garbage Collector");
        markScan();
    }
    //Alocando celula da freeList
    node celulaAlocada = freeList->esq;
    celulaAlocada->gb = 'O';
    celulaAlocada->tipo = tipo;
    celulaAlocada->esq = celulaAlocada->dir = NULL;

    //Reorganizando o ponteiro da freeList
    freeList->esq = freeList->esq->esq;
    return celulaAlocada;
}

// Atribui o status Livre para
// um node ja alocado
void liberarNode(node celula) {
    celula->gb = 'L';
}
#endif //PROJETO_DE_COMPILADORES_HEAP_H
