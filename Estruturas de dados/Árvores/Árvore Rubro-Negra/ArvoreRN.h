#include <stdio.h>
#include <stdlib.h>

typedef int ITEM;

typedef enum {VERMELHO, PRETO} COR;

typedef struct estrutura {
  ITEM chave;
  COR cor;
  struct estrutura* esquerda;
  struct estrutura* direita;
  struct estrutura* pai;
} NO;

typedef struct {
  NO* raiz;
  NO* nulo; // Nó sentinela
} ARVORE_RUBRO_NEGRA;

// Função auxiliar para criar um novo nó
NO* criarNo(ARVORE_RUBRO_NEGRA* arvore, ITEM chave);

// Função auxiliar para rotacionar à esquerda
void rotacaoEsquerda(ARVORE_RUBRO_NEGRA* arvore, NO* x);

// Função auxiliar para rotacionar à direita
void rotacaoDireita(ARVORE_RUBRO_NEGRA* arvore, NO* y);

// Função para corrigir a inserção
void corrigirInsercao(ARVORE_RUBRO_NEGRA* arvore, NO* novo);

// Função para inserir um valor na árvore
void inserir(ARVORE_RUBRO_NEGRA* arvore, ITEM chave);

/*Para lidar com a violação, vamos considerar que a propriedade número 5 da arvore rubro negra 
não foi violada, e que o nó x ganhou uma nova camada de "preto", assim essa propriedade não 
será ferida, focando nas outras violações do código*/
void corrigirRemocao(ARVORE_RUBRO_NEGRA* arvore, NO* x);

// Função auxiliar para retornar o nó com a menor chave a partir de x
NO* minimo(ARVORE_RUBRO_NEGRA *arvore, NO* x);

// Função auxiliar para substituir o nó u pelo nó v
void substituir(ARVORE_RUBRO_NEGRA* arvore, NO* u, NO* v);

// Função para buscar um nó na árvore pela sua chave
NO* buscarNo(ARVORE_RUBRO_NEGRA* arvore, ITEM chave);

//A função remover é baseada no mesmo mecanismo da arvore binária de busca
void remover(ARVORE_RUBRO_NEGRA* arvore, ITEM chave);

// Função para imprimir a árvore em ordem
void imprimirEmOrdem(ARVORE_RUBRO_NEGRA* arvore, NO* no);