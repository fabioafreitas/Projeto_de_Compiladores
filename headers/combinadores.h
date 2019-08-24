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
    int size = 0;
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

}

void reduzS(node grafo) {

}

char reduzirGrafo(node grafo) {
    int size = tamanhoGrafo(grafo);
    while(size > 1) {
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
    return grafo->tipo;
}


#endif //PROJETO_DE_COMPILADORES_COMBINADORES_H
