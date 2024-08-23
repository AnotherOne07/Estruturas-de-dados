#include <stdio.h>
#include <stdlib.h>

#include "ArvoreRN.h"

int main() {
  ARVORE_RUBRO_NEGRA arvore;
  arvore.nulo = (NO*) malloc(sizeof(NO));
  arvore.nulo->cor = PRETO;
  arvore.raiz = arvore.nulo;
    
  ITEM valores[7] = {7,3,18,10,22,8,11};

  for (int i = 0; i < 7; i++) {
    inserir(&arvore, valores[i]);
    printf("=>Inserindo [%d]\n", valores[i]);
  }

  printf("Árvore rubro-negra em ordem:\n");
  imprimirEmOrdem(&arvore, arvore.raiz);
  printf("\n");
  
  printf("=> Removendo [4]\n");
  remover(&arvore, 4);

  printf("=> Removendo [8]\n");
  remover(&arvore, 8);

  printf("Árvore rubro-negra em ordem:\n");
  imprimirEmOrdem(&arvore, arvore.raiz);
  printf("\n");

  printf("=>Inserindo [4]\n");
  inserir(&arvore, 4);
  printf("Árvore rubro-negra em ordem:\n");
  imprimirEmOrdem(&arvore, arvore.raiz);
  printf("\n");
  return 0;
}