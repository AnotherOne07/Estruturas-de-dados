#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Patricia.h"

#define MAX_PALAVRA 100

int main() {
    ARVORE_PATRICIA *arvore = NULL;
    inicializar(arvore);
    int numPalavras;

    arvore = Insere("casa", &arvore);
    arvore = Insere("casinha", &arvore);
    arvore = Insere("abacaxi", &arvore);
    arvore = Insere("zoo", &arvore);
    arvore = Insere("abacate", &arvore);
    arvore = Insere("brasil", &arvore);
    arvore = Insere("copa", &arvore);
    arvore = Insere("abobora", &arvore);
    arvore = Insere("copeiro", &arvore);
    arvore = Insere("notebook", &arvore);
    arvore = Insere("zoom", &arvore);

    printf("\nPalavras na Árvore Patricia:\n");
    imprime(arvore);


    Pesquisa("casa",  arvore);

    printf("\ncomposição dos Nós: \n");
    Ordem(arvore);

    return 0;
}
