#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "PilhaEnc.h"


char compare(ITEM x, ITEM y)
{
    return x > y ? 1 : (x < y ? -1 : 0);
}


bool igual(ITEM x, ITEM y)
{
    return compare(x,y) == 0;
}


void inicializar(PILHA *p)
{
    p->topo = NULL;
    p->tamanho = 0;
}


NO* criarNo(ITEM item, NO *prox)
{
    NO* pNovo = (NO*) malloc(sizeof(NO));
    pNovo->item = item;
    pNovo->prox = prox;
    return pNovo;
}


int tamanho(PILHA *p)
{
    return p->tamanho;
}


bool cheia(PILHA *p)
{
    return false;
}


bool vazia(PILHA *p)
{
    return p->topo == NULL;
}


bool empilhar(ITEM item, PILHA *p)
{
    p->topo = criarNo(item, p->topo);
    p->tamanho++;
    return true;
}


bool topo(ITEM *item, PILHA *p)
{
   if (vazia(p))
      return false; // Nao achou

   *item = p->topo->item;
   return true;
}


bool desempilhar(ITEM *item, PILHA *p)
{
   if (vazia(p))
      return false; // Nao desempilhou

   NO* pDesempilhado = p->topo;
   *item = pDesempilhado->item;

   // Muda o topo da lista para ser o NO abaixo do Topo atual  
   p->topo = pDesempilhado->prox;
   p->tamanho--;
   free(pDesempilhado);
   return true;
}

/*
    Objetivo: Retorna o endereco do No contido na posicao informada.
              Caso a posicao seja invalida (negativa ou maior ou igual
              ao tamanho da pilha, retorna NULL.
*/
NO* noNaPosicao(int n, PILHA *pilha)
{
    if (n < 0 || n > tamanho(pilha))
        return NULL;
    
    NO* p = pilha->topo;
    for (int i = 0; i < n; i++)
        p = p->prox;
    return p;  // existe um n-esimo e p aponta para ele
}


ITEM enesimo(int n, PILHA *p) {
    NO* no = noNaPosicao(n, p);
    if (no)
        return no->item;
    else
    {
        printf("Posicao inexistente na fila (%d)\n", n);
        exit(EXIT_FAILURE);
    }
}


void exibirItem(ITEM i)
{
    printf("%d", i);
}


void exibir(PILHA *pilha)
{
    printf("[");
    NO* p = pilha->topo;
    while (p)  // p != NULL
    {
        exibirItem(p->item);
        if (p->prox)
           printf(",");
        p = p->prox;
    }
    printf("]");
}


void limpar(PILHA *p)
{
    NO* atual = p->topo;
    while (atual) {
        NO* prox = atual->prox; // guarda proxima posicao
        free(atual);            // libera memoria apontada por atual
        atual = prox;
    }
    p->topo = NULL; // ajusta o topo da pilha (vazia)
    p->tamanho = 0;
}


void destruir(PILHA *p)
{
    limpar(p);
}


//////////////////// EXERCICIOS LISTA ///////////////////////

