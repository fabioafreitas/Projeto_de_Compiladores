// Estrutura de um noh da memoria
typedef struct reg
{
    char tipo;
    char status;
    struct reg *dir;
    struct reg *esq;
} node;

//Cria um noh, retorna o ponteiro da mesma
node *criarNode()
{
    node *nova = (node *)malloc(sizeof(node));
    nova->dir = NULL;
    nova->esq = NULL;
    return nova;
}

//Procedimento que recebe duas variaveis, uma que aponta para
//um array e outra que aponta para um inteiro com a posicao do
//array a ser usada. O procedimento termina quando atinge a
//primeira posicao depois dos parenteses.
void casaParenteses(char *array1, int *p)
{
    int paren = 1;
    int c = *p;
    while (paren != 0)
    {
        switch (array1[c])
        {
        case '(':
            paren++;
            c++;
            break;
        case ')':
            paren--;
            c++;
            break;
        default:
            c++;
        }
    }
    *p = c;
}

//Procedimento que recebe duas variaveis, uma que aponta para
//um array e outra que aponta para um inteiro com a posicao do
//array a ser usada. O procedimento termina quando atinge a
//primeira posicao depois do argumento.
void achaArgumento(char *array1, int *p)
{
    int c = *p;
    if (array1[c] == '(')
    {
        c++;
        casaParenteses(array1, &c);
    }
    else
    {
        c++;
    }
    *p = c;
}

void gerarK()
{
    //recebe a string, root do grafo e a posicao de leitura da string
    //busca os argumentos deste combinador A B
    //se A ou B for parenteses, chamar gerar combinador recursivamente
    //senao organizo os ponteiros
    //altero o valor da leitura da string
}

void gerarS()
{
}

//Procedimento que recebe:
// Um ponteiro para a String a ser lida
// Um ponteiro que representa a Raiz do grafo
void gerarGrafo(char *string, node *root)
{
    int i = 1;
    while (string[i] != '\0')
    {
        switch (string[i])
        {
        case '(':
            //ainda pensando no procedimento deste case
            break;
        case 'S':
            //gero o S do grafo
            break;
        case 'K':
            //gero o
            break;
        default:
        }
    }
}
