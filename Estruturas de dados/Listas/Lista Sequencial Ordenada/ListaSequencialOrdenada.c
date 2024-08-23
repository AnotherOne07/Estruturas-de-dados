#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "ListaSeqOrd.h"


char compare(ITEM x, ITEM y)
{
    return x > y ? 1 : (x < y ? -1 : 0);
}


bool igual(ITEM x, ITEM y)
{
    return compare(x,y) == 0;
}


void inicializar(LISTA *l)
{
    l->tamanho = 0;
}


long tamanho(LISTA *l)
{
    return l->tamanho;
}


bool cheia(LISTA *l)
{
    return tamanho(l) == MAX;
}


bool vazia(LISTA *l)
{
    return tamanho(l) == 0;
}


ITEM enesimo(long n, LISTA *l)
{
    if (n >= 0 && n < tamanho(l))
       return (l->itens[n]);
    else
    {
        printf("ERRO: Posicao %ld fora dos limites da lista (0 a %ld).\n",
               n, tamanho(l)-1);
        exit(EXIT_FAILURE);
    }
}


bool inserirNaPos(ITEM item, long i, LISTA *l)
{
    // A posicao tem que estar entre 0 e MAX-1 e ate o tamanho atual
    if ((tamanho(l) >= MAX) || (i < 0) || (i > tamanho(l)))
        return false; // lista cheia ou indice invalido

    // Se for inserido no meio, e necessario abrir espaco para o item
    for (long j = tamanho(l); j > i; j--)
        l->itens[j] = l->itens[j-1];

    // Coloca o item em um espaco vago e ajusta o tamanho        
    l->itens[i] = item;
    l->tamanho++;
    return true;
}


void exibirItem(ITEM i)
{
    printf("%d", i);
}


void exibirLista(LISTA *l)
{
    printf("[");
    for(long i = 0; i < tamanho(l);)
    {
        exibirItem(l->itens[i++]);
        if (i < tamanho(l))
           printf(",");
    }
    printf("]");
}


void limpar(LISTA *l)
{
    l->tamanho = 0;
}


void destruir(LISTA *l)
{
    limpar(l);
}

//////////////// MUDANCAS SOBRE A LISTA SEQUENCIAL ////////////////


/*
 Objetivo: Move para uma posicao para esquerda todos os elementos
           a direita da posicao pos.
*/ 
void moverParaEsquerda(long pos, LISTA *l)
{
    for (; pos < l-> tamanho - 1; pos++)
        l->itens[pos] = l->itens[pos + 1];
}


/*
 Objetivo: Move para uma posicao para direita todos os elementos a partir
           da posicao pos, comecando a copia da posicao tamanho - 1 (final)
           para tamanho e terminando ate chegar a copiar para pos + 1 o
           item contido em pos.
*/ 
void moverParaDireita(long pos, LISTA *l)
{
    for (long i = l->tamanho; i > pos; i--)
        l->itens[i] = l->itens[i-1];
}


/*
  Objetivo: Executa uma busca binaria na lista. 
            Depende da lista estar ordenada.
            Retorna a posicao (indice) do item (no) passado como 
            parametro na lista.
            Caso nao encontre, retorna o valor -1.
*/
long buscaBin(ITEM item, long inicio, long fim, ITEM *itens)
{
    printf("Comecando BuscaBin Inicio: %d, Fim: %d\n", inicio, fim);
    while (inicio <= fim)
    {
        long meio = (inicio + fim) / 2; // calcula a posicao do meio
        printf("Meio: %ld, Inicio: %ld, Fim: %ld\n", meio, inicio, fim);
        long comp = compare(item, itens[meio]);
        if (comp == 0) // iguais 
            return meio; // achou
        else
        {
            if (comp == 1) // item maior do que o do meio
                inicio = meio + 1; // concentra a busca na parte da direita
            else // item menor do que o do meio 
                fim = meio - 1; // concentra a busca na parte da esquerda
        }
    }
    return -1; // nao achou
}


/*
  Objetivo: Executa uma busca binaria na lista (de forma recursiva). 
            Depende da lista estar ordenada.
            Recebe como parametro as posicoes de inicio (inf) e 
            fim (sup) da busca.
            Retorna a posicao (indice) do item (no) passado como 
            parametro na lista.
            Caso nao encontre, retorna o valor -1.
*/
long buscaBinRec(ITEM item, long inicio, long fim, ITEM *itens)
{
    if (inicio <= fim)
    {
        long meio = (inicio + fim) / 2;
        int comp = compare(item, itens[meio]);
        if (comp == 0) 
            return meio; // achou
        else
        {
            if (comp == 1) // item maior do que o do meio 
                return buscaBinRec(item, meio + 1, fim, itens); // concentra a busca na parte da direita
            else  // item menor do que o do meio 
                return buscaBinRec(item, inicio, meio - 1, itens); // concentra a busca na parte da esquerda
        }
    }
    return -1; // nao achou
}


long buscar(ITEM item, LISTA *l)
{
    printf("Tamanho da lista: %d\n", tamanho(l));
    //return buscaBin(item, 0, tamanho(l) - 1, l->itens);
    return buscaBinRec(item, 0, tamanho(l) - 1, l->itens);
}


/*
 Objetivo: Inserir em uma lista ordenada o item passado e garantir
           que nao havera duplicacao. 
           Esta versao nao usa a busca sequencial (menos eficiente).
*/
bool inserir(ITEM item, LISTA *l){
    if (cheia(l)) 
        return false; // lista cheia
    
    long i = 0;

    // Faz uma busca sequencial ate o ponto correto de insercao
    // ou chegar ao final da lista
    while (i < tamanho(l) && (compare(l->itens[i], item) == -1)) i++;
    
    if (i == tamanho(l)) // inserindo no final da lista
        return inserirNaPos(item, i, l);
    else 
    {
       if (igual(l->itens[i], item)) // Se encontrou o item, evita incluir um duplicado
          return false;
       else 
          return inserirNaPos(item, i, l);
    } 
}

/*
  Objetivo: Remove o item que  coincide com o parametro item
            passado. Caso nao seja encontrado o item, retorna
            false. Se o item foi removido, retorna true.
*/
bool remover(ITEM item, LISTA *l)
{
    long pos = buscar(item, l);
    if (pos == -1)
        return false; // nao achou
    else
    {
        moverParaEsquerda(pos, l);
        l->tamanho--;
        return true; // achou
    }
}