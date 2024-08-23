#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#include "ListaSeqOrd.h"

// Imprime na tela o status da lista
void imprimirStatus(LISTA *l)
{
    printf("Tamanho = %ld\n", tamanho(l));
	exibirLista(l);
	printf("\n");
}

// Testa a insercao de valores na lista
void testarInserir(LISTA *l)
{
    printf("=> Teste de Inserir\n");
    long qtd;
    printf("Quantos itens deseja guardar na lista? ");
    scanf("%ld", &qtd);

    ITEM item;
    for (long i = 1; i <= qtd; i++)
    {
        printf("Digite o valor %ld/%ld: ", i, qtd);
        scanf("%d", &item);
        inserir(item, l);
	}

	imprimirStatus(l);
}


// Testa a insercao de valores na lista escolhendo a posicao
void testarInserirVarios(LISTA *l)
{ 
    
    printf("=> Teste de InserirVarios\n");
    long qtd;
    printf("Quantos itens aleatorios deseja inserir na lista? ");
    scanf("%ld", &qtd);

	ITEM item;
    long sucessos = 0;
    long erros = 0;

    // Inicia a contagem de tempo
    time_t inicio = time(NULL);
	for (long i = 0; i < qtd; i++)
    {
        item = rand();
        if (inserir(item, l))
            sucessos += 1;
        else
            erros += 1;
	}
    // Finaliza a contagem de tempo
    time_t fim = time(NULL);
    // Calcula o tempo decorrido
    double tempo_gasto = (double)(fim - inicio);
    // Tempo medio por insercao
    double tempo_medio = 1000.0  * tempo_gasto / qtd;

    printf("Insercoes com sucesso: %ld\n", sucessos);
    printf("Insercoes com erro: %ld\n", erros);
    printf("Tempo total das insercoes %f segundos\n", tempo_gasto);
    printf("Tempo medio por insercao %f milisegundos\n", tempo_medio);
}



// Testa a busca de valores na lista
void testarBuscar(LISTA *l)
{
    // Testa a busca por um valor existente
    printf("=> Teste de Busca\n");

    // Preenchendo a lista com valores crescentes
    long TOTAL = 100;
    limpar(l);
    printf("=> Limpando a lista\n");

    
    // Preenchendo a lista com os valores de TOTAL ate 1
    printf("=> Preenchendo a lista com valores de 1 a %ld\n", TOTAL);
    for (long i = TOTAL; i > 0; i--)
        if (!inserir(i, l))
            printf("Algum erro duranta a insercao do valor %ld\n", i);
    imprimirStatus(l);
       
        
    printf("Digite o valor que deseja buscar: ");
    ITEM item;
    scanf("%d", &item);
    long pos = buscar(item, l); 
    if (pos >= 0)
        printf("Achou na posicao: %ld\n", pos);
    else
        printf("Nao achou o item na lista\n");

    // Testa a busca por uma posicao existente
    printf("Digite a posicao que deseja acessar (ou -1 para sair): ");
    long p;
    scanf("%ld", &p);
    while (p != -1)
    {
        ITEM item = enesimo(p, l);
        printf("Achou na posicao[%ld] o valor: %d\n", p, item);
        // Leitura da proxima posicao a ser acessada
        printf("Digite a posicao que deseja acessar (ou -1 para sair): ");
        scanf("%ld", &p);
    }

}


/////////////////////////////////////////////////////

int main(){
	LISTA l;
	
	inicializar(&l);
    testarInserir(&l);
    testarInserirVarios(&l);
    testarBuscar(&l);   
    limpar(&l);
    imprimirStatus(&l);
    destruir(&l);
    
    getchar();
	return 0;
}