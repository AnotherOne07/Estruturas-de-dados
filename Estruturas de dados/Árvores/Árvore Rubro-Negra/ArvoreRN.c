#include <stdio.h>
#include <stdlib.h>

#include "ArvoreRN.h"

// Função auxiliar para criar um novo nó
NO* criarNo(ARVORE_RUBRO_NEGRA* arvore, ITEM chave) {
  NO* novo = (NO*)malloc(sizeof(NO));
  if(novo == NULL) {
    printf("ERRO: Erro na alocacao de memoria.");
    exit(EXIT_FAILURE);
  }
  novo->chave = chave;
  novo->cor = VERMELHO; // Novos nós são sempre vermelhos
  novo->esquerda = arvore->nulo;
  novo->direita = arvore->nulo;
  novo->pai = arvore->nulo;
  return novo;
}

// Função auxiliar para rotacionar à esquerda
void rotacaoEsquerda(ARVORE_RUBRO_NEGRA* arvore, NO* x) {
  NO* y = x->direita;
  x->direita = y->esquerda;
  
  // Verifica se y tem filho esquerdo
  if (y->esquerda != arvore->nulo)
    y->esquerda->pai = x;
  
  y->pai = x->pai;
  // Verifica se o pivô tem pai
  if (x->pai == arvore->nulo)
    arvore->raiz = y; // y se torna a nova raiz da árvore
  else if (x == x->pai->esquerda)
    x->pai->esquerda = y;
  else
    x->pai->direita = y;
  
  y->esquerda = x;
  x->pai = y;
}

// Função auxiliar para rotacionar à direita
void rotacaoDireita(ARVORE_RUBRO_NEGRA* arvore, NO* y) {
  NO* x = y->esquerda;
  y->esquerda = x->direita;

  // Verifica se x tem filho direito
  if (x->direita != arvore->nulo)
    x->direita->pai = y;
  
  x->pai = y->pai;
  // Verifica se o pivô tem pai
  if (y->pai == arvore->nulo)
    arvore->raiz = x; // x se torna a nova raiz da árvore
  else if (y == y->pai->esquerda)
    y->pai->esquerda = x;
  else
    y->pai->direita = x;
  
  x->direita = y;
  y->pai = x;
}

// Função para corrigir a inserção
void corrigirInsercao(ARVORE_RUBRO_NEGRA* arvore, NO* novo) {
  NO* pai = NULL;
  NO* avo = NULL;

  while (novo != arvore->raiz && novo->cor == VERMELHO && novo->pai->cor == VERMELHO) {
    pai = novo->pai;
    avo = novo->pai->pai;

    // Caso 1: O pai de `novo` é o filho esquerdo do avô
    if (pai == avo->esquerda) {
      NO* tio = avo->direita;

      // Caso 1.1: O tio de `novo` é vermelho - recolorir
      if (/*tio != NULL &&*/ tio->cor == VERMELHO) {
        avo->cor = VERMELHO;
        pai->cor = PRETO;
        tio->cor = PRETO;
        novo = avo; // Continue a verificação com o avô
      } else {
        // Caso 1.2: `novo` é um filho direito - rotação à esquerda
        if (novo == pai->direita) {
          rotacaoEsquerda(arvore, pai);
          novo = pai;
          pai = novo->pai;
        }

        // Caso 1.3: `novo` é um filho esquerdo - rotação à direita
        rotacaoDireita(arvore, avo);
        pai->cor = PRETO;
        avo->cor = VERMELHO;
        novo = pai;
      }
    } else { 
      NO* tio = avo->esquerda;

      // Caso 2.1: O tio de 'novo' é vermelho - recolorir
      if (/*tio != NULL &&*/ tio->cor == VERMELHO){
        avo->cor = VERMELHO;
        pai->cor = PRETO;
        tio->cor = PRETO;
        novo = avo; // Continue a verificação com o avô
      } else {
        // Caso 2.2: 'novo' é um filho esquerda - rotação à direita
        if (novo == pai->esquerda){
          rotacaoDireita(arvore, pai);
          novo = pai;
          pai = novo->pai;
        }
        // Caso 2.3: 'novo' é um filho direito - rotação à esquerda
        rotacaoEsquerda(arvore, avo);
        pai->cor = PRETO;
        avo->cor = VERMELHO;
        novo = pai;
      }
    }
  }

  arvore->raiz->cor = PRETO; // A raiz deve ser sempre preta
}

// Função para inserir um valor na árvore
void inserir(ARVORE_RUBRO_NEGRA* arvore, ITEM chave) {
  NO* novo = criarNo(arvore, chave);

  // Inserção padrão de uma árvore binária de busca
  NO* pai = arvore->nulo;
  NO* atual = arvore->raiz;
  while (atual != arvore->nulo) {
    pai = atual;
    if (chave < atual->chave) {
      atual = atual->esquerda;
    } else if (chave > atual->chave) {
      atual = atual->direita;
    } else {
      // Valor já existe na árvore
      free(novo);
      return;
    }
  }
  novo->pai = pai;

  if (pai == arvore->nulo) {
    arvore->raiz = novo; // Árvore vazia
  } else if (chave < pai->chave) {
    pai->esquerda = novo;
  } else {
    pai->direita = novo;
  }

  corrigirInsercao(arvore, novo);
}

