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

static node combinadores[26];

//Aloca os combinadores que sao utilizados
//na construcao e reducao do grafo
//So eh necessaria uma unidade de cada,
//pois eles sao reutilizados, reduzindo
//o gasto de memoria da heap
void alocarCombinadores() {
    combinadores['S'-65] = alocarNode('S');
    combinadores['K'-65] = alocarNode('K');
    combinadores['I'-65] = alocarNode('I');
    combinadores['B'-65] = alocarNode('B');
    combinadores['C'-65] = alocarNode('C');
    combinadores['D'-65] = alocarNode('D');
    combinadores['E'-65] = alocarNode('E');
    combinadores['F'-65] = alocarNode('F');
}

node atribuirCombinador(char combinador) {
    return combinadores[combinador-65];
}

//Exibe o grafo no console, escrito em preordem
void printGrafo (node r) {
    if (r != NULL) {
        printf ("%c", r->tipo);
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
    node root = alocarNode(' ');

    // Folha a esquerda
    node combinador = atribuirCombinador(string[indexAtual++]);
    root->esq = combinador;

    // Folhas a direita
    while(indexAtual < indexFinal) {
        if(string[indexAtual] != '(') {
            node combinador = atribuirCombinador(string[indexAtual++]);
            node arroba = alocarNode('@');
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
            node arroba = alocarNode('@');
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
    alocarCombinadores();
    int lenght = 0;
    while(string[lenght] != '\0')
        lenght++;
    return gerarGrafoAux(string, 0, lenght);
}

#endif //PROJETO_DE_COMPILADORES_GRAFO_H
