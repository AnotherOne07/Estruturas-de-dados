#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef LISTA_SEQ_DINAMICA
#define LISTA_SEQ_DINAMICA

#define MAX 1000

typedef int ITEM;
typedef ITEM *P_ITEM;

typedef struct {
  P_ITEM itens[MAX];
  int tamanho;
} LISTA_DINAMICA;

char compare(ITEM x, ITEM y);

void inicializar(LISTA_DINAMICA *l);

bool igual(ITEM x, ITEM y);

int tamanho(LISTA_DINAMICA *l);

bool cheia(LISTA_DINAMICA *l);

bool vazia(LISTA_DINAMICA *l);

bool inserir(ITEM item, LISTA_DINAMICA *l);

void exibirItem(P_ITEM i);

void exibirLista(LISTA_DINAMICA *l);

void destruir(LISTA_DINAMICA *l);

bool remover(ITEM item, LISTA_DINAMICA *l);

int buscar(ITEM item, LISTA_DINAMICA *l, int inicio, int fim);

#endif // LISTA_SEQ_DINAMICA
