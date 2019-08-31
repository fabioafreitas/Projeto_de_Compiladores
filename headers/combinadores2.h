//
// Created by fabio on 30/08/2019.
//
// A lista encadeada armazena o caminho
// de church rosser II. Desta forma, só é necessário
// montar o caminho uma vez, sendo possível navegar
// pela lista e encontrar os argumentos dos combinadores
// de forma mais eficiente. Após alguma redução, é necessário
// adicionar o novo pedaço do caminho à lista.
//

#ifndef PCOMPILADORES_COMBINADORES2_H
#define PCOMPILADORES_COMBINADORES2_H

#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

//lista encadeada que armazena o caminho de church rosser II
struct li {
    node conteudo;
    struct li* prox;
};

typedef struct li* list;

list criarLista() {
    list novaLista = (list) malloc(sizeof(list));
    novaLista->prox = NULL;
    return novaLista;
}

void printLista(list lista) {
    list aux = lista;
    while(aux->prox != NULL) {
        printf("%c", aux->prox->conteudo->tipo);
        aux = aux->prox;
    }
}

// Monta o caminho de church rosser II a partir de algum
// ponto da lista e a partir de algum ponto do grafo
// Desta forma, essa função pode tanto criar o primeiro
// caminho CH II quanto atualizar alguma parte do caminho
list montarCaminhoCH(node grafo) {
    list lista = criarLista();
    node aux = grafo;
    while(aux != NULL) {
        list nova = criarLista();
        nova->conteudo = aux;
        nova->prox = lista->prox;
        lista->prox = nova;
        aux = aux->esq;
    }
    return lista;
}

//TODO completar este combinador
void reduzK2(list caminho) {
    //Aplicando a redução ao grafo
    caminho->prox->prox->prox->prox->conteudo->esq = caminho->prox->prox->conteudo->dir;

    //Indicando que agora os @ são nodes Livres TODO
    caminho->prox->conteudo->status = 'L';
    caminho->prox->prox->conteudo->status = 'L';

    //Atualizando o caminho de CH2 TODO
    list aux = montarCaminhoCH(caminho->prox->prox->conteudo->dir);
    aux->prox = caminho->prox->prox->prox->prox;
    caminho->prox = aux->prox;

    printf("a");
}

void reduzS2(list caminho) {
    node arroba1 = alocarNode('@');
    node arroba2 = alocarNode('@');
    node arroba3 = alocarNode('@');

    arroba1->esq = arroba2;
    arroba1->dir = arroba3;

    arroba2->esq = caminho->prox->prox->conteudo->dir; //Argumento A
    arroba2->dir = caminho->prox->prox->prox->prox->conteudo->dir; //Argumento C

    arroba3->esq = caminho->prox->prox->prox->conteudo->dir; //Argumento B
    arroba3->dir = caminho->prox->prox->prox->prox->conteudo->dir; //Argumento B

    //Aplicando a redução ao grafo
    caminho->prox->prox->prox->prox->prox->conteudo->esq = arroba1;

    //Indicando que agora os @ são nodes Livres
    caminho->prox->conteudo->status = 'L';
    caminho->prox->prox->conteudo->status = 'L';
    caminho->prox->prox->prox->conteudo->status = 'L';

    //Atualizando o caminho de CH2
    list aux = montarCaminhoCH(arroba1);
    aux->prox->prox->prox->prox = caminho->prox->prox->prox->prox->prox;
    caminho->prox = aux->prox;
}

void reduzirGrafo2(node grafo) {
    list caminho = montarCaminhoCH(grafo); //Caminho de Church Rosser 2
    while(caminho->prox->prox != NULL) {
        char combinador = caminho->prox->conteudo->tipo;
        switch(combinador) {
            case 'K':
                reduzK2(caminho);
                break;
            case 'S':
                reduzS2(caminho);
                break;
                /* case 'I': reduzI(grafo);
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
                     break;*/
            default:
                break;
        }
        //TODO checar se é necessário fazer "caminho->prox = caminho->prox->prox"
    }
}


#endif //PCOMPILADORES_COMBINADORES2_H
