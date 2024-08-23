#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdbool.h>


#include "ListaSeqDin.h"

char compare(ITEM x, ITEM y)
{
    return x > y ? 1 : (x < y ? -1 : 0);
}


void inicializar(LISTA_DINAMICA *l)
{
    l->tamanho = 0;
}


bool igual(ITEM x, ITEM y)
{
  return compare(x, y) == 0;
}


int tamanho(LISTA_DINAMICA *l)
{
    return l->tamanho;
}


bool cheia(LISTA_DINAMICA *l)
{
    return tamanho(l) == MAX;
}


bool vazia(LISTA_DINAMICA *l)
{
    return tamanho(l) == 0;
}


bool inserir(ITEM item, LISTA_DINAMICA *l)
{
    if (tamanho(l) == MAX) 
        return false; // lista cheia
    else{
        P_ITEM p_item = (ITEM*) malloc(sizeof(item));
        *p_item = item;
        l->itens[l->tamanho++] = p_item;
    }
    return true;
}


int buscar(ITEM item, LISTA_DINAMICA *l, int inicio, int fim)
{
    for (int pos = inicio; pos < fim; pos++)
       if (igual(item, *l->itens[pos]))
           return pos; // achou
    return -1; // nao achou
}


bool remover(ITEM item, LISTA_DINAMICA *l)
{
    int i, j;
    int pos = buscar(item, l, 0, l->tamanho - 1);
    if (pos == -1)
      return false; // nao achou
    
    free(l->itens[pos]);
    for (i = pos; i < l->tamanho - 1; i++){
        l->itens[i] = l->itens[i+1]; 
    }

    l->tamanho--;
    return true; // achou
}


void removerItem(ITEM item, LISTA_DINAMICA *l)
{
  
}


void exibirItem(P_ITEM i)
{
    printf("%d", *i);
}


void exibirLista(LISTA_DINAMICA *l)
{  
    printf("LISTA : ");
    printf("[");
    for(int i = 0; i < tamanho(l);)
    {
        exibirItem(l->itens[i++]);
        if (i < tamanho(l))
           printf(",");
    }
    printf("]\n");
}


void destruir(LISTA_DINAMICA *l)
{
  for(int i = 0; i < l->tamanho; i++)
      free(l->itens[i]);
  l->tamanho = 0;
}