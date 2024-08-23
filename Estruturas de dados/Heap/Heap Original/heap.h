#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
  int* itens;
  int tamanho;
  int capacidade;
} HEAP;


// inicializa a heap com capacidade max = 15, e todos os elementos nulos;
void inicializar(HEAP *h);



// considera-se que h já é um heap quase completamente correto, pois apenas o elemento do indice informado pode estar quebrando a corretude da estrutura. A função vai corrigir a questão da prioridade comparando o elemento do indice com os filhos, olhando sempre para o filho de maior prioridade, repetindo o processo até que a prioridade esteja sendo respeitada:
void corrigeDescendo(HEAP *h, int indice);


// considera-se que h já é uma heap quase completamente correto, pois apenas o elemento do indice informado pode estar quebrando a corretude da estrutura. A função vai corrigir a questão da prioridade comparando o elemento do indice com o pai repetidamente até o momento em que a prioridade for respeitada:
void corrigeSubindo(HEAP *h, int indice);


// usada para corrigir as questões de prioriade de uma heap que pode ter sido estragada:
void corrigeHeap(HEAP *h);


// função para auxiliar na heapsort; vai ser usada parar trocar os valores de prioridade pelos valores dos itens, assim, poderemos ordenar pelos valores em si, e não por suas prioridades:
void auxSort(HEAP *h);


// função auxiliar para a heapsort que vai ser usada no final, para retormar os valores normais de itens e prioridades:
void auxSort2(HEAP *h);


// ordena a heap pelo valor dos itens:
void heapSort(HEAP *h);


// retorna true se achar o elemento na lista e false se não achar
bool buscar(HEAP *h, int valor);


// vai inserir o item na árvore na primeira posição livre, ou seja, como uma folha, e depois vai ajustar esse elemento para respeitar as prioridades da árvore. Retorna true se a inserção der certo, e false caso contrário:
bool inserir(int valor, HEAP *h);


// vai remover o elemento de maior prioridade da árvore, da seguinte forma: o elemento do nó raiz vai ser removido e dar o lugar ao elemento do último nó da árvore, que vem de uma folha. Então fazemos uma reordenação para que o elemento que foi posto como nó raiz vá para o seu devido lugar, respeitando as prioridades da árvore. Retorna true se a remoção der certo, e false caso contrário:
bool remover(HEAP *h);


// imprime cada elemento da árvore, com sua prioridade informada ao lado, entre parênteses:
void imprimir(HEAP *h);


// Altera o elemento de um nó específico da heap, e depois faz os ajustes necessários para respeitar as prioridades da árvore. Retorna true se a alteração ocorrer corretamente e false caso contrário:
bool alterar(HEAP *h, int indice, int valor);


// cada item que antes havia na árvore é resetado, e o tamanho da árvore passa a ser 0:
void limpar(HEAP *h);

// função criada para destruir a heap ao sair da execução do programa, ou seja, para liberar a memória:
void destruir(HEAP *h);