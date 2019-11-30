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
    struct reg *dir;
    struct reg *esq;
} noh;
typedef noh* node;

static node tokens[128];//Otimização que reutiliza combinadores

static noh heap1[H/2];      //Ponteiro para a HEAP1
static noh heap2[H/2];      //Ponteiro para a HEAP2
static noh* rootGrafo;      //Ponteiro a cabeça do grafo
static int heapPointer = 0; //Variavel que indica a proxima celula livre de heap atual
static int copyPointer = 0; //Variavel que indica a celula que está sendo copiada atualmente
static int currentHeap = 1; //Indica qual heap deve ser usada atualmente. (1) -> heap1, (2) -> heap2

//Retorna um node da heap em uso atual
//recebe o tipo de dado a ser armazenado no
//campo tipo do node
node alocarNode(int tipo) {
    if(heapPointer >= H/2) {
        printf("\nErro: HeapPointer maior que Heap/2\n");
        exit(0);
    }
    node celulaAlocada = (currentHeap == 1) ? &heap1[heapPointer++] : &heap2[heapPointer++];
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
    int i;
    int constante[18] = {K, S, I, B, C, D, E, F, Y, SOMA, SUBTRACAO, MULTIPLICACAO,
                          DIVISAO, TRUE, FALSE, MENORQUE, MAIORQUE, IGUALDADE};
    for(i = 0 ; i < 18 ; i++) {
        tokens[-1 * constante[i]] = alocarNode( constante[i] );
    }
}

void copiaTokens() {
    int i;
    int constante[18] = {K, S, I, B, C, D, E, F, Y, SOMA, SUBTRACAO, MULTIPLICACAO,
                  DIVISAO, TRUE, FALSE, MENORQUE, MAIORQUE, IGUALDADE};
    for(i = 0 ; i < 18 ; i++) {
        int index = heapPointer++;
        node nodeCopia = (currentHeap == 1) ? &heap1[index] : &heap2[index];

        //Copiando conteudo
        nodeCopia->tipo = tokens[-1 * constante[i]]->tipo;
        nodeCopia->esq = tokens[-1 * constante[i]]->esq;
        nodeCopia->dir = tokens[-1 * constante[i]]->dir;

        //Criando foward pointer
        tokens[-1 * constante[i]]->esq = nodeCopia;
        tokens[-1 * constante[i]]->dir = NULL;

        //Atribuindo nova celula no vetor
        tokens[-1 * constante[i]] = nodeCopia;
    }
}

//Recebe um grafo e o copia para a heap vazia
node copiarGrafo(node grafo) {
    copyPointer = heapPointer;

    node auxEsq, auxDir, nodeCopiaAtual;

    node nodeCopia = alocarNode(grafo->tipo);
    nodeCopia->esq = grafo->esq;
    nodeCopia->dir = grafo->dir;
    grafo->esq = nodeCopia;
    grafo->dir = NULL;

    while(copyPointer < heapPointer) {
        if(copyPointer > (H/2)) {
            printf("Erro: Memoria cheia");
            exit(0);
        }

        nodeCopiaAtual = (currentHeap == 1) ? &heap1[copyPointer] : &heap2[copyPointer];
        auxEsq = nodeCopiaAtual->esq;
        auxDir = nodeCopiaAtual->dir;

        //Foward Pointer
        if(auxEsq != NULL) {
            if (auxEsq->dir == NULL && auxEsq->esq != NULL) {
                nodeCopia->esq = auxEsq->esq;
            } else {
                node nodeCopiaEsq = alocarNode(auxEsq->tipo);
                nodeCopiaEsq->esq = auxEsq->esq;
                nodeCopiaEsq->dir = auxEsq->dir;
                auxEsq->esq = nodeCopiaEsq;
                auxEsq->dir = NULL;
                nodeCopia->esq = nodeCopiaEsq;
            }
        }

        //Foward Pointer
        if(auxDir != NULL) {
            if (auxDir->dir == NULL && auxDir->esq != NULL) {
                nodeCopia->dir = auxDir->esq;
            } else {
                node nodeCopiaDir = alocarNode(auxDir->tipo);
                nodeCopiaDir->esq = auxDir->esq;
                nodeCopiaDir->dir = auxDir->dir;
                auxDir->esq = nodeCopiaDir;
                auxDir->dir = NULL;
                nodeCopia->esq = nodeCopiaDir;
            }
        }
        copyPointer++;
    }

    //O index 18 armazena a proxima posicao livre apos os tokens
    //Portanto, sera garantidamente a raiz do grafo copiado
    return (currentHeap == 1) ? &heap1[18] : &heap2[18];
}


void cheney() {
    currentHeap = (currentHeap == 1) ? 2 : 1;
    heapPointer = 0;
    copiaTokens();
    node grafo = copiarGrafo(rootGrafo->esq);
    rootGrafo = alocarNode(ROOT);
    rootGrafo->esq = grafo;
}


#endif //PROJETO_DE_COMPILADORES_HEAP_H
