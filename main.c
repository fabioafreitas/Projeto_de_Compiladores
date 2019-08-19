 #include <stdio.h>
 #include <stdlib.h>
 #define N 100000000

//static char entrada[N] = "S(K(K))(KS)(SK)KK(SK)K\0";
static char entrada[N] = "SKKK\0";

// Estrutura de um noh da memoria
typedef struct reg {
    char tipo;
    char status;
    struct reg *dir;
    struct reg *esq;
} noh;

typedef noh* node; 

node criarNode(char tipo) {
	node novo = (node) malloc(sizeof(node));
	novo->esq = novo->dir = NULL;
	novo->tipo = tipo;
	return novo;
} 

//
void erd (node r) {
   if (r != NULL) {
      erd (r->esq);
      printf ("%c", r->tipo);
      erd (r->dir); 
   }
}

void printGrafo (node r) {
   if (r != NULL) {
      printf ("%c", r->tipo);
      printGrafo (r->esq);
      printGrafo (r->dir); 
   }
}

// retorna a raiz do grafo gerado
// por hora este método só gera grafos
// de strings simples (sem parenteses)
node gerarGrafo(char* string, int index) {
	node root = criarNode(' ');
	static int casoBase = 1;
	int i = index;
	
	//caso base
	node combinador = criarNode(string[i++]);
	root->esq = combinador;
	combinador->esq = NULL;
	
	while(string[i] != '\0') {
		node arroba = criarNode('@');
		node combinador2 = criarNode(string[i++]);
		arroba->dir = combinador2;

		arroba->esq = root->esq;
		root->esq = arroba;
	}

	return root;
}

int main(int num, char *args[]) {
	/*node root = criarNode(' ');
	node nc = criarNode('@');
	node nb = criarNode('@');
	node na = criarNode('@');
	node c = criarNode('K');
	node b = criarNode('K');
	node a = criarNode('K');
	node s = criarNode('S');
	
	root->esq = nc;
	nc->esq = nb;
	nb->esq = na;
	na->esq = s;
	
	nc->dir = c;
	nb->dir = b;
	na->dir = a;
	printGrafo(root);
	printf("\n");*/
	
	node r = gerarGrafo(entrada, 0);
	printGrafo(r);
	
	return 0;
}
