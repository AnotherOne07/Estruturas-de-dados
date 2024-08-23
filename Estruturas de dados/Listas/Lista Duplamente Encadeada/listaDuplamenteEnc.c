#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef int ITEM;

typedef struct estrutura
{
    ITEM item;
    struct estrutura *ant;
    struct estrutura *prox;
} NO;

typedef struct
{
    NO* cabeca;
    NO* cauda;
    long tamanho;
} LISTA;


char compare(ITEM x, ITEM y)
{
    return x > y ? 1 : (x < y ? -1 : 0);
}


bool igual(ITEM x, ITEM y)
{
    return compare(x,y) == 0;
}


void inicializar(LISTA *l)
{
    l->cabeca = NULL;
    l->cauda = NULL;
    l->tamanho = 0;
}


NO* criarNo(ITEM item,  NO *ant, NO *prox)
{
    NO* pNovo = (NO*) malloc(sizeof(NO));
    if (pNovo == NULL)
    {
        printf("Nao foi possivel alocar memoria para pNovo\n");
        exit(EXIT_FAILURE);        
    }
    pNovo->item = item;
    pNovo->ant = ant;
    pNovo->prox = prox;
    return pNovo;
}


long tamanho(LISTA *l)
{
    return l->tamanho;
}


bool cheia(LISTA *l)
{
    return false;
}


bool vazia(LISTA *l)
{
    return tamanho(l) == 0;
}


NO* noNaPosicao(long n, LISTA *l)
{
    if (n < 0 || n >= tamanho(l))
        return NULL;
    
    NO* p = l->cabeca;
    for (long i = 0; i < n; i++)
        p = p->prox;
    return p;  // existe um n-esimo e p aponta para ele
}


NO* buscarNO(ITEM item, LISTA *l)
{
    NO* p = l->cabeca;
    while (p)   // enquanto nao e NULL
    {
        if (igual(item, p->item))
            return p;
        p = p->prox;
    }
    return NULL; // Nao achou
}


bool inserir(ITEM item, LISTA *l)
{
    NO* pNovo = criarNo(item, NULL, l->cabeca);
    l->tamanho++;

    // Insercao na cabeca da lista
    if (l->cabeca) // cabeca != NULL
       l->cabeca->ant = pNovo;  // ajusta o apontador para o anterior
                                // na antiga cabeca
    l->cabeca = pNovo;
    
    if (l->cauda == NULL) // se nao tinha cauda, o novo no estara tambem na cauda 
       l->cauda = pNovo;

    return true;
}


long buscar(ITEM item, LISTA *l)
{
    NO* p = l->cabeca;
    long pos = 0;
    while (p)   // enquanto nao e NULL
    {
        if (igual(item, p->item))
            return pos;
        p = p->prox;
        pos++;
    }
    return -1; // Nao achou
}


ITEM enesimo(long n, LISTA *l) {
    NO * no = noNaPosicao(n, l);
    if (no)
        return no->item;
    else
    {
        printf("ERRO: Posicao %ld fora dos limites da lista (0 a %ld).\n",
               n, tamanho(l)-1);
        exit(EXIT_FAILURE);
    }
}


bool alterar(ITEM item, long pos, LISTA *l)
{
    NO * no = noNaPosicao(pos, l);
    if (no)
    {
        no->item = item;  // existe um n-esimo e p aponta para ele
        return true; 
    }
    else
        return false;
}


bool inserirNaPos(ITEM item, long i, LISTA *l)
{
    if (i < 0 || i > tamanho(l))
    {
        printf("Posicao de insercao invalida (%d)\n", i);
        exit(EXIT_FAILURE);
    }

    NO* pNovo = NULL;
    if (i == 0) // Insercao na cabeca da lista (vazia ou com 1 ou + itens)
    {
        pNovo = criarNo(item, NULL, l->cabeca);
        if (vazia(l)) // o novo no sera Cabeca e Cauda
            l->cauda = pNovo;
        else // ajusta o apontador anterior da cabeca atual para a nova cabeca (pNovo)
            l->cabeca->ant = pNovo;
        l->cabeca = pNovo;
    } 
    else
    {
        if (i == tamanho(l)) // Insercao na cauda
        {
            pNovo = criarNo(item, l->cauda, NULL);
            l->cauda->prox = pNovo;
            l->cauda = pNovo;
        }
        else // Insercao no meio
        {
             NO * noAnt = noNaPosicao(i-1, l); // Obtem o no anterior
             pNovo = criarNo(item, noAnt, noAnt->prox);
             pNovo->prox->ant = pNovo; // ajusta o apontador anterior do NO seguinte 
             noAnt->prox = pNovo; // ajusta o apontador proximo do NO anterior
        }
    }
    
    l->tamanho++;
    return true;
}


bool remover(ITEM item, LISTA *l)
{
   NO* pAtual = buscarNO(item, l);
   if (pAtual != NULL)
   {
      if (pAtual == l->cabeca)  // ajusta a cabeca para o próximo do nó removido
         l->cabeca = pAtual->prox;

      if (pAtual == l->cauda)  // ajusta a cauda para o anterior do nó removido
         l->cauda = pAtual->ant;

      if (pAtual->prox != NULL)  // ajusta o apontador ant do próximo nó
         pAtual->prox->ant = pAtual->ant;

      if (pAtual->ant != NULL)  // ajusta o apontador prox do nó anterior
         pAtual->ant->prox = pAtual->prox;

      free(pAtual);
      l->tamanho--;
      return true;        
   }

   return false;  // nao removeu 
}


void limpar(LISTA *l)
{
    NO* atual = l->cabeca;
    while (atual)   // enquando nao chegar ao final da lista
    {
        NO* prox = atual->prox; // guarda proxima posicao
        free(atual);            // libera memoria apontada por atual
        atual = prox;
    }
    l->cabeca = NULL;
    l->cauda = NULL;
    l->tamanho = 0;
}


void destruir(LISTA *l)
{
    limpar(l);
}


void exibirItem(ITEM i)
{
    printf("%d", i);
}


void exibirLista(LISTA *l)
{
    printf("[");
    NO* p = l->cabeca;
    while (p)   // enquando nao chegou ao final da lista
    {
        exibirItem(p->item);
        if (p->prox)
           printf(",");
        p = p->prox;
    }
    printf("]");
}