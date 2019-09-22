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
#include "constantes.h"


typedef struct reg {
    int tipo;
    char gb;
    struct reg *dir;
    struct reg *esq;
} noh;
typedef noh* node;

static noh* heap;       //Ponteiro para a heap
static noh* rootGrafo;  //Ponteiro a cabeça do grafo
static noh* freeList;   //Ponteiro para a freelist

//Este procedimento cria o vetor da heap e
//adiciona todas essas celulas à freelist
//e marca o bit do gabage collection com '0'
void inicializarHeap() {
    int aux = 0;
    heap = (noh*) malloc(sizeof(noh) * H);
    freeList = (noh*) malloc(sizeof(noh));
    freeList->esq = NULL;
    while(aux < H) {
        heap[aux].esq = freeList->esq;
        heap[aux].gb = CELULA_LIVRE;
        freeList->esq = &heap[aux];
        aux++;
    }
}


int numeroCelulasGrafo(node grafo) {
    if(grafo == NULL) return 0;
    int x = 0;
    if(grafo->tipo == ARROBA || grafo->tipo == ROOT) {
        x = 1;
        if(grafo->esq != NULL) {
            x += numeroCelulasGrafo(grafo->esq);
        }
        if(grafo->dir != NULL) {
            x += numeroCelulasGrafo(grafo->dir);
        }
    }
    return x;
}

int tamanhoFreeList() {
    int i = 0;
    node aux = freeList;
    while(aux->esq != NULL) {
        aux = aux->esq;
        i++;
    }
    return i;
}



//Este procedimento retorna a primeira celula da freelist, se houverem
//celulas disponíveis, atribui um inteiro no campo Tipo desta celula
//e seta os ponteiros esq e dir para NULL.
node alocarNode(int tipo) {
    if(freeList->esq == NULL) {
        printf("\nErro: FreeList Vazia\n");
        exit(0);
    }
    //Alocando celula da freeList
    node celulaAlocada = freeList->esq;

    //Reorganizando o ponteiro da freeList
    freeList->esq = freeList->esq->esq;

    celulaAlocada->tipo = tipo;
    celulaAlocada->esq = celulaAlocada->dir = NULL;
    return celulaAlocada;
}

//Este procedimento é a fase de mark, do algoritmo mark scan.
//Ele marca todas as celulas conectadas ao grafo com '1'
void marcarGrafo(node grafo) {
    grafo->gb = CELULA_OCUPADA;
    if(grafo->esq != NULL)
        marcarGrafo(grafo->esq);
    if(grafo->dir != NULL)
        marcarGrafo(grafo->dir);
}

//Este procedimento varre toda a heap e devolve para a freelist
//todas as celulas não marcadas com '1'
void varrerHeap() {
    int i = 0;
    freeList->esq = NULL;
    while(i < H) {
        if(heap[i].gb != CELULA_OCUPADA) {
            heap[i].esq = freeList->esq;
            freeList->esq = &heap[i];
        }
        i++;
    }
}

void markScan() {
    int i = 0;
    while(i < H) {
        heap[i++].gb = CELULA_LIVRE;
    }
    marcarGrafo(rootGrafo);
    varrerHeap();
}

//TODO checar se é possível que uma celula fora do grafo pode ser marcada com CELULA_OCUPADA
//TODO salvar estado das reduções, para evitar que o markScan desaloque celulas que serão utilizadas nas reduções

//TODO após gerar o grafo, as raizes à direita podem ser descartadas










#endif //PROJETO_DE_COMPILADORES_HEAP_H
