#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#ifndef ARV_BINARIA
#define ARV_BINARIA

typedef enum {NoEsquerdo, NoDireito, NoPai, NoRaiz} DIRECAO;

typedef int ITEM;

typedef struct estrutura
{
    ITEM item;
    struct estrutura *esq;
    struct estrutura *dir;
    struct estrutura *pai;
} ARVORE_BINARIA;

/*
   Compara o item x com o y, retornando:
     1 caso x > y
     0 caso x = y
    -1 caso x < y
*/
char compare(ITEM x, ITEM y);

// Retorna true se x = y e false caso contrario
bool igual(ITEM x, ITEM y);

// Inicializa a arvore binaria deixando-a pronta para ser utilizada.
void inicializar(ARVORE_BINARIA *arvore);

// Retorna true se a arvore esta vazia (igual a NULL)
bool vazia(ARVORE_BINARIA *arvore);

// Cria um novo no usando o apontador arvore passado contendo o item,
// os apontadores para o pai e para os filhos contendo NULL
void criarNo(ITEM item, ARVORE_BINARIA **arvore);

// Testa se o No indicado por Direcao a partir de arv existe
bool existeNo(DIRECAO direcao, ARVORE_BINARIA *arvore);

// Deslocar o apontador Arvore para o No indicado por Direcao
void deslocar(DIRECAO direcao, ARVORE_BINARIA **arvore);

// O parametro item recebe o item contido no No apontado por Arvore.
// Caso tenha sucesso, retorna true. Caso contrário, false.
bool obterItem(ITEM *item, ARVORE_BINARIA *arvore);

// Altera o valor do item armazenado no No da Arvore.
// Caso tenha sucesso, retorna true. Caso contrário, false.
bool alterarItem(ITEM item, ARVORE_BINARIA *arvore);

// Cria um filho no NO apontado por Arvore na direcao informada
bool adicionarFilho(ITEM item, DIRECAO direcao, ARVORE_BINARIA *arvore);

// Desaloca da memoria toda a arvore
void disposeArvore(ARVORE_BINARIA *arvore);

// Desaloca da memoria arvore e seus descendentes, atualizando, se
// necessario, o apontador do pai dessa arvore ou atribuindo o valor
// NULL a arvore, quando for a raiz.
void deltree(ARVORE_BINARIA **arvore);

// Percorre a arvore, visitando primeiro a raiz, depois a subarvore
// esquerda e por ultimo a subarvore direita.
void preOrdem(ARVORE_BINARIA *arvore, void (*visite)(ARVORE_BINARIA*) );

// Percorre a arvore, visitando primeiro a subarvore esquerda,
// depois a raiz e por ultimo a subarvore direita.
void inOrdem(ARVORE_BINARIA *arvore, void (*visite)(ARVORE_BINARIA*) );

// Percorre a arvore, visitando primeiro a subarvore esquerda,
// depois subarvore direita e por ultimo a a raiz.
void posOrdem(ARVORE_BINARIA *arvore, void (*visite)(ARVORE_BINARIA*) );

ITEM calcularSubArvore(ARVORE_BINARIA *arvore, ITEM folhaEsq, ITEM folhaDir);

ITEM calcularExpressao(ARVORE_BINARIA *arvore);

bool arvoresIguais(ARVORE_BINARIA *arvore1, ARVORE_BINARIA *arvore2);

bool iguais(ARVORE_BINARIA *arv1, ARVORE_BINARIA *arv2);

bool chaveEstaNaArvore(ITEM chave, ARVORE_BINARIA *arv1);

#endif // ARV_BINARIA