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


static node tokens[128];
static noh* heap;       //Ponteiro para a heap
static noh* rootGrafo;  //Ponteiro a cabeça do grafo
static noh* freeList;   //Ponteiro para a freelist

static int sizeFreeList;

//Este procedimento cria o vetor da heap e
//adiciona todas essas celulas à freelist
//e marca o bit do gabage collection com '0'
void inicializarHeap() {
    sizeFreeList = H; //o tamanho inicial da freelist, é o tamanho da HEAP
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

//TODO observar esta funcao
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
        printf("\nErro: Tentou Alocar Celula Com FreeList Vazia\n");
        exit(0);
    }
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
    tokens[-1 * S]->gb = CELULA_OCUPADA;
    tokens[-1 * K]->gb = CELULA_OCUPADA;
    tokens[-1 * I]->gb = CELULA_OCUPADA;
    tokens[-1 * B]->gb = CELULA_OCUPADA;
    tokens[-1 * C]->gb = CELULA_OCUPADA;
    tokens[-1 * D]->gb = CELULA_OCUPADA;
    tokens[-1 * E]->gb = CELULA_OCUPADA;
    tokens[-1 * F]->gb = CELULA_OCUPADA;
    tokens[-1 * Y]->gb = CELULA_OCUPADA;
    tokens[-1 * SOMA]->gb = CELULA_OCUPADA;
    tokens[-1 * SUBTRACAO]->gb = CELULA_OCUPADA;
    tokens[-1 * MULTIPLICACAO]->gb = CELULA_OCUPADA;
    tokens[-1 * DIVISAO]->gb = CELULA_OCUPADA;
    tokens[-1 * TRUE]->gb = CELULA_OCUPADA;
    tokens[-1 * FALSE]->gb = CELULA_OCUPADA;
    tokens[-1 * MENORQUE]->gb = CELULA_OCUPADA;
    tokens[-1 * MAIORQUE]->gb = CELULA_OCUPADA;
    tokens[-1 * IGUALDADE]->gb = CELULA_OCUPADA;
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

    marcarTokens();
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
    sizeFreeList = 0;
    while(i < H) {
        if(heap[i].gb != CELULA_OCUPADA) {
            heap[i].esq = freeList->esq;
            freeList->esq = &heap[i];
            sizeFreeList++;
        }
        i++;
    }
}

void markScan() {
//    int i = 0;
//    while(i < H) {
//        heap[i++].gb = CELULA_LIVRE;
//    }

    marcarTokens();
    marcarGrafo(rootGrafo);

    varrerHeap();
}

#endif //PROJETO_DE_COMPILADORES_HEAP_H
