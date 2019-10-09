#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "heap.h"
#include "grafo.h"
#include "combinadores.h"
#include "constantes.h"

//static char fab1[N] = "S(K(SII))(S(S(KS)K)(K(SII)))(S(K(S(S(S(S(K=)I)(K0))(K1))))(S(K(S(S(K+)I)))(S(S(KS)(S(KK)I))(K(S(S(K-)I)(K1))))))\0";
//static char fab2[N] = "Y(ES(C(F=I0)1)(E(D+)I(FBI(F-I1))))\0";
//static char fib1[N] = "S(K(SII))(S(S(KS)K)(K(SII)))(S(K(S(S(S(KI)(S(S(K<)I)(K2)))I)))(S(S(KS)(S(K(S(K+)))(S(S(KS)(S(KK)I))(K(S(S(K-)I)(K2))))))(S(S(KS)(S(KK)I))(K(S(S(K-)I)(K1))))))\0";
static char fib2[N] = "Y(ES(S(F<I2)I)(D(D+)(FBI(F-I2))(FBI(F-I1))))\0";

int main(int n, char* args[]) {
    inicializarHeap(10000);
    rootGrafo = gerarGrafo(fib2);
    adicionarParametro(16);

    printf("\n# MarkScan #");
    reduzirGrafo(0);
    printf("\nTempo = %.10lf", (clock()/(float)CLOCKS_PER_SEC));
    printf("\nResultado = ");
    printGrafoPosfixo(rootGrafo->esq);
    printf("\n");
    return 0;
}
