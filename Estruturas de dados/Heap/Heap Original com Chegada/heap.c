#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "heap.h"



void inicializar(HEAP *h) {
  h->capacidade = 15;
  h->chegada = 0;
  h->itens = (ITEM *) calloc(h->capacidade, sizeof(ITEM));
  if(!h->itens) {
    printf("Inicializacao nao foi efetuada!");
  }
  h->tamanho = 0;
}



void corrigeDescendo(HEAP *h, int indice) {
    int filho_esq, filho_dir, filho_maior;
    
    while (1) {
        filho_esq = 2 * indice + 1;
        filho_dir = 2 * indice + 2;
        filho_maior = indice;

        // os dois próximos if´s pegam o índice do elemento que deve ficar na posição do pai (seja um dos filhos ou o próprio pai)

      // confere primeiro se o filho da esquerda exisite; se existir, vamos analisar prioridade e chegada para saber se havrá a troca de índice;
        if (filho_esq < h->tamanho && (h->itens[filho_esq].prio > h->itens[filho_maior].prio ||
            (h->itens[filho_esq].prio == h->itens[filho_maior].prio &&
             h->itens[filho_esq].chegada < h->itens[filho_maior].chegada))) {
            filho_maior = filho_esq;
        }

      // confere primeiro se o filho da esquerda exisite; se existir, vamos analisar prioridade e chegada para saber se havrá a troca de índice;
        if (filho_dir < h->tamanho && (h->itens[filho_dir].prio > h->itens[filho_maior].prio ||
            (h->itens[filho_dir].prio == h->itens[filho_maior].prio &&
             h->itens[filho_dir].chegada < h->itens[filho_maior].chegada))) {
            filho_maior = filho_dir;
        }
        
        if (filho_maior == indice) {
            break; // A heap está correta agora.
        }
        
        // Aqui, trocamos os elementos.
        ITEM aux = h->itens[indice];
        h->itens[indice] = h->itens[filho_maior];
        h->itens[filho_maior] = aux;
        
        indice = filho_maior; // Continuamos verificando com o filho maior.
    }
}




void corrigeSubindo(HEAP *h, int indice) {
  ITEM aux;
  int i = indice;
  bool maiorQpai;
  while(i > 0) { // até chegar no nó raiz, vai comparar o elemento do momento com o seu pai, desde que a prioridade ainda não esteja correta
    maiorQpai = h->itens[i].prio > h->itens[(i-1)/2].prio; // verificando se a prio do no atual é maior que a do pai dele
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
    if(h->itens[i].valor == valor)
      return true;
  }
  return false;
}



bool inserir(int valor, int prio, HEAP *h) {
  if(buscar(h, valor)) //se um elemento com a mesma prioridade e o mesmo valor for achado na árvore, não será feita inserção
    return false;

  if(prio < 0)
    return false;
  
  ITEM* item = (ITEM *) malloc(sizeof(ITEM)); // aloca espaço de memória para um novo item (nó)
  if(!item) // verifica se a alocação deu certo; se não deu, não será feito mais nada
    return false;
  item->prio = prio; // aqui, estamos colocando os dados informados no novo item
  item->valor = valor;
  item->chegada = h->chegada;
  h->chegada++;
  
  if(h->tamanho == h->capacidade) { // se o array já estiver lotado, fará a realocação para inserir
    h->capacidade *= 2;
    h->itens = (ITEM *) realloc(h->itens, h->capacidade*sizeof(ITEM));
    if(!h->itens) { // se a alocação não deu certo, não será feita a inserção
      printf("Realocacao falhou!");
      return false;
    }
  }
  // Agora, basta inserir o item na heap e depois corrigir a posição dele de acordo com a sua prioridade:
  h->itens[h->tamanho] = *item; // o último espaço livre vai receber o conteúdo de item
  h->tamanho++; // devemos aumentar o tamanho da heap
  corrigeSubindo(h, h->tamanho-1); // como fizemos h->tamanho++, a posição em que o item foi inserido é h->tamanho-1
  return true;
}



bool remover(HEAP *h) {
  if(h->tamanho == 0) {
    printf("Nao ha o que remover");
    return false;
  }
  h->itens[0] = h->itens[(h->tamanho)-1]; // o nó raiz vai receber o item contido na última folha da heap
  h->tamanho--; // diminuímos o tamanho da heap, pois estamos removendo, e o nó folha que doou seu conteúdo para a raiz passa a ser inválido
  corrigeDescendo(h, 0); // fazemos o corrigeDescendo a partir da raiz para corrigir as questões de prioridade
  return true;
}