//Para lidar com a violação, vamos considerar que a propriedade número 5 da arvore rubro negra não foi violada, e que o nó x ganhou uma nova camada de "preto", assim essa propriedade não será ferida, focando nas outras violações do código
void corrigirRemocao(ARVORE_RUBRO_NEGRA* arvore, NO* x){
	NO *w;	

	while(x != arvore->raiz && x->cor == PRETO){
//vamos mover o preto extra de x ate que x vire a raiz, ou x seja rubro e negro ao mesmo tempo

		if(x == x->pai->esquerda){ //Checa se x é o filho esquerdo de seu pai
			w = x->pai->direita;
//Caso 1: checa se w(irmão de x) é vermelho
			if(w->cor == VERMELHO){
				w->cor = PRETO;
				x->pai->cor = VERMELHO;
				rotacaoEsquerda(arvore, x->pai);
				w = x->pai->direita;
			}
//Caso 2: checa se w é preto e ambos seus filhos são pretos
			if(w->esquerda->cor == PRETO && w->direita->cor == PRETO){
				w->cor = VERMELHO;
				x->pai->cor = PRETO;
				x = x->pai;
			}
			else{
//Caso 3: w é preto, filho esquerdo é vermelho, filho direito é preto
				if(w->direita->cor == PRETO){
					w->cor = VERMELHO;
					w->esquerda->cor = PRETO;
					rotacaoDireita(arvore, w);
					w = x->pai->direita;
				}
//Caso 4: filho esquedo é preto, filho direito é vermelho
				w->cor = x->pai->cor;
				x->pai->cor = PRETO;
				x->direita->cor = PRETO;
				rotacaoEsquerda(arvore, x->pai);
				x = arvore->raiz;		

			}

		}
		else{ //X é o filho direito de seu pai(o código é simétrico ao anterior)
			w = x->pai->esquerda;

			if(w->cor == VERMELHO){
				w->cor = PRETO;
				x->pai->cor = PRETO;
				rotacaoDireita(arvore, x->pai);
				w = x->pai->esquerda;
			}

			if(w->esquerda->cor == PRETO && w->direita->cor == PRETO){
				w->cor = VERMELHO;
				x->pai->cor = PRETO;
				x = x->pai;
			}
			else{

				if(w->esquerda->cor == PRETO){
					w->cor = VERMELHO;
					w->direita->cor = PRETO;
					rotacaoEsquerda(arvore, w);
					w = x->pai->esquerda;
				}

				w->cor = x->pai->cor;
				x->pai->cor = PRETO;
				w->esquerda->cor = PRETO;
				rotacaoDireita(arvore, x->pai);
				x = arvore->raiz;

			}
		}

	}

	x->cor = PRETO;
}

// retorna o nó com a menor chave a partir de x
NO* minimo(ARVORE_RUBRO_NEGRA *arvore, NO* x){
	while(x->esquerda != arvore->nulo){
		x = x->esquerda;
	}
	return x;
}

// substitui o nó u pelo nó v
void substituir(ARVORE_RUBRO_NEGRA* arvore, NO* u, NO* v){
	if(u->pai == arvore->nulo){
		arvore->raiz = v;
	}
	else if(u == u->pai->esquerda){
		u->pai->esquerda = v;
	}
	else{
		u->pai->direita = v;
	}

	v->pai = u->pai;
}

// Função para buscar um nó na árvore pela sua chave
NO* buscarNo(ARVORE_RUBRO_NEGRA* arvore, ITEM chave){
	NO* noAtual = arvore->raiz;

  // Atualiza noAtual até que seja nulo ou a chave seja encontrada
	while(noAtual != arvore->nulo && noAtual->chave != chave)
		if(chave < noAtual->chave)
      //Continua a busca na subárvore esquerda
			noAtual = noAtual->esquerda;
		else
      // Continua a busca na subárvore direita
			noAtual = noAtual->direita;

  // No caso de uma busca sem sucesso, retorna o nó sentinela
  // Caso a busca seja bem sucedida, retorna o nó desejado
	return noAtual;
}

//A função remover é baseada no mesmo mecanismo da arvore binária de busca
void remover(ARVORE_RUBRO_NEGRA* arvore, ITEM chave){
	NO *z, *y, *x;
	COR corInicialY;

  // Buscando o nó a ser removido na árvore pela sua chave
  z = buscarNo(arvore, chave);

  // Garante a remoção apenas para valores existentes
  if(z == arvore->nulo) {
    printf("O valor [%d] não foi encontrado.\n", chave);
    return;
  }
    
	y = z;
	corInicialY = y->cor; //A cor original de y é salva
//Caso 1: z não possui filho esquerdo
	if(z->esquerda == arvore->nulo){
		x = z->direita;
		substituir(arvore, z, z->direita);
    free(z);
	}
//Caso 2: z não possui filho direito 
	else if(z->direita == arvore->nulo){
		x = z->esquerda;
		substituir(arvore, z, z->esquerda);
    free(z);
	}
//Caso 3: z possui ambos os filhos
	else{
    // encontra o sucessor imediato
		y = minimo(arvore, z->direita);
		corInicialY = y->cor;

		x = y->direita;

		if(y->pai == z){
			x->pai = y;
		}
		else{
			substituir(arvore, y, y->direita);
			y->direita = z->direita;
			y->direita->pai = y;
		}

		substituir(arvore, z, y);
		y->esquerda = z->esquerda;
		y->esquerda->pai = y;
		y->cor = z->cor;
    free(z);
	}
//A cor original de y é chamada para conferir se as propriedades da árvore foram feridas, se a cor original de y for preta é chamada a função de correção
	if(corInicialY == PRETO){
		corrigirRemocao(arvore, x);
	}
}

// Função para imprimir a árvore em ordem
void imprimirEmOrdem(ARVORE_RUBRO_NEGRA* arvore, NO* no) {
    if (no != arvore->nulo) {
        imprimirEmOrdem(arvore, no->esquerda);
        printf("(%d|%s) ", no->chave, (no->cor == VERMELHO) ? "V" : "P");
        imprimirEmOrdem(arvore, no->direita);
    }
}