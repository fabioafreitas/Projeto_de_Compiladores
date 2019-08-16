typedef struct reg
{
    char tipo;
    char status;
    struct reg *dir;
    struct reg *esq;
} node;

node *criarNode()
{
    node *nova = (node *)malloc(sizeof(node));
    nova->dir = NULL;
    nova->esq = NULL;
    return nova;
}

//TODO
void reduzK()
{
}

//TODO
void reduzS()
{
}

//TODO
void reduzGrafo()
{
    //se K, chama reduzK
    //se S, chama reduzS
}