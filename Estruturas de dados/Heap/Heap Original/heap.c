#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "heap.h"



void inicializar(HEAP *h) {
  h->capacidade = 15;
  h->itens = (int *) calloc(h->capacidade, sizeof(int));
  if(!h->itens) {
    printf("Inicializacao nao foi efetuada!");
  }
  h->tamanho = 0;
}



void corrigeDescendo(HEAP *h, int indice) {
  if(h->tamanho == 0 || h->tamanho == 1) {
    return;
  }
  int aux;
  int i = indice; // usado para percorrer os índices dos nós da árvore, em que i vai indicar o nó atual
  
  while(true) {
    if(2*i+2 < h->tamanho && h->itens[i] < h->itens[2*i+2] && h->itens[2*i+2] > h->itens[2*i+1]) { // se o filho 2 é maior que o filho 1, e se for maior que o pai, basta trocar os valores do pai com o filho 2 e continuar checando
      aux = h->itens[i];
      h->itens[i] = h->itens[2*i+2];
      h->itens[2*i+2] = aux;
      i = 2*i+2;
    } else if(2*i+1 < h->tamanho && h->itens[i] < h->itens[2*i+1]) { // se o filho 1 é maior, basta trocar os valores do pai com o filho 1 e continuar checando
      aux = h->itens[i];
      h->itens[i] = h->itens[2*i+1];
      h->itens[2*i+1] = aux;
      i = 2*i+1;
    }
    else
      break;
  }
}



void corrigeSubindo(HEAP *h, int indice) {
  if(h->tamanho == 0 || h->tamanho == 1 || indice == 0) {
    return;
  }
  int aux;
  int i = indice;
  bool maiorQpai;
  while(i > 0) { // até chegar no nó raiz, vai comparar o elemento do momento com o seu pai, desde que a prioridade ainda não esteja correta
    maiorQpai = h->itens[i] > h->itens[(i-1)/2]; // verificando se a prio do no atual é maior que a do pai dele
    if(maiorQpai) {
      aux = h->itens[i];
      h->itens[i] = h->itens[(i-1)/2];
      h->itens[(i-1)/2] = aux;
      i = (i-1)/2;
    } else
        return;
  }
}



bool buscar(HEAP *h, int valor) {
  for(int i = 0; i < h->tamanho; i++) {
    if(h->itens[i] == valor)
      return true;
  }
  return false;
}



bool inserir(int valor, HEAP *h) {
  if(buscar(h, valor)) //se um elemento com a mesma prioridade e o mesmo valor for achado na árvore, não será feita inserção
    return false;
  
  if(h->tamanho == h->capacidade) { // se o array já estiver lotado, fará a realocação para inserir
    h->capacidade *= 2;
    h->itens = (int *) realloc(h->itens, h->capacidade*sizeof(int));
    if(!h->itens) { // se a alocação não deu certo, não será feita a inserção
      printf("Realocacao falhou!");
      return false;
    } 
  }
  // Agora, basta inserir o item na heap e depois corrigir a posição dele de acordo com a sua prioridade:
  h->itens[h->tamanho] = valor; // o último espaço livre vai receber o conteúdo de item
  h->tamanho++; // devemos aumentar o tamanho da heap
  corrigeSubindo(h, h->tamanho-1); // como fizemos h->tamanho++, a posição em que o item foi inserido é h->tamanho-1,
  // e vamos corrigir subindo para manter as regras de prioridae na heap. Como inserimos na última folha, basta aplicar essa função
  return true;
}



bool remover(HEAP *h) {
  if(h->tamanho == 0) {
    return false;
  }
  h->itens[0] = h->itens[(h->tamanho)-1]; // o nó raiz vai receber o item contido na última folha da heap
  h->tamanho--; // diminuímos o tamanho da heap, pois estamos removendo, e o nó folha que doou seu conteúdo para a raiz passa a ser inválido
  corrigeDescendo(h, 0); // fazemos o corrigeDescendo a partir da raiz para corrigir as questões de prioridade
  return true;
}



void imprimir(HEAP *h) {
    if(h->tamanho == 0) {
      printf("\n\nNada para imprimir ¯_(ツ)_/¯\n\n");
      return;
    }
    printf("\n----------HEAP----------\n");
    for (int i = 0; i < h->tamanho; i++) {
        printf("%d ", h->itens[i]);
    }
    printf("\n----------FIM-----------\n");
}



bool alterar(HEAP *h, int indice, int valor) {
  if(h->tamanho == 0 || indice < 0)
    return false;
  
  if(valor > h->itens[indice]) { // verifica se a prioridade do item a ser inserido é maior(numericamente menor) do que a prio do item do indice informado
    // se a prioridade for maior, significa que existe a possibilidade dessa prioridade ser maior que a do pai dele:
    h->itens[indice] = valor; // atribuindo o conteúdo de item
    corrigeSubindo(h, indice);
    return true;
  }
  if(valor < h->itens[indice]) { // verifica se a prioridade do item a ser inserido é menor(numericamente maior) do que a prio do item do indice informado
    // se a prioridade for menor, significa que existe a possibilidade dessa prioridade ser menor que a de um dos filhos dele:
    h->itens[indice] = valor;
    corrigeDescendo(h, indice);
    return true;
  }
  return false; // aqui, o valor a ser inserido vai ser igual ao que já estava no índice informado pelo usuário, pois terá passado pelos dois ifs. Não aceitaremos
  // esse caso.
}



void corrigeHeap(HEAP *h) { // usada para corrigir as questões de prioriade de uma heap que pode ter sido estragada
  int ultimoNo = h->tamanho-1; // É o índice do último nó válido do array
  if(h->tamanho == 1 || h->tamanho == 0)
    return;
  for(int i = (ultimoNo-1)/2; i >= 0; i--) {
    corrigeDescendo(h, i); // vai corrigir cada parte da heap
  }
}



void heapSort(HEAP *h) {
  int aux;
  corrigeHeap(h); // não sabemos se foi passada uma h correta, então fazemos a correção
  int ultimoIndice = h->tamanho - 1;
  // o próximo laço for ordena crescentemente o array
  for(int i = ultimoIndice; i > 0; i--) {
    if(i == 1) {
      if(h->itens[0] > h->itens[i]) {
        aux = h->itens[0];
        h->itens[0] = h->itens[i];
        h->itens[i] = aux;
        break;
      } else
        break;
    }
    aux = h->itens[0];
    h->itens[0] = h->itens[i];
    h->itens[i] = aux;
    h->tamanho--;
    corrigeHeap(h);
  }
  h->tamanho = ultimoIndice + 1; // retomamos o tamanho original
}



void limpar(HEAP *h) {
  for(int i = 0; i < h->tamanho; i++) {
    h->itens[i] = 0;
  }
  h->tamanho = 0;
}

void destruir(HEAP *h) {
  limpar(h);
  free(h->itens);
  h->itens = NULL;
  h->capacidade = 0;
}