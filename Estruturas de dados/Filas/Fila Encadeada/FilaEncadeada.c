#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "FilaEnc.h"


char compare(ITEM x, ITEM y)
{
    return x > y ? 1 : (x < y ? -1 : 0);
}


bool igual(ITEM x, ITEM y)
{
    return compare(x,y) == 0;
}


void inicializar(FILA *f)
{
    f->inicio = NULL;
    f->fim = NULL;
    f->tamanho = 0;
}


NO* criarNo(ITEM item, NO *prox)
{
    NO* pNovo = (NO*) malloc(sizeof(NO));
    pNovo->item = item;
    pNovo->prox = prox;
    return pNovo;
}


int tamanho(FILA *f)
{
    return f->tamanho;
}


bool cheia(FILA *f)
{
    return false;
}


bool vazia(FILA *f)
{
    return f->inicio == NULL;
}


bool inserir(ITEM item, FILA *f){
    NO* pNovo = criarNo(item, NULL);
    if (vazia(f))    //  inicio == NULL
       f->inicio = pNovo;  // A lista esta vazia
    else
       f->fim->prox = pNovo;
    f->fim = pNovo;
    f->tamanho++;
    return true;
    
}


bool frente(ITEM *item, FILA *f)
{
   if (vazia(f))
      return false; // Nao achou

   *item = f->inicio->item;
   return true;
}


bool retirar(ITEM *item, FILA *f)
{
   if (frente(item, f))
   {
       NO* pFrente = f->inicio;    // Guarda o endereco do NO retirado
       f->inicio = pFrente->prox;  // Ajusta o inicio da fila

       if (f->inicio == NULL)
          f->fim = NULL;  // Fila esta vazia, logo fim deve ser NULL

       f->tamanho--;
       free(pFrente);
       return true;
   } 
   else
      return false;   // Nao retirou ja que esta nao tem nada na frente
}


/*
    Objetivo: Retorna o endereco do No contido na posicao informada.
              Caso a posicao seja invalida (negativa ou maior ou igual
              ao tamanho da lista, retorna NULL.
*/
NO* noNaPosicao(int n, FILA *f)
{
    if (n < 0 || n > tamanho(f))
        return NULL;
    
    NO* p = f->inicio;
    for (int i = 0; i < n; i++)
        p = p->prox;
    return p;  // existe um n-esimo e p aponta para ele
}


ITEM enesimo(int n, FILA *f) {
    NO * no = noNaPosicao(n, f);
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


void exibir(FILA *f)
{
    printf("[");
    NO* p = f->inicio;
    while (p)  // p != NULL
    {
        exibirItem(p->item);
        if (p->prox)
           printf(",");
        p = p->prox;
    }
    printf("]");
}


void limpar(FILA *f)
{
    NO* atual = f->inicio;
    while (atual) {
        NO* prox = atual->prox; // guarda proxima posicao
        free(atual);            // libera memoria apontada por atual
        atual = prox;
    }
    f->inicio = NULL; // ajusta o inicio da lista (vazia)
    f->fim = NULL;    // ajusta o fim da lista (vazia)
    f->tamanho = 0;

}


void destruir(FILA *f)
{
    limpar(f);
}