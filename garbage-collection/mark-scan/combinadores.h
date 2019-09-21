//
// Created by fabio on 23/08/2019.
//
// Implementação dos combinadores
// responsaveis por reduzir o grafo.
//

#ifndef PROJETO_DE_COMPILADORES_COMBINADORES_H
#define PROJETO_DE_COMPILADORES_COMBINADORES_H

#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

//Cabecalho para permitir que os combinadores chamem a funcao reduzirGrafo
void reduzirGrafo(node grafo);

int tamanhoGrafo(node grafo) {
    int size = -1; //desconsiderando o nó raiz
    node aux = grafo;
    while(aux != NULL) {
        size++;
        aux = aux->esq;
    }
    return size;
}

int buscaCombinador(node grafo) {
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
    node arroba1 = alocarNode(ARROBA);
    node arroba2 = alocarNode(ARROBA);
    node arroba3 = alocarNode(ARROBA);

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
    node arroba1 = alocarNode(ARROBA);
    node arroba2 = alocarNode(ARROBA);

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
    node arroba1 = alocarNode(ARROBA);
    node arroba2 = alocarNode(ARROBA);

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
    node arroba1 = alocarNode(ARROBA);
    node arroba2 = alocarNode(ARROBA);
    node arroba3 = alocarNode(ARROBA);
    node arroba4 = alocarNode(ARROBA);

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
    node arroba1 = alocarNode(ARROBA);
    node arroba2 = alocarNode(ARROBA);
    node arroba3 = alocarNode(ARROBA);

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
    node arroba1 = alocarNode(ARROBA);
    node arroba2 = alocarNode(ARROBA);
    node arroba3 = alocarNode(ARROBA);

    arroba1->esq = arroba2;
    arroba1->dir = aux->esq->esq->dir; //argumento C

    arroba2->dir = arroba3;
    arroba2->esq = aux->esq->esq->esq->esq->dir; //argumento A

    arroba3->esq = aux->esq->esq->esq->dir; //argumento B
    arroba3->dir = aux->esq->dir; //argumento D

    aux->esq = arroba1;
}

void reduzY(node grafo) {
    int size = tamanhoGrafo(grafo);
    node aux = grafo;
    while(size > 2) {
        aux = aux->esq;
        size--;
    }
    node arroba1 = alocarNode(ARROBA);
    node arroba2 = alocarNode(ARROBA);

    node argumentoA = aux->esq->dir;

    arroba1->dir = arroba2;
    arroba1->esq = argumentoA;

    arroba2->dir = argumentoA;
    arroba2->esq = atribuirToken('Y');

    aux->esq = arroba1;
}

// Outra forma de reduzir o combinador Y
void reduzY2(node grafo) {
    int size = tamanhoGrafo(grafo);
    node aux = grafo;
    while(size > 2) {
        aux = aux->esq;
        size--;
    }

    node arroba1 = alocarNode(ARROBA);
    arroba1->esq = aux->esq->dir;
    arroba1->dir = arroba1;

    aux->esq = arroba1;
}

/*##########  OPERADORES ARITIMÉTICOS E LÓGICOS #########*/

node avaliarExpressao(node argumento) {
    node subgrafo = alocarNode(EMPTY);
    subgrafo->esq = argumento;
    reduzirGrafo(subgrafo);
    return subgrafo->esq;
}

void reduzSoma(node grafo) {
    int size = tamanhoGrafo(grafo);
    node aux = grafo;
    while(size > 3) {
        aux = aux->esq;
        size--;
    }
    node argumentoB = aux->esq->dir;
    if(argumentoB->tipo == ARROBA)
        argumentoB = avaliarExpressao(argumentoB);

    node argumentoA = aux->esq->esq->dir;
    if(argumentoA->tipo == ARROBA)
        argumentoA = avaliarExpressao(argumentoA);

    int a = argumentoA->tipo;
    int b = argumentoB->tipo;
    node resultado = alocarNode(a+b);

    aux->esq = resultado;
}

void reduzSubtracao(node grafo) {
    int size = tamanhoGrafo(grafo);
    node aux = grafo;
    while(size > 3) {
        aux = aux->esq;
        size--;
    }
    node argumentoB = aux->esq->dir;
    if(argumentoB->tipo == ARROBA)
        argumentoB = avaliarExpressao(argumentoB);

    node argumentoA = aux->esq->esq->dir;
    if(argumentoA->tipo == ARROBA)
        argumentoA = avaliarExpressao(argumentoA);

    int a = argumentoA->tipo;
    int b = argumentoB->tipo;
    node resultado = alocarNode(a-b);

    aux->esq = resultado;
}

void reduzMultiplicacao(node grafo) {
    int size = tamanhoGrafo(grafo);
    node aux = grafo;
    while(size > 3) {
        aux = aux->esq;
        size--;
    }
    node argumentoB = aux->esq->dir;
    if(argumentoB->tipo == ARROBA)
        argumentoB = avaliarExpressao(argumentoB);

    node argumentoA = aux->esq->esq->dir;
    if(argumentoA->tipo == ARROBA)
        argumentoA = avaliarExpressao(argumentoA);

    int a = argumentoA->tipo;
    int b = argumentoB->tipo;
    node resultado = alocarNode(a*b);

    aux->esq = resultado;
}

