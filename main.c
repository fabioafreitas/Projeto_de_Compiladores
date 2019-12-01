#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include "frontend/bracket.h"
#include "scripts/analytics.h"

static char lambda[100] = "Y+xy\0";
static char lambda2[100] = "XY+xff(+yy)\0";
static char teste[100] = "SKKK\0";


int main(int n, char* args[]) {
    //1 = MarkScan
    //2 = FenichelYochelson
    //3 = Cheney
    analiseDesempenhoAlgoritmo(3);
    return 0;
}