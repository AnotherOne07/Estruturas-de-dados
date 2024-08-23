#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "PilhaEnc.h"


// Imprime na tela o status da pilha
void imprimirStatus(PILHA *p)
{
    printf("Tamanho = %d\n", tamanho(p));
	exibir(p);
	printf("\n");
}


// Testa empilhar valores na pilha
void testarEmpilhar(PILHA *p)
{
    printf("=> Teste de Empilhar\n");
    int qtd;
    printf("Quantos itens deseja guardar na pilha? ");
    scanf("%d", &qtd);

    ITEM item;
	for (int i = 0; i < qtd; i++)
    {
        printf("Digite o proximo valor a empilhar [%d/%d]: ", i+1, qtd);
        scanf("%d", &item);
        empilhar(item, p);
	}

	imprimirStatus(p);
}


// Testa o acesso a elementos da pilha
void testarEnesimo(PILHA *pilha)
{
    // Testa o acesso a cada elemento da pilha
    printf("=> Teste de Enesimo\n");
    // Testa a busca por uma posicao existente
    printf("Digite a posicao que deseja acessar (ou -1 para sair): ");
    int p;
    scanf("%d", &p);
    while (p != -1)
    {
        ITEM item = enesimo(p, pilha);
        printf("Achou na posicao[%d] o valor: %d\n", p, item);
        // Leitura da proxima posicao a ser acessada
        printf("Digite a posicao que deseja acessar (ou -1 para sair): ");
        scanf("%d", &p);
    }

}


// Testa o desempilhamento de valores
void testarDesempilhar(PILHA *p)
{
    printf("=> Teste do Topo\n");
    
    if (vazia(p)) 
    {
        printf("Pilha vazia. Nada a desempilhar...\n");
        return;
    } else {
        printf("Pilha tem %d valores\n", tamanho(p));
    } 
    
    ITEM i;
    if (topo(&i, p))
       printf("Valor contido no topo da Pilha: %d\n", i);
    else
       printf("Erro: Deveria haver um valor no topo da Pilha."); 
    
    while (!vazia(p))
    {
        ITEM item;
        if (desempilhar(&item, p))
           printf("Retirado um valor do topo da pilha com sucesso\n");
        else
           printf("Erro na retirada do topo da pilha\n");

        // Mostra o valor retirado da pilha
        printf("Valor retirado do topo da pilha: %d\n", item);
        
        imprimirStatus(p);
    }
}

/////////////////////////////////////////////////////

int main(){
	PILHA p;
	
	inicializar(&p);
    
    testarEmpilhar(&p);
    testarEnesimo(&p);
    testarDesempilhar(&p);

    destruir(&p);
    imprimirStatus(&p);
        
    getchar();
	return 0;
}