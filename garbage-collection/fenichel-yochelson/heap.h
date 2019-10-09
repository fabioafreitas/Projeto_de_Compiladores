//
// Created by fabio on 23/08/2019.
//
// Armazena a Struct das celulas da heap
//
// Armazena o algoritmo de garbage collection, fenichel yochelson
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

static int H;          //Variável global que representa o tamanho da HEAP

static noh* heap1;      //Ponteiro para a HEAP1
static noh* heap2;      //Ponteiro para a HEAP2
static noh* heapAux;      //Ponteiro Aux, usado no funcionamento do GC

static node tokens[128];//Otimização que reutiliza combinadores
static noh* rootGrafo;  //Ponteiro a cabeça do grafo
static int heapPointer; //Varialvel que conta a proxima celula livre de heap atual

//Procedimento que recebe o tamanho total da heap
//e aloca duas heaps com o tamanho total divido por 2
void inicializarHeap(int sizeHeap) {
    H = sizeHeap;
    heap1 = (noh*) malloc(sizeof(noh) * (H/2));
    heap2 = (noh*) malloc(sizeof(noh) * (H/2));
    heapAux = (noh*) malloc(sizeof(noh));
    heapPointer = 0;
}


//Retorna um node da heap em uso atual
//recebe o tipo de dado a ser armazenado no
//campo tipo do node
node alocarNode(int tipo) {
    node celulaAlocada = &heap1[heapPointer++];
    celulaAlocada->tipo = tipo;
    celulaAlocada->esq = celulaAlocada->dir = NULL;
    return celulaAlocada;
}


//Aloca os tokens que sao utilizados
//na construcao e reducao do grafo
//So eh necessaria uma unidade de cada,
//pois eles sao reutilizados, reduzindo
//o gasto de memoria da heap
void alocarTokens() {
    tokens[-1 * K] = alocarNode(K);
    tokens[-1 * S] = alocarNode(S);
    tokens[-1 * I] = alocarNode(I);
    tokens[-1 * B] = alocarNode(B);
    tokens[-1 * C] = alocarNode(C);
    tokens[-1 * D] = alocarNode(D);
    tokens[-1 * E] = alocarNode(E);
    tokens[-1 * F] = alocarNode(F);
    tokens[-1 * Y] = alocarNode(Y);
    tokens[-1 * SOMA] = alocarNode(SOMA);
    tokens[-1 * SUBTRACAO] = alocarNode(SUBTRACAO);
    tokens[-1 * MULTIPLICACAO] = alocarNode(MULTIPLICACAO);
    tokens[-1 * DIVISAO] = alocarNode(DIVISAO);
    tokens[-1 * TRUE] = alocarNode(TRUE);
    tokens[-1 * FALSE] = alocarNode(FALSE);
    tokens[-1 * MENORQUE] = alocarNode(MENORQUE);
    tokens[-1 * MAIORQUE] = alocarNode(MAIORQUE);
    tokens[-1 * IGUALDADE] = alocarNode(IGUALDADE);
}

//Recebe um grafo e o copia para a heap vazia
node copiarGrafoEmUso(node grafo) {
    if(grafo == NULL) {
        return NULL;
    }

    int currentIndex = heapPointer++;
    heap2[currentIndex].tipo = grafo->tipo;
    grafo->gb = CELULA_VISITADA;
    //TODO tratar celulas que são apontadas por mais de um ponteiro

    node auxEsq, auxDir;

    //redundancia
    if(grafo == grafo->esq) heap2[currentIndex].esq = &heap2[currentIndex];
    else auxEsq = copiarGrafoEmUso(grafo->esq);

    //redundancia
    if(grafo == grafo->dir) heap2[currentIndex].dir = &heap2[currentIndex];
    else auxDir = copiarGrafoEmUso(grafo->dir);

    heap2[currentIndex].esq = auxEsq;
    heap2[currentIndex].dir = auxDir;

    return &heap2[currentIndex];
}

//marca as celulas do grafo em uso como
//CELULA_NAO_VISITADA, para evitar a cópia
//da mesma célula mais de uma vez
void marcarGrafo(node grafo) {
    if(grafo != NULL) {
        grafo->gb = CELULA_NAO_VISITADA;
        if(grafo->esq != NULL)
            marcarGrafo(grafo->esq);
        if(grafo->dir != NULL)
            marcarGrafo(grafo->dir);
    }
}

void fenichelYochelson() {
    marcarGrafo(rootGrafo);

    //copiar grafo em uso para heap2
    heapPointer = 0;
    rootGrafo = copiarGrafoEmUso(rootGrafo);

    //trocando ponteiros de heap1 e heap2
    heapAux = heap1;
    heap1 = heap2;
    heap2 = heapAux;
}


#endif //PROJETO_DE_COMPILADORES_HEAP_H
