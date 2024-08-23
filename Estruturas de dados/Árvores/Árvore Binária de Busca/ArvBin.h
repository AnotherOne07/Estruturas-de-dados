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


//////////////////////////////////////////////////////////////
// FUNCOES ESPECIFICAS DA ARVORE BINARIA DE BUSCA
//////////////////////////////////////////////////////////////

// Retorna true se a item for encontrado.
// Neste caso, p aponta para o No.
// Se o item nao for encontrado, retorna false e p
// aponta para o No que seria o seu pai (caso existisse).
bool encontrarNo(ITEM item, ARVORE_BINARIA **p, ARVORE_BINARIA *arvore);

// Procura o item na arvore, retornando true caso esteja contido
// e false caso contrario
bool contem(ITEM item, ARVORE_BINARIA *arvore);

// Tenta inserir um No na Arvore Binaria de Busca apontada por arvore.
// Se conseguir, retorna true.
bool inserir(ITEM item, ARVORE_BINARIA **arvore);

// Retira o No contendo o item da arvore apontada por arvore. 
// Se esse No for retirado, retorna true. Caso contrario, false.
bool remover(ITEM item, ARVORE_BINARIA **arvore);

#endif // ARV_BINARIA