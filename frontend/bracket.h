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

int bracketMaisInterno(char* lambda);

//Retorna o index da variável do bracket mais interno
//XYZ++xyz -> retorna 9
int getUltimoBracket(char* lambda) {
	int i, answer = 0;
	int len = strlen(lambda);
    for(i = 0; i < len ; i++) {
        if(isupper(lambda[i])) answer = i;
    }
    return answer;
}

//Recebe um intervalo, uma string origem e uma string destino.
//Copia o conteudo da string origem no intervalo (inicio, final) dentro da string destino
void getSubString(char* stringOrigem, char* stringDestino, int inicio, int final) {
    int i, j = 0;
    for(i = inicio; i <= final ; i++) {
        stringDestino[j++] = stringOrigem[i];
    }
    stringDestino[j] = '\0';
}

//Copia a stringCopiar na StringInserir a partir do index de entrada
void inserirSubString(char* stringInserir, char* stringCopiar, int index) {
    int i, j = 0;
    char aux[strlen(stringInserir)];
    for (i = index; stringInserir[i] != '\0' ; i++) {
        aux[j++] = stringInserir[i];
    }
    aux[j] = '\0';
    for (i = index, j = 0; stringCopiar[j] != '\0'; i++) {
        stringInserir[i] = stringCopiar[j++];
    }
    for (j = 0; aux[j] != '\0' ; i++) {
        stringInserir[i] = aux[j++];
    }
}

//Conta a quantidade de argumentos de uma expressão lambda a partir de um index de entrada
int contarArgumentos(char* lambda, int index) {
    int numArgs = 0;
    while(lambda[index] != '\0' && lambda[index] != ')') {
        numArgs++;
        achaArgumento(lambda, &index);
    }
    return numArgs;
}

//Conta a quantidade de brackets a esquerda de uma expressao lambda
int contaBracketsAEsquerda(char* lambda) {
    int i = 0;
    int count = 0;
    while(isupper(lambda[i])) {
        count++;
        i++;
    }
    return count;
}

//Recebe uma expressao lambda que possui apenas 1 bracket a esquerda
//Recebe uma expressao lambda e a currifica
//X+xy -> X(+x)y
void currificar(char* lambda) {
    int numArgs = contarArgumentos(lambda, 1);
    if(numArgs > 2) {
        int i, indexUltimoArg = 1;
        for(i = 0 ; i < numArgs-1 ; i++) {
            achaArgumento(lambda, &indexUltimoArg);
        }
        inserirParenteses(lambda, 1, indexUltimoArg);
    }
}

//Recebe uma expressao lambda que possui apenas 1 bracket a esquerda
//Avalia se seus argumentos sao constantes em relacao ao bracket a esquerda
//Retorna 1 se os argumentos sao constantes e 0 caso nao sejam
int avaliarArgumentos(char* lambda) {
    char bracketLowerCase = tolower(lambda[0]);
    int i;
    for (i = 1; lambda[i] != '\0'; i++) {
        if(lambda[i] == bracketLowerCase)
            return 0;
    }
    return 1;
}

//Checa se a expressao esta reduzida, ou seja, se nao há mais brackets
int expressaoLambdaReduzida(char* lambda) {
    int i;
    for (i = 0; i < strlen(lambda); i++) {
        if(isupper(lambda[i])) return 0;
    }
    return 1;
}

void converterK(char* lambda) {
    inserirParenteses(lambda,1, strlen(lambda));
    lambda[0] = 'K';
}

void converterS(char* lambda) {
    //Buscando argumentos
    int A, nA, B, nB;
    int n = 1;
    A = n; achaArgumento(lambda, &n); nA = n-1;
    B = n; achaArgumento(lambda, &n); nB = n-1;

    //TODO
}

void converterI(char* lambda) {
    lambda[0] = 'I';
    lambda[1] = '\0';
}

//Recebe uma expressao lambda que possui apenas 1 bracket a esquerda
//Estou presumindo que a entrada ja esta no formado de entrada, nao faço validaçoes
void bracketCasoBase(char* lambda) {
    int numeroArgumentos = contarArgumentos(lambda, 1);
    if(numeroArgumentos > 2) {
        currificar(lambda);
    }

    if(strlen(lambda)==2) {
        converterI(lambda);
        return;
    }

    int argumentosConstantes = avaliarArgumentos(lambda);
    if(argumentosConstantes)
        converterK(lambda);
    else
        converterS(lambda);
}

//Converte a expressao lambda do parametro para uma expressao e logica combinatorial
void bracket(char* lambda) {
    //checo se a expressao ja esta reduzida
    if(expressaoLambdaReduzida(lambda)) {
        return;
    }

    //Checo se a expressao esta no caso base (Apenas um bracket a esquerda)
    int numeroBracketsEsquerda = contaBracketsAEsquerda(lambda);
    if(numeroBracketsEsquerda == 1) {
        bracketCasoBase(lambda);
        return;
    }

    //Expressao com muitos brackets a esquerda
    char lambdaAux[SIZE];
    int ultimoBracket = getUltimoBracket(lambda);           // Index do bracket mais interno
    int final = strlen(lambda) - 1;                         // Index do ultimo character da expressao lambda
    getSubString(lambda, lambdaAux, ultimoBracket, final);  // Copiando a expressao do caso base em lambdaAux

    bracket(lambdaAux);                                     // Chamada recursiva para resolver a expressao mais interna
    int penultimoBracket = ultimoBracket-1;                 // Index do bracket anterior ao mais interno
    inserirSubString(lambda, lambdaAux, penultimoBracket);  // Copiando lambdaAux de volta na expressoa lambda
    bracket(lambda);                                        // Chamada recursiva para resolver o restante da expressao

    //TODO a ideia é que essa ultima chamada recursiva esbarre no PRIMEIRO IF quando todos os brackets forem resolvidos
}
#endif //PCOMPILADORES_BRACKET_H