void imprimir(HEAP *h) {
    if(h->tamanho == 0) {
      printf("\n\nNada para imprimir\n\n");
      return;
    }
    printf("\n----------HEAP----------\n");
    for (int i = 0; i < h->tamanho; i++) {
        printf("%d(%d)(%d) ", h->itens[i].valor, h->itens[i].prio, h->itens[i].chegada);
    }
    printf("\n----------FIM-----------\n");
}



bool alterar(HEAP *h, int indice, int valor, int prio) {
  if(h->tamanho == 0 || indice < 0)
    return false;
  // criando um novo item (nó) que contenha as informações passadas:
  ITEM* item = (ITEM *) malloc(sizeof(ITEM));
  if(!item) // verifica se a alocação deu certo
    return false;
  item->prio = prio;
  item->valor = valor;
  item->chegada = h->itens[indice].chegada; // vamos atribuir a mesma chegada do item que estava no índice passado
  if(item->prio > h->itens[indice].prio) { // verifica se a prioridade do item a ser inserido é maior(numericamente menor) do que a prio do item do indice informado
    // se a prioridade for maior, significa que existe a possibilidade dessa prioridade ser maior que a do pai dele:
    h->itens[indice] = *item; // atribuindo o conteúdo de item
    corrigeSubindo(h, indice);
    return true;
  }
  if(item->prio < h->itens[indice].prio) { // verifica se a prioridade do item a ser inserido é menor(numericamente maior) do que a prio do item do indice informado
    // se a prioridade for menor, significa que existe a possibilidade dessa prioridade ser menor que a de um dos filhos dele:
    h->itens[indice] = *item;
    corrigeDescendo(h, indice);
    return true;
  }
  if(item->valor == h->itens[indice].valor)
    return false; // aqui, o usuário tentou inserir um valor já existente na árvore, com prio e valor iguais, pois passou dos dois if's
  h->itens[indice] = *item; // Aqui, o usuário alterou um nó de uma árvore por outro de igual prioridade. Basta alterar diretamente
  return true;
}



void corrigeHeap(HEAP *h) { // usada para corrigir as questões de prioriade de uma heap que pode ter sido estragada
  int ultimoNo = h->tamanho-1; // É o índice do último nó válido do array
  if(h->tamanho == 1 || h->tamanho == 0)
    return;
  for(int i = (ultimoNo-1)/2; i >= 0; i--) {
    corrigeDescendo(h, i); // vai corrigir cada parte da heap, para todos os pais
  }
}



void auxSort(HEAP *h) { // função auxiliar para atribuir os valores dos nós como prioridades, para ordenar pelo valor, e não pela prioridade 
  int aux;
  for(int i = 0; i < h->tamanho; i++) {
    aux = h->itens[i].prio;
    h->itens[i].prio = h->itens[i].valor; 
    h->itens[i].valor = aux;
  }
}

void auxSort2(HEAP *h) { // retoma os valores originais dos campos dos itens
  int aux;
  for(int i = 0; i < h->tamanho; i++) {
    aux = h->itens[i].valor;
    h->itens[i].valor = h->itens[i].prio;
    h->itens[i].prio = aux;
  }
}



void heapSort(HEAP *h) {
  ITEM aux;
  int ultimoIndice = h->tamanho - 1;
  corrigeHeap(h); // não sabemos se foi passada uma h correta, então corrigimos antes
  auxSort(h); // primeiro, troca as prioridades com os valores dos itens (para que possamos ordenar pelos valores, em si, e não pelas prioridades)
  corrigeHeap(h); // agora, como as prioridades, foram trocadas pelos valores dos itens, precisamos retomar as propriedades de heap

  // no próximo laço for, a gente faz a ordenação
  for(int i = ultimoIndice; i > 0; i--) {
    if(i == 1) {
      if(h->itens[0].prio > h->itens[i].prio) {
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
  h->tamanho = ultimoIndice + 1; // retomamos ao tamanho original
  auxSort2(h); // fazemos com que os valores dos itens e as prioridades sejam trocados novamente, agora com os valores ordenados
}



void limpar(HEAP *h) {
  for(int i = 0; i < h->tamanho; i++) {
    h->itens[i].prio = 0;
    h->itens[i].valor = 0;
  }
  h->tamanho = 0;
  h->chegada = 0;
}

void destruir(HEAP *h) {
  limpar(h);
  free(h->itens);
  h->itens = NULL;
  h->capacidade = 0;
}