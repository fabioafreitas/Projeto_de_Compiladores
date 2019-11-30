#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include "frontend/bracket.h"
#include "garbage-collection/cheney/main.c"

static char lambda[100] = "Y+xy\0";
static char lambda2[100] = "XY+xff(+yy)\0";
static char teste[100] = "SKKK\0";


int main(int n, char* args[]) {
    //run(); /*
    rootGrafo = gerarGrafo(teste); cheney(); //*/
    printGrafoPosfixo(rootGrafo->esq);
    return 0;
}