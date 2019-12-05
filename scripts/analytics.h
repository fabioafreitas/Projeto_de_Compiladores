//
// Created by fabio on 01/12/2019.
//

#ifndef PCOMPILADORES_ANALYTICS_H
#define PCOMPILADORES_ANALYTICS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct a {
    float chamadas;
    float tempo;
} data;

data obterDadosDeArquivo() {
    FILE* file = fopen("..\\scripts\\analytics.txt", "r");
    char string[25], chamadasSTR[10], timeSTR[10];
    fgets(string, 25, file);
    fgets(string, 25, file);
    fgets(string, 25, file);
    int i, j;
    for(i = 17, j = 0; string[i] != '\n' ; i++) {
        chamadasSTR[j++] = string[i];
    }
    chamadasSTR[j] = '\0';
    j=0;
    fgets(string, 25, file);
    for(i = 8, j = 0; i<13 ; i++) {
        timeSTR[j++] = string[i];
    }
    timeSTR[j] = '\0';
    data dados;
    dados.chamadas = strtof(chamadasSTR, NULL);
    dados.tempo = strtof(timeSTR, NULL);
    fclose(file);
    return dados;
}

void compilarConstruirAlgoritmo(int algoritmo) {
    FILE *file;
    if (file = fopen("..\\scripts\\analytics.txt", "r")){
        fclose(file);
        system("del ..\\scripts\\analytics.txt");
    }
    char compilar[100] = "@gcc ..\\garbage-collection";
    if(algoritmo == 1) strcat(compilar, "\\mark-scan");
    else if(algoritmo == 2) strcat(compilar, "\\fenichel-yochelson");
    else if(algoritmo == 3) strcat(compilar, "\\cheney");
    strcat(compilar, "\\main.c -o ..\\scripts\\main -O3");
    system(compilar);
    system("@..\\scripts\\main >> ..\\scripts\\analytics.txt");
}

/**
 * 1 = MarkScan
 * 2 = FenichelYochelson
 * 3 = Cheney
 */
 void analiseDesempenhoAlgoritmo(int algoritmo) {
    float tempoMedio = 0;
    int chamadas, i, iteracoes = 5;
    for(i=0;i<iteracoes;i++) {
        compilarConstruirAlgoritmo(algoritmo);
        data dados = obterDadosDeArquivo();
        tempoMedio += dados.tempo;
        chamadas = (int) dados.chamadas;
    }
    tempoMedio /= iteracoes;
    printf(" %f    %i",tempoMedio,chamadas);
}

#endif //PCOMPILADORES_ANALYTICS_H
