%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bracket.h"
#include "../backend/cheney/cheney.h"


typedef struct func {
    char* name;
    char* expr;
}function;

static function table[100];
static int funcCounter = 0;

extern int yylex();
void yyerror(char *msg);
float calc(float a, char c, float b);
void bracket(char *fun, char *str, char *valor);
void func_call(char* str);

int searchParethesis(char* expr, int* ap, int* fp);
void removeBrackets(char* expr);
void storeFunction(char* name, char* expr);
int countIntDigits(int num);
char* convertIntToString(int number);
void printFunctions();
int functionCall(char* expr);


%}


%union{
	int dval;
	char op;
	char str[150];
}

%token <str> NAME
%token <str> NUMBER
%token <op> OPERATOR
%token EOL AP FP ASSIGN SUM MIN TIMES DIV IF THEN ELSE GT LT

%type <str> expr
%type <str> condition
%type <str> factor
%type <str> term
%type <str> FUNC_CALL

%%

PROGRAM : STATEMENT {;}
	;

STATEMENT : STATEMENT STATEMENT
	| DECLARATION {;}
	| FUNC_CALL {
				// printf("%s", $1);
				func_call($1);
				}
	| EOL {;}
	;

DECLARATION : FUNC_ASSIGN_VAR {;}
	;

FUNC_CALL : NAME AP expr FP {
		char r[150] = "";
		char b[2] = "\0";
		char ap[2] = "(";
		char fp[2] = ")";
		//strcat(r, ap);
		strcat(r, $1);
		strcat(r, ap);
		strcat(r, $3);
		strcat(r, fp);
		//strcat(r, fp);
		strcpy($$, r);
		}
	| NAME AP FUNC_CALL FP {
		char r[150] = "";
		char b[2] = "\0";
		char ap[2] = "(";
		char fp[2] = ")";
		//strcat(r, ap);
		strcat(r, $1);
		strcat(r, ap);
		strcat(r, $3);
		strcat(r, fp);
		//strcat(r, fp);
		strcpy($$, r);
		}
	;

FUNC_ASSIGN_VAR : NAME AP NAME FP ASSIGN expr { 
		
		//printFunctions();
		bracket($1, $6, "\0");
	}
	;

expr : expr SUM expr {
		char r[150] = "";
		char a[2] = "+";
		char b[2] = "\0";
		char ap[2] = "(";
		char fp[2] = ")";
		strcat(r, a);
		strcat(r, ap);
		strcat(r, $1);
		strcat(r, fp);
		strcat(r, ap);
		strcat(r, $3);
		strcat(r, fp);
		strcpy($$, r);
		}
	| expr MIN expr {
		char r[150] = "";
		char a[2] = "-";
		char b[2] = "\0";
		char ap[2] = "(";
		char fp[2] = ")";
		strcat(r, a);
		strcat(r, ap);
		strcat(r, $1);
		strcat(r, fp);
		strcat(r, ap);
		strcat(r, $3);
		strcat(r, fp);
		strcpy($$, r);
		}
	| term
	| IF condition THEN expr ELSE expr {
		char r[150] = "";
		char ifa[3] = "if\0";
		char thena[5] = "then\0";
		char elsea[5] = "else\0";
		char b[2] = "\0";
		char ap[2] = "(";
		char fp[2] = ")";
		strcat(r, ifa);
		strcat(r, ap);
		strcat(r, $2);
		strcat(r, fp);
		strcat(r, thena);
		strcat(r, ap);
		strcat(r, $4);
		strcat(r, fp);
		strcat(r, elsea);
		strcat(r, ap);
		strcat(r, $6);
		strcat(r, fp);
		strcat(r, b);
		strcpy($$, r);
		}
	;

condition: expr ASSIGN expr {
		char r[150] = "";
		char a[2] = "=";
		char b[2] = "\0";
		char ap[2] = "(";
		char fp[2] = ")";
		strcat(r, ap);
		strcat(r, a);
		strcat(r, $1);
		strcat(r, $3);
		strcat(r, b);
		strcat(r, fp);
		strcpy($$, r);
		}
	| expr GT expr {
		char r[150] = "";
		char a[2] = ">";
		char b[2] = "\0";
		char ap[2] = "(";
		char fp[2] = ")";
		strcat(r, ap);
		strcat(r, a);
		strcat(r, $1);
		strcat(r, $3);
		strcat(r, b);
		strcat(r, fp);
		strcpy($$, r);
		}
	| expr LT expr {
		char r[150] = "";
		char a[2] = "<";
		char b[2] = "\0";
		char ap[2] = "(";
		char fp[2] = ")";
		strcat(r, ap);
		strcat(r, a);
		strcat(r, $1);
		strcat(r, $3);
		strcat(r, b);
		strcat(r, fp);
		strcpy($$, r);
		}
	;

