//
// Created by fabio on 23/08/2019.
//
// Implementação das funcoes que
// convertem a string de combinadores
// num grafo
//

#ifndef PROJETO_DE_COMPILADORES_GRAFO_H
#define PROJETO_DE_COMPILADORES_GRAFO_H

#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

#define ARROBA -64
#define K -75
#define S -83
#define I -73
#define B -66
#define C -67
#define D -68
#define E -69
#define F -70
#define Y -89
#define SOMA -43
#define SUBTRACAO -45
#define MULTIPLICACAO -42
#define DIVISAO -47
#define TRUE -15
#define FALSE -16
#define MENORQUE -60
#define MAIORQUE -62
#define IGUALDADE -61
#define EMPTY -100 //Usado como Root do grafo, representa o espaco vazio ' '

static node tokens[256];

//Aloca os tokens que sao utilizados
//na construcao e reducao do grafo
//So eh necessaria uma unidade de cada,
//pois eles sao reutilizados, reduzindo
//o gasto de memoria da heap
void alocarTokens() {
    tokens[-1 * ARROBA] = alocarNode(ARROBA);
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

node atribuirToken(char tipo) {
    if(tipo < '0' || tipo > '9')
        return tokens[tipo];
    else
        return alocarNode(tipo-'0');
}

//Exibe o grafo no console, escrito em preordem
void printGrafo (node r) {
    if (r != NULL) {
        char token;
        switch (r->tipo) {
            case ARROBA: token = '@'; break;
            case K: token = 'K'; break;
            case S: token = 'S'; break;
            case I: token = 'I'; break;
            case B: token = 'B'; break;
            case C: token = 'C'; break;
            case D: token = 'D'; break;
            case E: token = 'E'; break;
            case F: token = 'F'; break;
            case Y: token = 'Y'; break;
            case SOMA: token = '+'; break;
            case SUBTRACAO: token = '-'; break;
            case MULTIPLICACAO: token = '*'; break;
            case DIVISAO: token = '/'; break;
            case MENORQUE: token = '<'; break;
            case MAIORQUE: token = '>'; break;
            case IGUALDADE: token = '='; break;
            default: token = '0'+r->tipo; break;
        }
        printf ("%c", token);
        printGrafo (r->esq);
        printGrafo (r->dir);
    }
}

//Procedimento que recebe duas variaveis, uma que aponta para
//um array e outra que aponta para um inteiro com a posicao do
//array a ser usada. O procedimento termina quando atinge a
//primeira posicao depois dos parenteses.
void casaParenteses(char* string, int* p) {
    int paren = 1;
    int c = *p;
    while (paren != 0) {
        char x = string[c];
        if(x == '(') {
            paren++;
            c++;
        }
        else if(x == ')') {
            paren--;
            c++;
        }
        else {
            c++;
        }
    }
    *p = c;
}

//Recebe uma string e um inteiro que armazena
//a posicao do ( parenteses a ser deletado.
//Reescreve a string, sem o abre parenteses
//do inteiro e seu fecha parenteses correspondente.
void removeParenteses(char* string, int index) {
    int i = ++index;
    casaParenteses(string, &index);
    for(; i < index-1 ; i++) {
        string[i-1] = string[i];
    }
    for(i = index ; string[i] != '\0' ; i++) {
        string[i-2] = string[i];
    }
    string[i-2] = '\0';
}

//Procedimento que remove redundancias (parenteses
//duplos) da string a ser convertida em grafo
void formatarString(char* string) {
    int i = 0, redundancia = 0;
    while(string[i] != '\0') {
        if(string[i] == '(' && string[i+1] == '(') redundancia = 1;
        if(redundancia) {
            removeParenteses(string, i+1);
            redundancia=0;
            i--;
        }
        i++;
    }
}



//Recebe a String a ser convertida, o index de inicio
//da string, e o index de onde a string termina.
//Converte esta string para grafo e
//retorna o node raiz do grafo gerado
node gerarGrafoAux(char* string, int indexAtual, int indexFinal) {
    node root = alocarNode(EMPTY);

    // Folha a esquerda
    node combinador = atribuirToken(string[indexAtual++]);
    root->esq = combinador;

    // Folhas a direita
    while(indexAtual < indexFinal) {
        if(string[indexAtual] != '(') {
            node combinador = atribuirToken(string[indexAtual++]);
            node arroba = alocarNode(ARROBA);
            arroba->dir = combinador;
            arroba->esq = root->esq;
            root->esq = arroba;
        }
        else {
            indexAtual++;
            int inicio = indexAtual;
            casaParenteses(string, &indexAtual);
            int fim = indexAtual-1;
            node subgrafo = gerarGrafoAux(string, inicio, fim);
            node arroba = alocarNode(ARROBA);
            arroba->dir = subgrafo->esq;
            arroba->esq = root->esq;
            root->esq = arroba;
        }
    }
    return root;
}

//Recebe a string a ser convertida em grafo
//e retorna o node raiz do grafo gerado
node gerarGrafo(char* string) {
    alocarTokens();
    int lenght = 0;
    while(string[lenght] != '\0')
        lenght++;
    return gerarGrafoAux(string, 0, lenght);
}

#endif //PROJETO_DE_COMPILADORES_GRAFO_H
