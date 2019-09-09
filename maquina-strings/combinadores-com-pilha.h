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
// INFELIZMENTE NAO É EFICIENTE ;-;

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

//Retorna a ultima celula da lista encadeada
//funcao utilizada durante a reducao do grafo
list ultimoElementoLista(list lista) {
    list aux = lista;
    while(aux->prox != NULL) {
        aux = aux->prox;
    }
    return aux;
}

void reduzK2(list caminho) {
    //Indicando que agora os @ são nodes Livres
    caminho->prox->prox->conteudo->status = 'L';
    caminho->prox->prox->prox->conteudo->status = 'L';

    node argumentoA = caminho->prox->prox->conteudo->dir;

    //Aplicando a redução ao grafo
    caminho->prox->prox->prox->prox->conteudo->esq = argumentoA;

    //Atualizando o caminho de CH2
    caminho->prox->conteudo = argumentoA;
    caminho->prox->prox = caminho->prox->prox->prox->prox;
}

void reduzS2(list caminho) {
    node arroba1 = alocarNode('@');
    node arroba2 = alocarNode('@');
    node arroba3 = alocarNode('@');

    arroba1->esq = arroba2;
    arroba1->dir = arroba3;

    node argumentoA = caminho->prox->prox->conteudo->dir;
    node argumentoB = caminho->prox->prox->prox->conteudo->dir;
    node argumentoC = caminho->prox->prox->prox->prox->conteudo->dir;

    arroba2->esq = argumentoA;
    arroba2->dir = argumentoC;

    arroba3->esq = argumentoB;
    arroba3->dir = argumentoC;

    //Indicando que agora os @ são nodes Livres
    caminho->prox->prox->conteudo->status = 'L';
    caminho->prox->prox->prox->conteudo->status = 'L';
    caminho->prox->prox->prox->prox->conteudo->status = 'L';

    //Aplicando a redução ao grafo
    caminho->prox->prox->prox->prox->prox->conteudo->esq = arroba1;

    //Atualizando o caminho de CH2
    list caminhoReducao = montarCaminhoCH(arroba1); //Caminho CH2 da redução do grafo
    list ultimoElemento = ultimoElementoLista(caminhoReducao); //ultimo elemento do caminhoNovo
    ultimoElemento->prox = caminho->prox->prox->prox->prox->prox;
    caminho->prox = caminhoReducao->prox;
}

void reduzirGrafo2(node grafo) {
    list caminho = montarCaminhoCH(grafo); //Caminho de Church Rosser 2
    while(caminho->prox->prox->prox != NULL) {
        char combinador = caminho->prox->conteudo->tipo;
        switch(combinador) {
            case 'K':
                reduzK2(caminho);
                break;
            case 'S':
                reduzS2(caminho);
                break;
            default:
                break;
        }
    }
}


#endif //PCOMPILADORES_COMBINADORES2_H
