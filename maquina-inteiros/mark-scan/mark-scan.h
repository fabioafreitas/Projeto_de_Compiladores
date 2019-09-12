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

static noh* freeList;

//Cria uma lista de celulas livres
//as celulas podem ser utilizadas
//a partir do ponteiro freeList
void inicializarHeap() {
    int aux = 0;
    freeList = (noh*) malloc(sizeof(noh));
    freeList->esq = NULL;
    while(aux < H) {
        noh* celula = (noh*) malloc(sizeof(noh));
        celula->esq = freeList->esq;
        celula->gb = 'L';
        freeList->esq = celula;
        aux++;
    }
}

//Devolve as celulas em desuso para a freeList
void markScan() {
    //TODO fazer algoritmo mark scan
}

//Atribui um caracter para o tipo (@ ou combinador)
//Atribui o estado de 'O' ao node, indicanod qu está ocupado
//Atribui NULL, para os ponteiros esquerda e direita
//Retorna um dos nodes da heap
node alocarNode(int tipo) {
    if(freeList->esq == NULL) { //Heap Cheia
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


#endif //PROJETO_DE_COMPILADORES_HEAP_H
