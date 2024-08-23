#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ListaEnc.h"

char compare(ITEM x, ITEM y) { return x > y ? 1 : (x < y ? -1 : 0); }

bool igual(ITEM x, ITEM y) { return compare(x, y) == 0; }

void inicializar(LISTA *l) {
  l->cabeca = NULL;
  l->tamanho = 0;
}

NO *criarNo(ITEM item, NO *prox) {
  NO *pNovo = (NO *)malloc(sizeof(NO));
  if (pNovo == NULL) {
    printf("Nao foi possivel alocar memoria para pNovo\n");
    exit(EXIT_FAILURE);
  }
  pNovo->item = item;
  pNovo->prox = prox;
  return pNovo;
}

int tamanho(LISTA *l) { return l->tamanho; }

bool cheia(LISTA *l) { return false; }

bool vazia(LISTA *l) { return l->cabeca == NULL; }

bool inserir(ITEM item, LISTA *l) {
  l->cabeca = criarNo(item, l->cabeca);
  l->tamanho++;
  return true;
}

/*
    Objetivo: Retorna o endereco do No contido na posicao informada.
              Caso a posicao seja invalida (negativa ou maior ou igual
              ao tamanho da lista, retorna NULL.
*/
NO *noNaPosicao(int n, LISTA *l) {
  if (n < 0 || n >= tamanho(l))
    return NULL;

  NO *p = l->cabeca;
  for (int i = 0; i < n; i++)
    p = p->prox;
  return p; // existe um n-esimo e p aponta para ele
}

int buscar(ITEM item, LISTA *l) {
  NO *p = l->cabeca;
  int pos = 0;
  while (p) // p != NULL
  {
    if (igual(item, p->item))
      return pos;
    p = p->prox;
    pos++;
  }
  return -1; // Nao achou
}

ITEM enesimo(int n, LISTA *l) {
  NO *no = noNaPosicao(n, l);
  if (no)
    return no->item;
  else {
    printf("Posicao inexistente na lista (%d)\n", n);
    exit(EXIT_FAILURE);
  }
}

bool alterar(ITEM item, int pos, LISTA *l) {
  NO *no = noNaPosicao(pos, l);
  if (no) {
    no->item = item; // existe um n-esimo e p aponta para ele
    return true;
  } else
    return false;
}

bool inserirNaPos(ITEM item, int i, LISTA *l) {
  if (i < 0 || i > tamanho(l)) {
    printf("Posicao de insercao invalida (%d)\n", i);
    exit(EXIT_FAILURE);
  }

  if (i == 0) // insercao na cabeca da lista
  {
    l->cabeca = criarNo(item, l->cabeca);
  } else // insercao no meio ou final
  {
    NO *pAnterior = noNaPosicao(i - 1, l);
    pAnterior->prox = criarNo(item, pAnterior->prox);
  }
  l->tamanho++;
  return true;
}

bool remover(ITEM item, LISTA *l) {
  if (vazia(l))
    return false;

  NO *pAnterior = l->cabeca;

  if (igual(item, l->cabeca->item)) {
    // Remove o item da cabeca da lista e a cabeca passa a ser
    // item seguinte ao removido
    l->cabeca = l->cabeca->prox;
    l->tamanho--;
    free(pAnterior);
    return true;
  } else {
    // Percorre a lista ate encontrar o item procurado.
    // Remove o item e corrige o apontador prox do NO anterior para
    // apontar para o proximo NO do item sendo removido
    while (pAnterior->prox) // prox != NULL
    {
      NO *pAtual = pAnterior->prox;

      if (igual(item, pAtual->item)) {
        pAnterior->prox = pAtual->prox;
        free(pAtual);
        l->tamanho--;
        return true;
      }

      pAnterior = pAtual;
    }
  }
  return false; // Nao removeu
}

void exibirItem(ITEM i) { printf("%d", i); }

void exibirLista(LISTA *l) {
  printf("[");
  NO *p = l->cabeca;
  while (p) // p != NULL
  {
    exibirItem(p->item);
    if (p->prox)
      printf(",");
    p = p->prox;
  }
  printf("]");
}

void limpar(LISTA *l) {
  NO *atual = l->cabeca;
  while (atual) {
    NO *prox = atual->prox; // guarda proxima posicao
    free(atual);            // libera memoria apontada por atual
    atual = prox;
  }
  l->cabeca = NULL; // ajusta inicio da lista (vazia)
  l->tamanho = 0;
}

void destruir(LISTA *l) { limpar(l); }

////////////////////// EXERCICIOS LISTA ENCADEADA /////////////////



bool removerDaPos(ITEM *item, int i, LISTA *l) 
{
  NO *pRemovido = noNaPosicao(i, l);

  if (pRemovido) {
    if (i == 0) {
      pRemovido = l->cabeca;
      l->cabeca = pRemovido->prox;
    }

    else {
      NO *pAnterior = noNaPosicao(i - 1, l);
      pAnterior->prox = pRemovido->prox;
    }

    l->tamanho--;
    *item = pRemovido->item;
    free(pRemovido);
    return true;
  }
  return false;
}



//////////////// LISTA ENCADEADA ORDENADA //////////////////////


bool inserirOrd(ITEM it, LISTA* l){
  int n = 1;
  
  if(l->cabeca) // Verifica se a lista nn tem cabeca --- Se ta vazia
  {
    if (it < l->cabeca->item)
    {
      inserir(it, l); //Insere no Inicio se for menor q a cabeca
      return true;
    }
    
    NO* pAtual = l->cabeca->prox; //Comeca do 2° elemento
    
    while(n < tamanho(l)) // Percorre a lista até achar alguém maior q o item
    {
      if (it < pAtual->item)
      {
        inserirNaPos(it, n, l); // Insere antes de Nó na posicao n
        return true;
      }
      n++;
    }
    
    inserirNaPos(it, l->tamanho, l); //Se eu n achar nenhum maior q ele, insiro no final 
    return true;

  }
    
  else
  {
    l->cabeca = criarNo(it, NULL);
    l->tamanho++;
    return true;
  }

  return false;
}

void inverter (LISTA *l)
{
  NO* pAtual = noNaPosicao(l->tamanho - 1, l);
  NO* pCabecaNova = pAtual; //pCabecaNova é o ultimo elemento da lista antiga
  
  for(int i = l->tamanho - 2; i >= 0; i--)
  {
    pAtual->prox = noNaPosicao(i, l);
    pAtual = pAtual->prox;
  }

  l->cabeca->prox = NULL;
  l->cabeca = pCabecaNova; 
}

void intersecao(LISTA* A, LISTA* B, LISTA* I)
{
  LISTA* listaMenor = A;
  LISTA* listaMaior = B;
  int cmp = compare(A->tamanho, B->tamanho);
  
  if (cmp == 1)
  {
    listaMaior = A;
    listaMenor = B; 
  }
    
  for(int i = 0; i < listaMenor->tamanho; i++)
    {
      ITEM item = (noNaPosicao(i, listaMenor))->item;
      if(buscar(item, listaMaior) != -1)
        inserirNaPos(item, I->tamanho, I);
    }
}
