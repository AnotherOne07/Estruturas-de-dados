#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int ITEM;

typedef struct{
  ITEM* itens;
  int tamanho;
  int inicio, fim, capacidade;
} FILA;



bool inicializar(FILA* f, int capacidade);

////////////////////////// MAIN ///////////////////////

int main(void) {
  printf("Hello World\n");
  return 0;
}

///////////////////// FUNCOES DE TESTE ////////////////


///////////////////// FUNCOES /////////////////////////

bool inicializar(FILA* f, int capacidade)
{
  ITEM* itensFila = (ITEM*) malloc(sizeof(ITEM)*capacidade);

  if (!(itensFila))
    return false;

  f->itens = itensFila;
  f->capacidade = capacidade;
  f->tamanho = 0; f->inicio = 0; f-> fim = 0;
  return true;
}

bool vazia(FILA* f)
{
  return f->tamanho == 0;
}

bool cheia(FILA* f)
{
  return f->tamanho == f->capacidade;
}

bool inserir(ITEM item, FILA* f)
{
  if (f->tamanho + 1 > f->capacidade)
    return false;
  
  f->fim = (f->fim + 1) % f->capacidade;
  f->itens[f->fim] = item;
  f->tamanho++;
  return true;
}

bool remover(ITEM *item, FILA* f)
{
  if (f->tamanho == 0)
    return false;

  *item = f->itens[f->inicio];
  f->inicio = (f->inicio + 1) % f->capacidade;
  f->tamanho--;
  return true;
}

