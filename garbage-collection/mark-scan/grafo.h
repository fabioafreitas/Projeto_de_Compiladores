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
#include "constantes.h"
#include "heap.h"





//só pode ser usada na geração do grafo
node atribuirToken(char tipo) {
    if(tipo < '0' || tipo > '9')
        return tokens[tipo];
    else
        return alocarNode(tipo-'0');
}

void imprime_arvore(node no){
    static int deph = 0;
    static int lista = 0;
    if(deph == 0 && no->tipo == -25)
        lista = 1;
    if(lista && no->tipo == -25)
        printf("[");
    if(no->esq) {
        deph++;
        imprime_arvore(no->esq);
    }
    switch (no->tipo){
        case -1:
            break;
        case ARROBA:
            printf("(");
            break;
        case S:
            printf("S");
            break;
        case K:
            printf("K");
            break;
        case I:
            printf("I");
            break;
        case B:
            printf("B");
            break;
        case C:
            printf("C");
            break;
        case D:
            printf("D");
            break;
        case E:
            printf("E");
            break;
        case F:
            printf("F");
            break;
        case TRUE:
            printf("TRUE");
            break;
        case FALSE:
            printf("FALSE");
            break;
        case MAIORQUE:
            printf(">");
            break;
        case MENORQUE:
            printf("<");
            break;
        case IGUALDADE:
            printf("==");
            break;
        case SOMA:
            printf("+");
            break;
        case SUBTRACAO:
            printf("-");
            break;
        case MULTIPLICACAO:
            printf("*");
            break;
        case DIVISAO:
            printf("/");
            break;
        case Y:
            printf("Y");
            break;
        default:
            printf("%u", no->tipo);
    }
    //printf("%d\n", no->tipo);
    if(no->dir) {
        deph++;
        if(no->dir != no) {
            imprime_arvore(no->dir);
            if (lista)
                printf("]");
            else
                printf(")");
        }else{
            printf("Y(");
            imprime_arvore(no->esq);
            printf(")");
            return;
        }
    }
    if(deph == 0)
        lista = 0;
}

//Exibe o grafo no console, escrito em preordem
void printGrafo (node r) {
    if (r != NULL) {
        int numero = 0;
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
            case ROOT: token = 'R'; break;
            default: numero = 1; break;
        }
        if(numero == 1) printf ("{%i}", r->tipo);
        else printf ("%c", token);
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

//Adiciona um parametro ao grafo
//Refebe o grafo e o parametro a ser adicionado
void adicionarParametro(node grafo, int param) {
    node arroba = alocarNode(ARROBA);
    arroba->dir = alocarNode(param);;
    arroba->esq = grafo->esq;
    grafo->esq = arroba;
}


//Recebe a String a ser convertida, o index de inicio
//da string, e o index de onde a string termina.
//Converte esta string para grafo e
//retorna o node raiz do grafo gerado
node gerarGrafoAux(char* string, int indexAtual, int indexFinal) {
    node root = alocarNode(ROOT);
    root->dir = NULL;

    // Folha a esquerda
    node token = atribuirToken(string[indexAtual++]);
    root->esq = token;

    // Folhas a direita
    while(indexAtual < indexFinal) {
        if(string[indexAtual] != '(') {
            node token = atribuirToken(string[indexAtual++]);
            node arroba = alocarNode(ARROBA);
            arroba->dir = token;
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
