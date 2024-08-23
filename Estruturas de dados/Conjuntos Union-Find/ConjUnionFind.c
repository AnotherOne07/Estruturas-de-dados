#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ConjUnionFind.h"

// função responsável por inicializar o conjunto unitário
Conjunto *makeSet(int valor) {

  // aloca memória para um conjunto
  Conjunto *conjunto = (Conjunto *)malloc(sizeof(Conjunto));
  if (conjunto == NULL) {
    printf("Não foi possível alocar memória para o conjunto");
    exit(EXIT_FAILURE);
  }
  
  // aloca memória para um elemento
  Elemento *elemento = (Elemento *)malloc(sizeof(Elemento));
  if (elemento == NULL) {
    printf("Não foi possível alocar memória para o elemento");
    exit(EXIT_FAILURE);
  }

  // elemento criado com o seu valor e sendo o seu próprio representante
  elemento->valor = valor;
  elemento->proximo = NULL;
  elemento->representante = elemento;
  elemento->conjunto = conjunto;

  // o conjunto unitário composto pelo elemento e de tamanho 1
  conjunto->cabeca = elemento;
  conjunto->cauda = elemento;
  conjunto->tamanho = 1;

  return conjunto;
}

// retorna o elemento representante do conjunto que determinado elemento faz parte
Elemento *findSet(Elemento *a) { 
  return a->representante; 
}

void unionSet(Elemento *a, Elemento *b) {

  // encontrando os conjuntos que representam os elementos
  Conjunto *x = findSet(a)->conjunto;
  Conjunto *y = findSet(b)->conjunto;

  // evita a união de conjuntos iguais, ou seja, elementos que estão no mesmo conjunto
  if (x == y) {
    printf("Nao é possível unir um conjunto com ele mesmo");
    exit(EXIT_FAILURE);
  }

  //testa qual dos conjuntos é o de menor tamanho
  if (x->tamanho <= y->tamanho) {
    Elemento *aux = x->cabeca;

    //transforma o representante de cada elemento do conjunto x no representante do conjunto b
    while (aux) {
      aux->representante = findSet(b);
      aux = aux->proximo;
    }

    //atualizando o tamanho para a soma dos tamanhos dos conjuntos unidos 
    y->tamanho = x->tamanho + y->tamanho;
    x->tamanho = 0;

    //----------UNINDO O CONJUNTO X AO Y----------
    //alterando os apontadores na união dos dois conjuntos
    y->cauda->proximo = x->cabeca; //cabeça do conjunto x sendo unido à cauda de conjunto y
    y->cauda = x->cauda; 
    x->cabeca = NULL;
    x->cauda = NULL;
    
  } else {
    Elemento *aux2 = y->cabeca;

    //transforma o representante de cada elemento do conjunto y no representante do conjunto a
    while (aux2) {
      aux2->representante = findSet(a);
      aux2 = aux2->proximo;
    }

    //atualizando o tamanho para a soma dos tamanhos dos conjuntos unidos
    x->tamanho = y->tamanho + x->tamanho;
    y->tamanho = 0;

    //----------UNINDO O CONJUNTO Y AO X----------
    //alterando os apontadores na união dos dois conjuntos
    x->cauda->proximo = y->cabeca; //cabeça do conjunto y sendo unido à cauda de conjunto x
    x->cauda = y->cauda;
    y->cabeca = NULL;
    y->cauda = NULL;
  }
}

void printConj(Elemento *a) {
  
  /* informa o tamanho do conjunto original desse elemento e o valor do seu
    representante*/
  printf("Tamanho: %d\n", a->conjunto->tamanho);
  printf("Representante: %d\n", a->representante->valor);
  printf("[");
  
  a = a->conjunto->cabeca;
  
  // exibe os elementos do conjunto começando pela sua cabeça
  while (a) // a != NULL
  {
    printf("%d", a->valor);
    if (a->proximo)
      printf(",");
    a = a->proximo;
  }
  printf("]\n");
}

// função responsável por limpar/eliminar a lista
void limpar(Conjunto *conjunto) {
  
  Elemento *elemento = conjunto->cabeca;
  Elemento *proximo;

  // varre a lista toda até que todos os elementos estejam limpos
  while (elemento != NULL) {
    proximo = elemento->proximo;
    free(elemento);
    elemento = proximo;
  }
}