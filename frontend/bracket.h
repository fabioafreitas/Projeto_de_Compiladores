//
// Created by fabio on 23/10/2019.
//
// Neste arquivo tem a implementacao
// do algoritmo que converte uma lambda
// expressao em logica combinatorial
//
// http://www.cantab.net/users/antoni.diller/brackets/intro.html

#ifndef PCOMPILADORES_BRACKET_H
#define PCOMPILADORES_BRACKET_H

#include <string.h>
#include <ctype.h>

#define SIZE 1000000
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

//Coloca a string de entrada entre parenteses
//Adiciona um abre parenteses em inicio-1
//Adiciona um fecha parenteses em fim+1
//XY+xy,0,4 -> (XY+xy)
void inserirParenteses(char* string, int inicio, int fim) {
    char array[strlen(string)+3];
    strcpy(array, string);
    int i, j = 0;
    for(i = 0; i < inicio ; i++) {
        array[j++] = string[i];
    }
    array[j++] = '(';
    for(i = inicio; i < fim ; i++) {
        array[j++] = string[i];
    }
    array[j++] = ')';
    for(i = fim; string[i] != '\0'; i++) {
        array[j++] = string[i];
    }
    array[j++] = '\0';
    strcpy(string, array);
}

void achaArgumento(char* array1, int* p) {
    int c = *p;
    if (array1[c] == '(') {
        c++;
        casaParenteses(array1,&c);
    } else {
        c++;
    }
    *p = c;
}

//Retorna o index da variável do bracket mais interno
//[x]([y]([z]((+x)((+y)z)))) -> retorna 9
int buscarBracketMaisInterno(char* lambda) {
	int i, answer = 0;
	int len = strlen(lambda);
    for(i = 0; i < len ; i++) {
        if(isupper(lambda[i])) answer = i;
    }
    return answer;
}

//Conta a quantidade de argumentos de uma expressão lambda a partir de um index de entrada
int contaArgumentos(char* lambda, int index) {
    int numArgs = 0;
    while(lambda[index] != '\0' && lambda[index] != ')') {
        numArgs++;
        achaArgumento(lambda, &index);
    }
    return numArgs;
}

//faz uma cópia da stringOrigem na stringDestino a partir de um intervalo inicio e fim
void copiarSubstring(char* stringOrigem, char* stringDestino, int inicio, int final) {
    int i, j = 0;
    for(i = inicio; i <= final ; i++) {
        stringDestino[j++] = stringOrigem[i];
    }
    stringDestino[j] = '\0';
}

//Currifica os argumentos de uma expressão lambda
//Y+xy -> Y(+x)y
//Abcde -> A(bcd)e
void currificarExpressaoLambda(char* lambda) {
    int numArgs = contaArgumentos(lambda, 1);
    int i, indexUltimoArg = 1;
    for(i = 0 ; i < numArgs-1 ; i++) {
        achaArgumento(lambda, &indexUltimoArg);
    }
    inserirParenteses(lambda, 1, indexUltimoArg);
}

void bracketAbstractionAlgorithm(char* lambda) {

    //Preprocessando e currificando
    char stringAux[SIZE];
    int bracketMaisInterno =  buscarBracketMaisInterno(lambda);
    int finalStringLambda;
    finalStringLambda = strlen(lambda) - 1;
    copiarSubstring(lambda, stringAux, bracketMaisInterno, finalStringLambda);
    int numArgs = contaArgumentos(stringAux, 1);
    if(numArgs > 2) {
        currificarExpressaoLambda(stringAux);
    }

    //Buscando argumentos
    int A, nA, B, nB;
    int n = 1;
    A = n;
    achaArgumento(stringAux, &n);
    nA = n-1;
    B = n;
    achaArgumento(stringAux, &n);
    nB = n-1;

    //Convertendo esta expressão

    if(A == nA) {

    }
}
#endif //PCOMPILADORES_BRACKET_H

//XY+xy         busco o bracket mais interno
//XY+xy         checo a quantidade de argumentos. se mais de 2, currifico
//XY(+x)y




//XY(+x)y
//XS(Y+x)(Yy)
//XS(Y+x)(Yy)
//XS(Y+x)(Yy)
//XS()()
