#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef CONJ_UF
#define CONJ_UF

/* estrutura de um elemento com: valor inteiro, ponteiro para o próximo
// elemento, ponteiro para o seu elemento representante e ponteiro para seu
conjunto*/
typedef struct Elemento {
  int valor;
  struct Elemento *proximo;
  struct Elemento *representante;
  struct Conjunto *conjunto;
} Elemento;

/* estrutura do conjunto com referência para a cabeça da lista encadeada, para a cauda da lista encadeada e o tamanho da lista */
typedef struct Conjunto {
  Elemento *cabeca;
  Elemento *cauda;
  int tamanho;
} Conjunto;

// cria um conjunto unitário com o elemento passado como parâmetro
Conjunto *makeSet(int elemento);

// une os conjuntos dos elementos representantes de cada elemento passado como parâmetro
void unionSet(Elemento *a, Elemento *b);

// retorna o elemento representante do elemento passado como parâmetro
Elemento *findSet(Elemento *a);

// imprime os elementos do conjunto passado como parâmetro
void printConj(Elemento *a);

// libera a memória de um conjunto passado como parâmetro
void limpar(Conjunto *a);

#endif