void reduzDivisao(node grafo) {
    int size = tamanhoGrafo(grafo);
    node aux = grafo;
    while(size > 3) {
        aux = aux->esq;
        size--;
    }
    node argumentoB = aux->esq->dir;
    if(argumentoB->tipo == ARROBA)
        argumentoB = avaliarExpressao(argumentoB);

    node argumentoA = aux->esq->esq->dir;
    if(argumentoA->tipo == ARROBA)
        argumentoA = avaliarExpressao(argumentoA);

    int a = argumentoA->tipo;
    int b = argumentoB->tipo;
    if(b == 0) {
        printf("Divisao por zero!\n");
        exit(0);
    }

    node resultado = alocarNode(a/b);

    aux->esq = resultado;
}

void reduzTrue(node grafo) {
    int size = tamanhoGrafo(grafo);
    node aux = grafo;
    while(size > 3) {
        aux = aux->esq;
        size--;
    }
    node argumentoA = aux->esq->esq->dir;

    aux->esq = argumentoA;
}

void reduzFalse(node grafo) {
    int size = tamanhoGrafo(grafo);
    node aux = grafo;
    while(size > 3) {
        aux = aux->esq;
        size--;
    }
    node argumentoB = aux->esq->dir;

    aux->esq = argumentoB;
}

void reduzMenorQue(node grafo) {
    int size = tamanhoGrafo(grafo);
    node aux = grafo;
    while(size > 3) {
        aux = aux->esq;
        size--;
    }
    node argumentoB = aux->esq->dir;
    if(argumentoB->tipo == ARROBA)
        argumentoB = avaliarExpressao(argumentoB);

    node argumentoA = aux->esq->esq->dir;
    if(argumentoA->tipo == ARROBA)
        argumentoA = avaliarExpressao(argumentoA);

    int a = argumentoA->tipo;
    int b = argumentoB->tipo;

    if(a < b) aux->esq = tokens[-1*TRUE];
    else aux->esq = tokens[-1*FALSE];
}

void reduzMaiorQue(node grafo) {
    int size = tamanhoGrafo(grafo);
    node aux = grafo;
    while(size > 3) {
        aux = aux->esq;
        size--;
    }
    node argumentoB = aux->esq->dir;
    if(argumentoB->tipo == ARROBA)
        argumentoB = avaliarExpressao(argumentoB);

    node argumentoA = aux->esq->esq->dir;
    if(argumentoA->tipo == ARROBA)
        argumentoA = avaliarExpressao(argumentoA);

    int a = argumentoA->tipo;
    int b = argumentoB->tipo;

    if(a > b) aux->esq = tokens[-1*TRUE];
    else aux->esq = tokens[-1*FALSE];
}

void reduzIgualdade(node grafo) {
    int size = tamanhoGrafo(grafo);
    node aux = grafo;
    while(size > 3) {
        aux = aux->esq;
        size--;
    }
    node argumentoB = aux->esq->dir;
    if(argumentoB->tipo == ARROBA)
        argumentoB = avaliarExpressao(argumentoB);

    node argumentoA = aux->esq->esq->dir;
    if(argumentoA->tipo == ARROBA)
        argumentoA = avaliarExpressao(argumentoA);

    int a = argumentoA->tipo;
    int b = argumentoB->tipo;

    if(a == b) aux->esq = tokens[-1*TRUE];
    else aux->esq = tokens[-1*FALSE];
}


void reduzirGrafo(node grafo) {
    while(grafo->esq->tipo == ARROBA) {
        //printGrafo(grafo->esq);
        //printf("\n\n");
        int combinador = buscaCombinador(grafo);
        switch(combinador) {
            case K: reduzK(grafo);
                break;
            case S: reduzS(grafo);
                break;
            case I: reduzI(grafo);
                break;
            case B: reduzB(grafo);
                break;
            case C: reduzC(grafo);
                break;
            case D: reduzD(grafo);
                break;
            case E: reduzE(grafo);
                break;
            case F: reduzF(grafo);
                break;
            case Y: reduzY(grafo);
                break;
            case SOMA: reduzSoma(grafo);
                break;
            case SUBTRACAO: reduzSubtracao(grafo);
                break;
            case MULTIPLICACAO: reduzMultiplicacao(grafo);
                break;
            case DIVISAO: reduzDivisao(grafo);
                break;
            case MENORQUE: reduzMenorQue(grafo);
                break;
            case MAIORQUE: reduzMaiorQue(grafo);
                break;
            case IGUALDADE: reduzIgualdade(grafo);
                break;
            case TRUE: reduzTrue(grafo);
                break;
            case FALSE: reduzFalse(grafo);
                break;
            default:
                break;
        }
    }
}


#endif //PROJETO_DE_COMPILADORES_COMBINADORES_H
