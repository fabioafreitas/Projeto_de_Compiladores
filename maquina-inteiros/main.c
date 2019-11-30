#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "heap.h"
#include "grafo.h"
#include "combinadores.h"


#define N 10000000  //Tamanho da String

static char fab1[N] = "S(K(SII))(S(S(KS)K)(K(SII)))(S(K(S(S(S(S(K=)I)(K0))(K1))))(S(K(S(S(K+)I)))(S(S(KS)(S(KK)I))(K(S(S(K-)I)(K1))))))\0";
static char fab2[N] = "Y(ES(C(F=I0)1)(E(D+)I(FBI(F-I1))))\0";
static char fib1[N] = "S(K(SII))(S(S(KS)K)(K(SII)))(S(K(S(S(S(KI)(S(S(K<)I)(K2)))I)))(S(S(KS)(S(K(S(K+)))(S(S(KS)(S(KK)I))(K(S(S(K-)I)(K2))))))(S(S(KS)(S(KK)I))(K(S(S(K-)I)(K1))))))\0";
static char fib2[N] = "Y(ES(S(F<I2)I)(D(D+)(FBI(F-I2))(FBI(F-I1))))\0";
static char succ1[N] = "S(S(K+)I)(K1)\0";
static char succ2[N] = "\0";
static char succ3[N] = "\0";
static char soma1[N] = "S(S(KS)(S(S(KS)(S(KK)(K+)))(S(KK)(K+)))(KI)\0";
static char soma2[N] = "S(S(KS)(S(S(KS)(S(KK)(K+)))(S(KK)I)))(KI)\0";
static char soma3[N] = "C(BB(CI+))I\0";


int main(int n, char* args[]) {
    inicializarHeap();
    rootGrafo = gerarGrafo(soma2);
    adicionarParametro(rootGrafo,  1);
    adicionarParametro(rootGrafo,  2);
//    adicionarParametro(rootGrafo,  3);
    reduzirGrafo(rootGrafo);
    printf("\nTempo = %.15lf", (clock()/(float)CLOCKS_PER_SEC));
    printf("\nResultado = ");
    printGrafoPosfixo(rootGrafo->esq);
    printf("\n");
    return 0;
}
