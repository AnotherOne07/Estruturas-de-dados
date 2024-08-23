#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#ifndef FILA_ENC
#define FILA_ENC

typedef int ITEM;

typedef struct estrutura
{
    ITEM item;
    struct estrutura *prox;
} NO;

typedef struct
{
    NO* inicio;
    NO* fim;
    int tamanho;
} FILA;

/*
   Compara o item x com o y, retornando:
     1 caso x > y
     0 caso x = y
    -1 caso x < y
*/
char compare(ITEM x, ITEM y);

// Retorna true se x = y e false caso contrario
bool igual(ITEM x, ITEM y);

// Inicializa a fila deixando-a pronta para ser utilizada.
void inicializar(FILA *f);

// Retornar o tamanho da fila
int tamanho(FILA *f);

// Nunca estara cheia pois o limite e a memoria disponivel
bool cheia(FILA *f);

// Retorna true se a filha esta vazia (Tamanho = 0)
bool vazia(FILA *f);

/* 
  Objetivo: Insere um item no final da fila. Retorna true caso
            tenha sucesso e false caso contrario.
*/
bool inserir(ITEM item, FILA *f);

/*
  Objetivo: Busca na lista o item passado.
            Caso encontre, retorna a posicao (entre 0 e tamanho - 1).
            Caso nao encontre, retorna o valor -1.

/*
  Objetivo: Acessa a frente da Fila e atribui ao parâmetro item, sem afetar
            o estado da Fila. Retorna true quando algum item foi obtido.
*/
bool frente(ITEM *item, FILA *f);

/*
  Objetivo: Retira o No do inicio da Fila (frente) e atribui
            ao parametro item.
            Retorna true quando algum item foi retornado.
*/
bool retirar(ITEM *item, FILA *f);

// Retornar o n-esimo elemento da fila
// Pre-condicao: 0 <= n < tamanho
ITEM enesimo(int n, FILA *f);

// Exibicao de um item da fila
void exibirItem(ITEM i);

// Exibicao da fila
void exibir(FILA *f);

// Remove todos os valores da fila, deixando-a vazia
void limpar(FILA *f);

// Destruicao da fila
void destruir(FILA *f);

#endif // FILA_ENC