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
#include "garbage-collection.h"

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

//K a b = a
void reduzK(node grafo) {
    int size = tamanhoGrafo(grafo);
    node aux = grafo;
    while(size > 3) {
        aux = aux->esq;
        size--;
    }
    aux->esq = aux->esq->esq->dir; //argumento A
}

//S a b c = a c ( b c )
void reduzS(node grafo) {
    int size = tamanhoGrafo(grafo);
    node aux = grafo;
    while(size > 4) {
        aux = aux->esq;
        size--;
    }
    node arroba1 = alocarNode('@');
    node arroba2 = alocarNode('@');
    node arroba3 = alocarNode('@');

    arroba1->esq = arroba2;
    arroba1->dir = arroba3;

    arroba2->esq = aux->esq->esq->esq->dir; //argumento A
    arroba2->dir = aux->esq->dir; //argumento C

    arroba3->esq = aux->esq->esq->dir; //argumento B
    arroba3->dir = aux->esq->dir; //argumento C

    aux->esq = arroba1;
}

//I a = a
void reduzI(node grafo) {
    int size = tamanhoGrafo(grafo);
    node aux = grafo;
    while(size > 2) {
        aux = aux->esq;
        size--;
    }
    aux->esq = aux->esq->dir; //argumento A
}

//B a b c = a ( b c )
void reduzB(node grafo) {
    int size = tamanhoGrafo(grafo);
    node aux = grafo;
    while(size > 4) {
        aux = aux->esq;
        size--;
    }
    node arroba1 = alocarNode('@');
    node arroba2 = alocarNode('@');

    arroba1->dir = arroba2;

    arroba1->esq = aux->esq->esq->esq->dir; //argumento A
    arroba2->esq = aux->esq->esq->dir; //argumento B
    arroba2->dir = aux->esq->dir; //argumenro C

    aux->esq = arroba1;
}

//C a b c = a c b
void reduzC(node grafo) {
    int size = tamanhoGrafo(grafo);
    node aux = grafo;
    while(size > 4) {
        aux = aux->esq;
        size--;
    }
    node arroba1 = alocarNode('@');
    node arroba2 = alocarNode('@');

    arroba1->esq = arroba2;

    arroba1->dir = aux->esq->esq->dir; //argumento B
    arroba2->dir = aux->esq->dir; //argumento C
    arroba2->esq = aux->esq->esq->esq->dir; //argumento A

    aux->esq = arroba1;
}

//D a b c d = a ( b d ) ( c d )
void reduzD(node grafo) {
    int size = tamanhoGrafo(grafo);
    node aux = grafo;
    while(size > 5) {
        aux = aux->esq;
        size--;
    }
    node arroba1 = alocarNode('@');
    node arroba2 = alocarNode('@');
    node arroba3 = alocarNode('@');
    node arroba4 = alocarNode('@');

    arroba1->esq = arroba2;
    arroba1->dir = arroba3;

    arroba2->dir = arroba4;
    arroba2->esq = aux->esq->esq->esq->esq->dir; //argumento A

    arroba4->esq = aux->esq->esq->esq->dir; //argumento B
    arroba4->dir = aux->esq->dir; //argumento D

    arroba3->esq = aux->esq->esq->dir; //argumento C
    arroba3->dir = aux->esq->dir; //argumento D

    aux->esq = arroba1;
}

//E a b c d = a b ( c d )
void reduzE(node grafo) {
    int size = tamanhoGrafo(grafo);
    node aux = grafo;
    while(size > 5) {
        aux = aux->esq;
        size--;
    }
    node arroba1 = alocarNode('@');
    node arroba2 = alocarNode('@');
    node arroba3 = alocarNode('@');

    arroba1->esq = arroba2;
    arroba1->dir = arroba3;

    arroba2->esq = aux->esq->esq->esq->esq->dir; //argumento A
    arroba2->dir = aux->esq->esq->esq->dir; //argumento B

    arroba3->esq = aux->esq->esq->dir; //argumento C
    arroba3->dir = aux->esq->dir; //argumento D

    aux->esq = arroba1;
}

//F a b c d = a ( b d ) c
void reduzF(node grafo) {
    int size = tamanhoGrafo(grafo);
    node aux = grafo;
    while(size > 5) {
        aux = aux->esq;
        size--;
    }
    node arroba1 = alocarNode('@');
    node arroba2 = alocarNode('@');
    node arroba3 = alocarNode('@');

    arroba1->esq = arroba2;
    arroba1->dir = aux->esq->esq->dir; //argumento C

    arroba2->dir = arroba3;
    arroba2->esq = aux->esq->esq->esq->esq->dir; //argumento A

    arroba3->esq = aux->esq->esq->esq->dir; //argumento B
    arroba3->dir = aux->esq->dir; //argumento D

    aux->esq = arroba1;
}

//TODO otimizar redução de grafo (ideias: pilha/lista encadeada)
void reduzirGrafo(node grafo) {
    while(grafo->esq->tipo == '@') {
        //printGrafo(grafo);
        //printf("\n");
        char combinador = buscaCombinador(grafo);
        switch(combinador) {
            case 'K': reduzK(grafo);
                break;
            case 'S': reduzS(grafo);
                break;
            case 'I': reduzI(grafo);
                break;
            case 'B': reduzB(grafo);
                break;
            case 'C': reduzC(grafo);
                break;
            case 'D': reduzD(grafo);
                break;
            case 'E': reduzE(grafo);
                break;
            case 'F': reduzF(grafo);
                break;
            default:
                break;
        }
    }
}


#endif //PROJETO_DE_COMPILADORES_COMBINADORES_H
