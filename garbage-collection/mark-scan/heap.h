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
    char gc;
    struct reg *dir;
    struct reg *esq;
} noh;
typedef noh* node;

static node tokens[128];//Otimização que reutiliza combinadores
static noh heap[H];       //Ponteiro para a heap
static noh* rootGrafo;  //Ponteiro a cabeça do grafo
static noh* freeList;   //Ponteiro para a freelist
static int sizeFreeList;//Variavel que guarda o Tamanho da freelist

//Este procedimento recebe a quantidade de
//celulas da heap e cria um vetor que as contem.
//Adiciona todas essas celulas à freelist
//e marca o bit do gabage collection com '0' (CELULA_LIVRE)
void inicializarHeap() {
    sizeFreeList = H;
    freeList = (noh*) malloc(sizeof(noh));
    freeList->esq = NULL;

    int aux = 0;
    while(aux < H) {
        heap[aux].esq = freeList->esq;
        heap[aux].gc = CELULA_LIVRE;
        freeList->esq = &heap[aux];
        aux++;
    }
}

//Retorna a quantidade de celulas presentes na freelist
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
//    if(sizeFreeList == 0) {
//        printf("\nErro: Tentou Alocar Celula Com FreeList Vazia\n");
//        exit(0);
//    }
    sizeFreeList--;

    //Alocando celula da freeList
    node celulaAlocada = freeList->esq;

    //Reorganizando o ponteiro da freeList
    freeList->esq = freeList->esq->esq;

    celulaAlocada->tipo = tipo;
    celulaAlocada->esq = celulaAlocada->dir = NULL;
    return celulaAlocada;
}

//Marca as celulas reservadas para aos combinadores t
//como CELULAS_OCUPADAS, pois estas celulas nao podem
//ser desalocadas, uma vez que só existe uma unidade
//de cada combinador no backend
void marcarTokens() {
    int i;
    int constante[18] = {K, S, I, B, C, D, E, F, Y, SOMA, SUBTRACAO, MULTIPLICACAO,
                         DIVISAO, TRUE, FALSE, MENORQUE, MAIORQUE, IGUALDADE};
    for(i = 0 ; i < 18 ; i++) {
        tokens[-1 * constante[i]]->gc = CELULA_OCUPADA;
    }
}

//Aloca os tokens que sao utilizados
//na construcao e reducao do grafo
//So eh necessaria uma unidade de cada,
//pois eles sao reutilizados, reduzindo
//o gasto de memoria da heap
void alocarTokens() {
    int i;
    int constante[18] = {K, S, I, B, C, D, E, F, Y, SOMA, SUBTRACAO, MULTIPLICACAO,
                         DIVISAO, TRUE, FALSE, MENORQUE, MAIORQUE, IGUALDADE};
    for(i = 0 ; i < 18 ; i++) {
        tokens[-1 * constante[i]] = alocarNode( constante[i] );
    }
    marcarTokens();
}

//Este procedimento é a fase de mark, do algoritmo mark scan.
//Ele marca todas as celulas conectadas ao grafo com '1'
void marcarGrafo(node grafo) {
    grafo->gc = CELULA_OCUPADA;
    if(grafo->esq != NULL)
        marcarGrafo(grafo->esq);
    if(grafo->dir != NULL && grafo->dir != grafo)
        marcarGrafo(grafo->dir);
}

//Este procedimento varre toda a heap e devolve para a freelist
//todas as celulas não marcadas com '1'
void varrerHeap() {
    int i = 0;
    freeList->esq = NULL;
    sizeFreeList = 0;
    while(i < H) {
        if(heap[i].gc != CELULA_OCUPADA) {
            heap[i].esq = freeList->esq;
            freeList->esq = &heap[i];
            sizeFreeList++;
        }
        i++;
    }
}

//Algoritmo de garbage collection, Mark-Scan
void markScan() {
    marcarTokens();
    marcarGrafo(rootGrafo);
    varrerHeap();
}

#endif //PROJETO_DE_COMPILADORES_HEAP_H
