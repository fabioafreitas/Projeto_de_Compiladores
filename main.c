#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "frontend/main.c"


static char aux[100] = "Y+xz\0";
int main(int n, char* args[]) {

    printf("%s", aux);
    currificar(aux);
    converterK(aux);
    printf("\n%s", aux);
    return 0;
}