#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "ListaCirc.h"


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
    l->cabeca = (NO*) malloc(sizeof(NO));
    l->cabeca->prox = l->cabeca;  // faz a referencia circular
    l->tamanho = 0;
}


NO* criarNo(ITEM item, NO *prox)
{
    NO* pNovo = (NO*) malloc(sizeof(NO));
    if (pNovo == NULL)
    {
        printf("Nao foi possivel alocar memoria para pNovo\n");
        exit(EXIT_FAILURE);        
    }
    pNovo->item = item;
    pNovo->prox = prox;
    return pNovo;
}


int tamanho(LISTA *l)
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


bool inserir(ITEM item, LISTA *l){
    l->cabeca->prox = criarNo(item, l->cabeca->prox);
    l->tamanho++;
    return true;    
}


/*
    Objetivo: Retorna o endereco do No contido na posicao informada.
              Caso a posicao seja invalida (negativa ou maior ou igual
              ao tamanho da lista, retorna NULL.
*/
NO* noNaPosicao(int n, LISTA *l)
{
    if (n < 0 || n >= tamanho(l))
        return NULL;
    
    NO* p = l->cabeca->prox;
    for (int i = 0; i < n; i++)
        p = p->prox;
    return p;  // existe um n-esimo e p aponta para ele
}


int buscar(ITEM item, LISTA *l)
{
    NO* p = l->cabeca->prox;
    int pos = 0;
    while (p != l->cabeca)   // enquanto nao deu a volta
    {
        if (igual(item, p->item))
            return pos;
        p = p->prox;
        pos++;
    }
    return -1; // Nao achou
}


ITEM enesimo(int n, LISTA *l) {
    NO * no = noNaPosicao(n, l);
    if (no)
        return no->item;
    else
    {
        printf("Posicao inexistente na lista (%d)\n", n);
        exit(EXIT_FAILURE);
    }
}


bool alterar(ITEM item, int pos, LISTA *l)
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


bool inserirNaPos(ITEM item, int i, LISTA *l)
{
    if (i < 0 || i > tamanho(l))
    {
        printf("Posicao de insercao invalida (%d)\n", i);
        exit(EXIT_FAILURE);
    }
    
    NO* pAnterior;
    if (i == 0) // insercaso na cabeca da lista
       pAnterior = l->cabeca;
    else // insercao no meio ou final da lista
       pAnterior = noNaPosicao(i-1, l);

    pAnterior->prox = criarNo(item, pAnterior->prox);
    l->tamanho++;
    return true;
}


bool remover(ITEM item, LISTA *l)
{
   NO* pAnterior = l->cabeca;

   // Percorre a lista ate encontrar um item com a chave procurada.
   // Remove o item e corrige o apontador do item anterior para
   // apontar para o proximo item
   while (pAnterior->prox != l->cabeca)
   {
      NO* pAtual = pAnterior->prox;
       
      if (igual(item, pAtual->item))
      {
         pAnterior->prox = pAtual->prox;
         free(pAtual);
         l->tamanho--;
         return true;
      }
       
      pAnterior = pAtual;
   }
   return false; // Nao removeu
}


void limpar(LISTA *l)
{
    NO* atual = l->cabeca->prox;
    while (atual != l->cabeca)   // enquando nao deu a volta completa
    {
        NO* prox = atual->prox; // guarda proxima posicao
        free(atual);            // libera memoria apontada por atual
        atual = prox;
    }
    l->cabeca->prox = l->cabeca;
    l->tamanho = 0;
}


void destruir(LISTA *l)
{
    limpar(l);
    free(l->cabeca);  // liberacao no No cabeca
    l->cabeca = NULL; // ajusta inicio da lista (vazia)
}


void exibirItem(ITEM i)
{
    printf("%d", i);
}


void exibirLista(LISTA *l)
{
    printf("[");
    NO* p = l->cabeca->prox;
    while (p != l->cabeca)   // enquando nao deu a volta completa
    {
        exibirItem(p->item);
        if (p->prox != l->cabeca)
           printf(",");
        p = p->prox;
    }
    printf("]");
}


/////////////////////// EXERCICIOS //////////////////////////

bool removerDaPos(ITEM *item, int i, LISTA *l)
{
  NO* pAnterior;

  if (i < 0 || i >= l->tamanho)
    return false;

  else
  {
    if(i == 0)
      pAnterior = l->cabeca;
    else
      pAnterior = noNaPosicao(i - 1, l);

    NO* pRemovido = pAnterior->prox;
    pAnterior->prox = pRemovido->prox;
    *item = pRemovido->item;
    free(pRemovido);
    l->tamanho--;
    return true;
  }

  return false;
}


LISTA* clonar(LISTA *l)
{
  LISTA* clone = (LISTA*) malloc(sizeof(LISTA));

  inicializar(clone);
  for(int i = 0; i < l->tamanho; i++)
    {
      ITEM item = (noNaPosicao(i, l))->item;
      inserirNaPos(item, clone->tamanho, clone);
    }

  return clone;
}

