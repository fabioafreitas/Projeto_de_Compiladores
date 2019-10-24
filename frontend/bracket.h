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

//Procedimento que recebe duas variaveis, uma que aponta para
//um array e outra que aponta para um inteiro com a posicao do
//array a ser usada. O procedimento termina quando atinge a
//primeira posicao depois dos parenteses.
void casa_parenteses(char* string, int* p) {
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
void remove_parenteses(char* string, int index) {
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

/**
 * [x](ab) => S([x]a)([x]b)
 * [x]y    => Ky, se o x != y
 * [x]x    => I
 *
 */
//Esta funcao recebe uma string de uma expressao lambda
//e a converte para uma string de uma expressao em logica
//combinatorial de turner (SKIBCDEFY)
char* converterExpressaoLambda(char* lambda) {

}
#endif //PCOMPILADORES_BRACKET_H

/**
 * [a] ([b] ([c] ac (bc)))
 * [a] ([b] ( S ([c]ac) ([c]bc) ))
 * [a] ([b] ( S ( S([c]a)([c]c) ) ( S([c]b)([c]c) ) ))
 * [a] ([b] (S(S(Ka)(I))(S(Kb)(I))) )
 * [a] ([b] S (S(Ka)(I)) (S(Kb)(I)) )
 * [a] ( S ([b] S (S(Ka)I)) ([b] S(Kb)I ) )
 *
 */
