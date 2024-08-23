#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ConjUnionFind.h"

int main() {

  Conjunto c1, c2, c3, c4, c5, c6;
  
  // criando os conjuntos unitários
  c1 = *makeSet(1);
  c2 = *makeSet(2);
  c3 = *makeSet(3);
  c4 = *makeSet(4);
  c5 = *makeSet(5);
  c6 = *makeSet(6);

  printf("CONJUNTOS INICIAS UNITÁRIOS:\n");
  printConj(c1.cabeca);
  printConj(c2.cabeca);
  printConj(c3.cabeca);
  printConj(c4.cabeca);
  printConj(c5.cabeca);
  printConj(c6.cabeca);

  printf("CONJUNTOS 1 E 2, NESSA ORDEM, APÓS SEREM UNIDOS:\n");
  unionSet(c1.cabeca, c2.cabeca);
  printConj(c1.cabeca);
  printConj(c2.cabeca);

  printf("CONJUNTOS 1, 2 E 3, NESSA ORDEM, APÓS A UNIÃO DO 1 COM O 3:\n");
  unionSet(c1.cabeca, c3.cabeca);
  printConj(c1.cabeca);
  printConj(c2.cabeca);
  printConj(c3.cabeca);

  printf("CONJUNTOS 2 E 4, NESSA ORDEM, APÓS A UNIÃO DO 2 COM O 4:\n");
  unionSet(c4.cabeca, c2.cabeca);
  printConj(c2.cabeca);
  printConj(c4.cabeca);

  printf("CONJUNTOS 5 E 6, NESSA ORDEM, APÓS A UNIÃO DO 5 COM O 6:\n");
  unionSet(c5.cabeca, c6.cabeca);
  printConj(c5.cabeca);
  printConj(c6.cabeca);

  printf("CONJUNTOS 2 E 6, NESSA ORDEM, APÓS A UNIÃO DO 2 COM O 6:\n");
  unionSet(c2.cabeca, c6.cabeca);
  printConj(c2.cabeca);
  printConj(c6.cabeca);

  limpar(&c2);
  return 0;
}