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
#include "constantes.h"
#include "heap.h"

//Cabecalho para permitir que os combinadores chamem a funcao reduzirGrafo
node reduzirGrafo(int chamadaRecursiva);

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


//Retorna um ponteiro, cujos elementos abaixo dele
//são todos os argumentos da respectiva reduçãp
//Recebe o grafo atual e a quantidade de elementos
//desta redução
node posicionarPonteiro(node grafo, int numArgs) {
    int size = tamanhoGrafo(grafo);
    node aux = grafo;
    while(size > numArgs+1) {
        aux = aux->esq;
        size--;
    }
    return aux;
}

//K a b = a
void reduzK(node grafo) {
    node aux = posicionarPonteiro(grafo, 2);
    aux->esq = aux->esq->esq->dir; //argumento A
}

//S a b c = a c ( b c )
void reduzS(node grafo) {
    node aux = posicionarPonteiro(grafo, 3);
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
    node aux = posicionarPonteiro(grafo, 1);
    aux->esq = aux->esq->dir; //argumento A
}

//B a b c = a ( b c )
void reduzB(node grafo) {
    node aux = posicionarPonteiro(grafo, 3);
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
    node aux = posicionarPonteiro(grafo, 3);
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
    node aux = posicionarPonteiro(grafo, 4);
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
    node aux = posicionarPonteiro(grafo, 4);
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
    node aux = posicionarPonteiro(grafo, 4);
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

//Y a = a ( Y a )
void reduzY(node grafo) {
    node aux = posicionarPonteiro(grafo, 1);
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
    node aux = posicionarPonteiro(grafo, 1);
    node arroba1 = alocarNode(ARROBA);
    arroba1->esq = aux->esq->dir;
    arroba1->dir = arroba1;

    aux->esq = arroba1;
}

/*##########  OPERADORES ARITIMÉTICOS E LÓGICOS #########*/

node avaliarExpressao(node argumento);

//Recebe o ponteiro do grafo, já posiciona acima dos
//argumentos da redução e dois ponteiros para atribuir
//os valores dos argumentos (ja avaliados)
//Retorna 1, caso a atribuição ocorra com sucesso
//Retorna 0, caso ocorra uma chamada ao garbage collection
int atribuirArgumentos(node aux, int* argA, int* argB) {
    node argumentoB = aux->esq->dir;
    if(argumentoB->tipo == ARROBA) {
        argumentoB = avaliarExpressao(argumentoB);
        aux->esq->dir = argumentoB;
    }

    node argumentoA = aux->esq->esq->dir;
    if(argumentoA->tipo == ARROBA) {
        argumentoA = avaliarExpressao(argumentoA);
        aux->esq->esq->dir = argumentoA;
    }

    //Caso verdade, significa que a freelist esta quase vazia
    if(argumentoB->tipo == ARROBA || argumentoA->tipo == ARROBA) {
        return 0;
    }

    //Significa que as avaliações ocorreram com sucesso
    aux->esq->dir = argumentoB;
    aux->esq->esq->dir = argumentoA;

    *argA = argumentoA->tipo;
    *argB = argumentoB->tipo;
    return 1;
}

//SOMA a b = eval(a) + eval(b)
void reduzSoma(node grafo) {
    node aux = posicionarPonteiro(grafo, 2);

    int a, b;
    int chamadaRecursiva = atribuirArgumentos(aux, &a, &b);
    if(chamadaRecursiva == 0) return;

    node resultado = alocarNode(a+b);

    aux->esq = resultado;
}

//SUBTRACAO a b = eval(a) - eval(b)
void reduzSubtracao(node grafo) {
    node aux = posicionarPonteiro(grafo, 2);

    int a, b;
    int chamadaRecursiva = atribuirArgumentos(aux, &a, &b);
    if(chamadaRecursiva == 0) return;

    node resultado = alocarNode(a-b);

    aux->esq = resultado;
}

//MULTIPLICACAO a b = eval(a) * eval(b)
void reduzMultiplicacao(node grafo) {
    node aux = posicionarPonteiro(grafo, 2);

    int a, b;
    int chamadaRecursiva = atribuirArgumentos(aux, &a, &b);
    if(chamadaRecursiva == 0) return;

    node resultado = alocarNode(a*b);

    aux->esq = resultado;
}

//DIVISAO a b = eval(a) / eval(b)
void reduzDivisao(node grafo) {
    node aux = posicionarPonteiro(grafo, 2);

    int a, b;
    int chamadaRecursiva = atribuirArgumentos(aux, &a, &b);
    if(chamadaRecursiva == 0)  return;

    if(b == 0) {
        printf("\n# Divisao por zero #\n");
        exit(0);
    }

    node resultado = alocarNode(a/b);

    aux->esq = resultado;
}

//TRUE a b = a
void reduzTrue(node grafo) {
    node aux = posicionarPonteiro(grafo, 2);
    node argumentoA = aux->esq->esq->dir;

    aux->esq = argumentoA;
}

//FALSE a b = B
void reduzFalse(node grafo) {
    node aux = posicionarPonteiro(grafo, 2);
    node argumentoB = aux->esq->dir;

    aux->esq = argumentoB;
}

//MENORQUE a b = (a < b)? TRUE : FALSE
void reduzMenorQue(node grafo) {
    node aux = posicionarPonteiro(grafo, 2);

    int a, b;
    int chamadaRecursiva = atribuirArgumentos(aux, &a, &b);
    if(chamadaRecursiva == 0) return;

    if(a < b) aux->esq = tokens[-1*TRUE];
    else aux->esq = tokens[-1*FALSE];
}

//MAIORQUE a b = (a > b)? TRUE : FALSE
void reduzMaiorQue(node grafo) {
    node aux = posicionarPonteiro(grafo, 2);

    int a, b;
    int chamadaRecursiva = atribuirArgumentos(aux, &a, &b);
    if(chamadaRecursiva == 0) return;

    if(a > b) aux->esq = tokens[-1*TRUE];
    else aux->esq = tokens[-1*FALSE];
}

//IGUALGADE a b = (a == b)? TRUE : FALSE
void reduzIgualdade(node grafo) {
    node aux = posicionarPonteiro(grafo, 2);
    node argumentoB = aux->esq->dir;

    int a, b;
    int chamadaRecursiva = atribuirArgumentos(aux, &a, &b);
    if(chamadaRecursiva == 0) return;

    if(a == b) aux->esq = tokens[-1*TRUE];
    else aux->esq = tokens[-1*FALSE];
}

node avaliarExpressao(node argumento) {
    node subgrafo = alocarNode(ROOT);
    //Avaliando Expressao
    subgrafo->esq = argumento;
    node aux = rootGrafo;
    rootGrafo = subgrafo;
    reduzirGrafo(1);
    node res = rootGrafo->esq;
    rootGrafo = aux;
    return res;
}



//Este procedimento recebe um grafo
//e retorna sua forma irredutível
node reduzirGrafo(int chamadaRecursiva) {
    int callsGC = 0;
    float porcentagem = 10;
    int euristica = H * (porcentagem/100);

    /*Variaveis que armazenam o tamanho da freelist
    antes e depois da ultima chamada do GC*/
    int freelistAntesLastCall = 0;
    int freelistDepoisLastCall = 0;

    while(rootGrafo->esq->tipo == ARROBA) {
        int combinador = buscaCombinador(rootGrafo);
        if( sizeFreeList <= euristica ) {
            if(chamadaRecursiva) {
                break;
            } else {
                callsGC++;
                /*printGrafoInfixo(rootGrafo->esq);
                printf("\n# MarkScan %i #\n",callsGC);*/
                int freelistAntesCurrentCall = sizeFreeList;
                markScan();
                int freelistDepoisCurrentCall = sizeFreeList;

                /*Caso o tamanho da freelist antes e depois
                da chamada anterior e da atual sejam iguais respectivamente
                entao significa que a heap eh muito pequena para esta reducao*/
                if( freelistAntesLastCall == freelistAntesCurrentCall &&
                    freelistDepoisLastCall == freelistDepoisCurrentCall) {
                    printf("\nErro: HEAP cheia, GB nao consegue liberar mais memoria.\n");
                    exit(0);
                }
                freelistAntesLastCall = freelistAntesCurrentCall;
                freelistDepoisLastCall = freelistDepoisCurrentCall;
            }
        }

        switch(combinador) {
            case K: reduzK(rootGrafo); break;
            case S: reduzS(rootGrafo); break;
            case I: reduzI(rootGrafo); break;
            case B: reduzB(rootGrafo); break;
            case C: reduzC(rootGrafo); break;
            case D: reduzD(rootGrafo); break;
            case E: reduzE(rootGrafo); break;
            case F: reduzF(rootGrafo); break;
            case Y: reduzY2(rootGrafo); break;
            case SOMA: reduzSoma(rootGrafo); break;
            case SUBTRACAO: reduzSubtracao(rootGrafo); break;
            case MULTIPLICACAO: reduzMultiplicacao(rootGrafo); break;
            case DIVISAO: reduzDivisao(rootGrafo); break;
            case MENORQUE: reduzMenorQue(rootGrafo); break;
            case MAIORQUE: reduzMaiorQue(rootGrafo); break;
            case IGUALDADE: reduzIgualdade(rootGrafo); break;
            case TRUE: reduzTrue(rootGrafo); break;
            case FALSE: reduzFalse(rootGrafo); break;
            default: break;
        }
    }

    if(chamadaRecursiva == 0) {
        printf("\nChamadas do GC = %i", callsGC);
    }

    return rootGrafo->esq;
}


#endif //PROJETO_DE_COMPILADORES_COMBINADORES_H