term: term TIMES factor {
		char r[150] = "";
		char a[2] = "*";
		char b[2] = "\0";
		char ap[2] = "(";
		char fp[2] = ")";
		strcat(r, a);
		strcat(r, ap);
		strcat(r, $1);
		strcat(r, fp);
		strcat(r, ap);
		strcat(r, $3);
		strcat(r, fp);
		strcpy($$, r);
		}
	| term DIV factor {
		char r[150] = "";
		char a[2] = "/";
		char b[2] = "\0";
		char ap[2] = "(";
		char fp[2] = ")";
		strcat(r, a);
		strcat(r, ap);
		strcat(r, $1);
		strcat(r, fp);
		strcat(r, ap);
		strcat(r, $3);
		strcat(r, fp);
		strcpy($$, r);
		}
	| factor	{;}
	;

factor: AP expr FP 		 {/* $$ = $2 */;}
	| MIN factor         {/* $$ = -$2 */;}
	| NUMBER             {;}
	| NAME               {;}
	| FUNC_CALL          {/* $<str>$ = $1 */;}
	;

%%

int searchParethesis(char* expr, int* ap, int* fp) {
    int abre = 0, fecha = 0, i, aux = 1;
    for(i = 0 ; i < strlen(expr) ; i++) {
        if(aux) {
            if(expr[i] == '(') {
                *ap = i;
                aux = 0;
            }
        }
        if(expr[i] == ')') {
            *fp = i;
        }
    }
}


//if x<2 the ....
void removeBrackets(char* expr) {
    int i, aux = 0;
    for (i = 0; i < strlen(expr) ; ++i) {
        if(expr[i] == ']')  aux = i;
    }
    if(i == strlen(expr)) {
        return;
    }
    aux++;
    for (i = 0; i < strlen(expr); ++i) {
        expr[i] = expr[aux++];
    }
    expr[i] = '\0';
}

//Recebe o nome da funcao (ID) e a expressao (EXPR) em formato bracket
void storeFunction(char* name, char* expr) {
    if(funcCounter > 100) {
        printf("tabela de funcoes cheia!\n");
        return;
    }

    //checo se name ja existe na lista
    int i;
    for (i = 0; i < funcCounter ; ++i) {
        if(strcmp(table[i].name, name) == 0) {
            printf("%s ja existe!\n",name);
            return;
        }
    }

    i = funcCounter++;

    //salvando o ID da funcao
    int len = strlen(name);
    table[i].name = (char*) malloc(len+1);
    strcpy(table[i].name, name);
    table[i].name[len] = '\0';

    //convertendo expr em expressao de turner
    char* exprName = (char*) malloc(sizeof(char)+1);
    exprName[0] = name[0];
    exprName[1] = '\0';

    //sanvando a expressao de turner na tabela
    len = strlen(expr);
    table[i].expr = (char*) malloc(len+1);
    strcpy(table[i].expr, expr);
    table[i].expr[len] = '\0';
}

int countIntDigits(int num) {
    int i = 0;
    while(num > 0) {
        num = num/10;
        i++;
    }
    return i;
}

char* convertIntToString(int number) {
    int numDigits = countIntDigits(number);
    char* string = (char*) malloc(numDigits+1);
    int i, j = numDigits-1;
    for (i = numDigits-1; i >= 0 ; --i) {
        int num = number%10;
        char aux = num+'0';
        string[i] = aux;
        number /= 10;
    }
    string[numDigits] = '\0';
    return string;
}


void printFunctions() {
    int i;
    for (i = 0; i < funcCounter; ++i) {
        printf("%s\t%s\n", table[i].name, table[i].expr);
    }
}

int functionCall(char* expr) {
    //busco o argumento de dentro da funcao
    int ap, fp, i, j, index = -1;
    searchParethesis(expr, &ap, &fp);
    //copiar o nome da funcao
    char* name = (char*) malloc(ap+1);
    for (i = 0; i < ap; ++i) {
        name[i] = expr[i];
    }
    name[i] = '\0';

    //copiar o argumento num novo vetor
    char* param = (char*) malloc(fp-ap);
    for (i = ap+1, j = 0; i < fp; ++i) {
        param[j++] = expr[i];
    }
    param[j] = '\0';

    //Checando se eh caracter
    //CHAMADA RECURSIVA
    if(param[0] < '0' || param[0] > '9') {
        int answer = functionCall(param);
        char* strAnswer = convertIntToString(answer);
        strcpy(param, strAnswer);
    }


    //buscando o index da funcao
    for (i = 0; i < funcCounter ; ++i) {
        if(strcmp(table[i].name, name) == 0) {
            index = i;
            break;
        }
    }

    if(index < 0) {
        printf("funcao nao existe!\n");
        return 0;
    }

    rootGrafo = gerarGrafo(table[index].expr);
    adicionarParametro(atoi(param));
    //printf("chegou aqui %s\n", table[index].expr);
    reduzirGrafo(0);

    //printf("%s(%s)=%i\n",name,param,rootGrafo->esq->tipo);
    return rootGrafo->esq->tipo;
}


void func_call(char* str){
	int result = functionCall(str);
	printf("%d\n", result);

}
float calc(float a, char c, float b){
	switch(c){
		case '+' :
			return a + b;
		case '-':
			return a - b;
	}
}

void bracket(char *fun, char *str, char *valor){
	char* r = converter_para_bracket(fun, str, valor);
	//printf("%s\n", str);
	storeFunction(fun, r);
}

void yyerror(char *msg) {
	fprintf(stderr, "%s\n", msg);
	exit(1);
}

int main(){
	yyparse();
	return 0;
}