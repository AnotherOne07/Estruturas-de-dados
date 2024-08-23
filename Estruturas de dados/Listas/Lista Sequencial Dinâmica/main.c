#include "ListaSeqDin.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void testarInserir(LISTA_DINAMICA *l)
{
  printf("=> Teste de Inserir\n");
  int qtd;
  printf("Quantos itens deseja guardar na lista? ");
  scanf("%d", &qtd);

  ITEM item;
  for (int i = 0; i < qtd; i++) {
    printf("Digite o valor para a posicao [%d]: ", i);
    scanf("%d", &item);
    inserir(item, l);
  }
}


void testarExibirLista(LISTA_DINAMICA *l)
{
  exibirLista(l);
}


void testarRemover(LISTA_DINAMICA *l)
{
  ITEM item;
  
  printf("Qual item deseja remover ? : ");
  scanf("%d", &item);
  bool removeu = remover(item, l);
  removeu ? printf("Removeu\n") : printf("Nao Conseguiu Remover\n");
}

// ------------------------- MAIN --------------------------

int main() 
{
  LISTA_DINAMICA l;

  inicializar(&l);
  testarInserir(&l);
  testarExibirLista(&l);
  testarRemover(&l);
  testarExibirLista(&l);
  destruir(&l);

  return 0;
}
