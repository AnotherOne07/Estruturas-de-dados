#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "FilaEnc.h"


// Imprime na tela o status da fila
void imprimirStatus(FILA *f)
{
    printf("Tamanho = %d\n", tamanho(f));
	exibir(f);
	printf("\n");
}


// Testa a insercao de valores na fila
void testarInserir(FILA *f)
{
    printf("=> Teste de Inserir\n");
    int qtd;
    printf("Quantos itens deseja guardar na fila? ");
    scanf("%d", &qtd);

    ITEM item;
	for (int i = 0; i < qtd; i++)
    {
        printf("Digite o valor para a posicao [%d]: ", i);
        scanf("%d", &item);
        inserir(item, f);
	}

	imprimirStatus(f);
}


// Testa o acesso a elementos da fila
void testarEnesimo(FILA *f)
{
    // Testa o acesso a cada elemento da fila
    printf("=> Teste de Enesimo\n");
    // Testa a busca por uma posicao existente
    printf("Digite a posicao que deseja acessar (ou -1 para sair): ");
    int p;
    scanf("%d", &p);
    while (p != -1)
    {
        ITEM item = enesimo(p, f);
        printf("Achou na posicao[%d] o valor: %d\n", p, item);
        // Leitura da proxima posicao a ser acessada
        printf("Digite a posicao que deseja acessar (ou -1 para sair): ");
        scanf("%d", &p);
    }

}


// Testa o acesso a frente e retirada de valores
void testarFrenteRetirar(FILA *f)
{
    printf("=> Teste da Frente\n");
    
    if (vazia(f)) 
    {
        printf("Fila vazia. Nada a retirar...\n");
        return;
    } else {
        printf("Fila tem %d valores\n", tamanho(f));
    } 
    
    ITEM i;
    if (frente(&i, f))
       printf("Valor contido na frente da Fila: %d\n", i);
    else
       printf("Erro: Deveria haver um valor na frente da fila."); 
    
    while (!vazia(f))
    {
        ITEM item;
        if (retirar(&item, f))
           printf("Retirado um valor da frente da fila com sucesso\n");
        else
           printf("Erro na retirada da frente da fila\n");

        // Mostra o valor retirado da fila
        printf("Valor retirado da frente da fila: %d\n", item);
        
        imprimirStatus(f);
    }
}
/////////////////////////////////////////////////////

int main(){
	FILA f;
	
	inicializar(&f);
    testarInserir(&f);
    testarEnesimo(&f);   
    testarFrenteRetirar(&f);

    destruir(&f);
    imprimirStatus(&f);
        
    getchar();
	return 0;
}