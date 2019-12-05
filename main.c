#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "frontend/main.c"


static char aux[100] = "Yxxx\0";
int main(int n, char* args[]) {

    printf("%s", aux);
    inserirParenteses(aux,1, strlen(aux) );
    printf("\n%s", aux);
    return 0;
}