#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#ifndef PILHA_ENC
#define PILHA_ENC

typedef int ITEM;

typedef struct estrutura
{
    ITEM item;
    struct estrutura *prox;
} NO;

typedef struct
{
    NO* topo;
    int tamanho;
} PILHA;

/*
   Compara o item x com o y, retornando:
     1 caso x > y
     0 caso x = y
    -1 caso x < y
*/
char compare(ITEM x, ITEM y);

// Retorna true se x = y e false caso contrario
bool igual(ITEM x, ITEM y);

// Inicializa a pilha deixando-a pronta para ser utilizada.
void inicializar(PILHA *p);

// Retornar o tamanho da pilha
int tamanho(PILHA *p);

// Nunca estara cheia pois o limite e a memoria disponivel
bool cheia(PILHA *p);

// Retorna true se a pilha esta vazia (Topo = NULL)
bool vazia(PILHA *p);

/* 
  Objetivo: Empilha um ITEM no topo da pilha.
            Coloca na cabeca de uma lista encadeada.
*/
bool empilhar(ITEM item, PILHA *p);

/*
  Objetivo: Acessa o topo da Pilha e atribui ao parâmetro item, sem afetar
            o estado da Pilha. Retorna true quando algum item foi obtido.
*/
bool topo(ITEM *item, PILHA *p);

/*
  Objetivo: Retira o No do Topo da Pilha e atribui ao parametro item.
            Retorna true quando algum item foi retornado.
*/
bool desempilhar(ITEM *item, PILHA *p);

// Retornar o n-esimo elemento da pilha comecando do topo (posicao 0)
// Pre-condicao: 0 <= n < tamanho
ITEM enesimo(int n, PILHA *p);

// Exibicao de um item da pilha
void exibirItem(ITEM i);

// Exibicao da pilha
void exibir(PILHA *p);

// Remove todos os valores da pilha, deixando-a vazia
void limpar(PILHA *p);

// Destruicao da pilha
void destruir(PILHA *p);

#endif // PILHA_ENC