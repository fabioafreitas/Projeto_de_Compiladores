 #include <stdio.h>
 #include <stdlib.h>
 #define N 1000 //alterar o tamanho deste DEFINE depois

//static char entrada[N] = "S(KK)(KS)(SK)KK(SK)K\0";
//static char entrada[N] = "SKKK\0";
//static char entrada[N] = "S(KK)KK(SK)\0";
static char entrada[N] = "S((SKKK)KK(SK(KS))KK\0";

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

void printGrafo (node r) {
   if (r != NULL) {
      printf ("%c", r->tipo);
      printGrafo (r->esq);
      printGrafo (r->dir); 
   }
}

//Procedimento que recebe duas variaveis, uma que aponta para
//um array e outra que aponta para um inteiro com a posicao do
//array a ser usada. O procedimento termina quando atinge a
//primeira posicao depois dos parenteses.
void casaParenteses(char* string, int* p) {
    int paren = 1;
    int c = *p;
    while (paren != 0) {
        char x = string[c];
        if(x == '(') {
            paren++;
            c++;
        }
        else if(x == ')') {
            paren--;
            c++;
        }
        else {
            c++;
        }
    }
    *p = c;
}

//Recebe a String a ser convertida, o index de inicio
//da string, e o index de onde a string termina.
//Converte esta string para grafo e
//retorna o node raiz do grafo gerado
node gerarGrafoAux(char* string, int indexAtual, int indexFinal) {
	node root = criarNode('R');
	
	// primeira folha
  if(string[indexAtual] == '(') {
    indexAtual++; 
    int inicio = indexAtual;
    casaParenteses(string, &indexAtual);
    int fim = indexAtual-1;
    node subgrafo = gerarGrafoAux(string, inicio, fim);

  } else {
    node combinador = criarNode(string[indexAtual++]);
    root->esq = combinador;
    combinador->esq = NULL;
  }
	
	while(indexAtual < indexFinal) {
		if(string[indexAtual] != '(') {
			node combinador = criarNode(string[indexAtual++]);
			node arroba = criarNode('@');
			arroba->dir = combinador;
			arroba->esq = root->esq;
			root->esq = arroba;
		}
		else {
			// proxima posição após o (
			indexAtual++; 
			
			 //posição de início da substring
			int inicio = indexAtual;
			
			/* Este comando irá buscar a próxima posição após ) do parenteses atual.
			o valor de indexAtual é alterado via ponteiro*/
			casaParenteses(string, &indexAtual);
			
			// para indicar exatamamente a posição do fecha parenteses
			int fim = indexAtual-1;
			
			/* cria um subgrafo com a string de dentro dos parenteses */
			node subgrafo = gerarGrafoAux(string, inicio, fim);
			
			node arroba = criarNode('@');
			arroba->dir = subgrafo->esq;
			arroba->esq = root->esq;
			root->esq = arroba;
		}
	}

	return root;
}

node gerarGrafo(char* string) {
	printf("teste");
	int lenght = 0;
	while(string[lenght] != '\0') 
		lenght++;
  	//printf("%i", lenght);
	return gerarGrafoAux(string, 0, lenght);
}

int main() {
	node root = gerarGrafo(entrada);
	printGrafo(root);
	printf("a");
  return 0;
}
