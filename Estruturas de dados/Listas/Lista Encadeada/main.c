#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "ListaEnc.h"

// Imprime na tela o status da lista
void imprimirStatus(LISTA *l)
{
    printf("Tamanho = %d\n", tamanho(l));
	exibirLista(l);
	printf("\n");
}

// Testa a insercao de valores na lista
void testarInserir(LISTA *l)
{
    printf("=> Teste de Inserir\n");
    int qtd;
    printf("Quantos itens deseja guardar na lista? ");
    scanf("%d", &qtd);

    ITEM item;
	for (int i = 1; i <= qtd; i++)
    {
        printf("Digite o valor %d/%d: ", i, qtd);
        scanf("%d", &item);
        inserir(item, l);
	}

	imprimirStatus(l);
}

// Testa a insercao de valores na lista escolhendo a posicao
void testarInserirNaPos(LISTA *l)
{
    printf("=> Teste de InserirNaPos\n");
    int qtd;
    printf("Quantos itens deseja inserir na lista? ");
    scanf("%d", &qtd);

	ITEM item;
	for (int i = 0; i < qtd; i++)
    {
        printf("Digite a posicao de insercao (de 0 a %d): ", tamanho(l));
        int p;
        scanf("%d", &p);
  
        printf("Digite o valor para a posicao [%d]: ", p);
        scanf("%d", &item);
        if (inserirNaPos(item, p, l))
            printf("Insercao com sucesso\n");
        else
            printf("Erro na insercao\n");

        imprimirStatus(l);
	}

}
// Testa a busca de valores na lista
void testarBuscar(LISTA *l)
{
   // Testa a busca por um valor existente
    printf("=> Teste de Busca\n");
    printf("Digite o valor que deseja buscar: ");
    ITEM item;
    scanf("%d", &item);
    int pos = buscar(item, l); 
    if (pos >= 0)
        printf("Achou na posicao: %d\n", pos);
    else
        printf("Nao achou o item na lista\n");

    // Testa a busca por uma posicao existente
    printf("Digite a posicao que deseja acessar (ou -1 para sair): ");
    int p;
    scanf("%d", &p);
    while (p != -1)
    {
        ITEM item = enesimo(p, l);
        printf("Achou na posicao[%d] o valor: %d\n", p, item);
        // Leitura da proxima posicao a ser acessada
        printf("Digite a posicao que deseja acessar (ou -1 para sair): ");
        scanf("%d", &p);
    }

}

// Testa a alteracao de um valor numa posicao
void testarAlterar(LISTA *l)
{
    printf("=> Teste da Alteracao\n");
    int p;
    printf("Digite a posicao que deseja alterar (ou -1 para sair): ");
    scanf("%d", &p);
    while (p != -1)
    {
        // Leitura do novo valor
        printf("Digite o NOVO valor para a posicao [%d]: ", p);
        ITEM item;
        scanf("%d", &item);
        if (alterar(item, p, l))
           printf("Alterou com sucesso\n");
        else
           printf("Erro na alteracao\n");

        imprimirStatus(l);

        // Leitura da proxima posicao a ser acessada
        printf("Digite a posicao que deseja alterar (ou -1 para sair): ");
        scanf("%d", &p);
    }
}

void testarRemoverNaPos(LISTA *l){
  printf("=> Teste da Alteracao\n");
  int i;
  ITEM item;
  printf("Insira a posicao que deseja remover : ");
  scanf("%d", &i);
  removerDaPos(&item, i, l);
  printf("ITEM REMOVIDO : %d\n", item);
  imprimirStatus(l);
}

void testarClonar(LISTA *l)
{
  printf("=> Teste de Clonagem de Lista \n");
}

void testarInserirOrd(LISTA *l){
  printf("=> Teste de Lista Encadeda Ordenada\n");
  int qtd;
  printf("Quantos itens deseja guardar na lista? ");
  scanf("%d", &qtd);

  ITEM item;
	for (int i = 1; i <= qtd; i++)
    {
        printf("Digite o valor %d/%d: ", i, qtd);
        scanf("%d", &item);
        inserirOrd(item, l);
	 }

	imprimirStatus(l);
}

void testarIntersecao(LISTA* A, LISTA* B, LISTA* I)
{
  intersecao(A, B, I);
  imprimirStatus(I);
}


/////////////////////////////////////////////////////

int main(){
	LISTA A, B, I;
	
	inicializar(&A);
  inicializar(&B);
  inicializar(&I);
    testarInserirOrd(&A);
    testarInserirOrd(&B);
    //testarClonar(&l);
    testarIntersecao(&A, &B, &I);
    //imprimirStatus(&l);
    //testarInserir(&l);
    //testarInserirNaPos(&l);
    //imprimirStatus(&A);
    /*
    testarInserir(&l);
    testarClonar(&l);
    testarRemoverNaPos(&l);
    testarInserirNaPos(&l);
    testarBuscar(&l);   
    testarAlterar(&l);
    destruir(&l);
    imprimirStatus(&l);
    */
        
    getchar();
	return 0;
}