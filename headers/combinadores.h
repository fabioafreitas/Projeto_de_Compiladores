//
// Created by fabio on 23/08/2019.
//
// Implementação dos combinadores
// responsáveis por reduzir o grafo.
//

#ifndef PROJETO_DE_COMPILADORES_COMBINADORES_H
#define PROJETO_DE_COMPILADORES_COMBINADORES_H

#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

int tamanhoGrafo(node grafo) {
    int size = -1; //desconsiderando o nó raiz
    node aux = grafo;
    while(aux != NULL) {
        size++;
        aux = aux->esq;
    }
    return size;
}

char buscaCombinador(node grafo) {
    node aux = grafo;
    while(aux->esq != NULL)
        aux = aux->esq;
    return aux->tipo;
}

void reduzK(node grafo) {
    int size = tamanhoGrafo(grafo);
    node aux = grafo;
    while(size > 3) {
        aux = aux->esq;
        size--;
    }
    aux->esq = aux->esq->esq->dir;
}

void reduzS(node grafo) {
    int size = tamanhoGrafo(grafo);
    node aux = grafo;
    while(size > 4) {
        aux = aux->esq;
        size--;
    }
    node arroba1 = criarNode('@');
    node arroba2 = criarNode('@');
    node arroba3 = criarNode('@');

    arroba1->esq = arroba2;
    arroba1->dir = arroba3;

    arroba2->esq = aux->esq->esq->esq->dir;
    arroba2->dir = aux->esq->dir;

    arroba3->esq = aux->esq->esq->dir;
    arroba3->dir = aux->esq->dir;

    aux->esq = arroba1;
}

//TODO otimizar redução de grafo (ideias: pilha/lista encadeada)
char reduzirGrafo(node grafo) {
    int size = tamanhoGrafo(grafo);
    while(size > 1) {
        //printGrafo(grafo);
        //printf("\n");
        char combinador = buscaCombinador(grafo);
        switch(combinador) {
            case 'K':
                reduzK(grafo);
                break;
            case 'S':
                reduzS(grafo);
                break;
            default:
                break;
        }
        size = tamanhoGrafo(grafo);
    }
    return grafo->esq->tipo;
}


#endif //PROJETO_DE_COMPILADORES_COMBINADORES_H
