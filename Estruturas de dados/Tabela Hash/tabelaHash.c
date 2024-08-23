#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX 10

typedef int TIPOCHAVE;

typedef enum {NuncaUsada, Desocupada, Ocupada} SITUACAO;

typedef struct {
  TIPOCHAVE chave;
  char valor[100];
} ITEM;

typedef struct {
  ITEM item;
  SITUACAO situacao;
} ITEM_TAB_HASH;

typedef struct{
  ITEM_TAB_HASH itens[MAX];
  int tamanho;
} TABELAHASH;


char compare(TIPOCHAVE x, TIPOCHAVE y)
{
    return x > y ? 1 : (x < y ? -1 : 0);
}


bool igual(TIPOCHAVE x, TIPOCHAVE y)
{
    return compare(x,y) == 0;
}


void inicializar(TABELAHASH *t)
{
    t->tamanho = 0;
    for (int i = 0; i < MAX; i++)
       t->itens[i].situacao = NuncaUsada;
}


int hash(TIPOCHAVE chave)
{
   return chave % MAX;
}


int proximaPosicao(int pos)
{
   return (pos + 1) % MAX;
}


int tamanho(TABELAHASH *t)
{
  return t->tamanho;
}


bool cheia(TABELAHASH *t)
{
  return tamanho(t) == MAX;
}


bool vazia(TABELAHASH *t)
{
  return tamanho(t) == 0;
}


bool inserir(ITEM item, TABELAHASH *t)
{
   // Se esta cheia, nao insere
   if (cheia(t))
      return false;

   int pos = hash(item.chave);
   int cont = 0;

   // Procura a primeira posicao livre (Desocupada ou NuncaUsada).
   // Se encontrar alguma chave igual sai da funcao retornando false
   for (; t->itens[pos].situacao == Ocupada; cont++)
      if (igual(t->itens[pos].item.chave, item.chave))
         return false; // A chave ja existe. Nao insere.
      else
          pos= proximaPosicao(pos);

   // Encontrada a posicao para insercao
   int posInsercao = pos;

   // Continua a procura pela chave para ter certeza de que nunca foi usada ou
   // que ja tenha sido removida. Isso garante que nao ha uma chave igual na tabela
   while ( (t->itens[pos].situacao != NuncaUsada) && (cont++ < MAX) )
   {
      // Se o elemento esta ocupado e a chave coincide, o dado nao deve
      // ser inserido
      if ((t->itens[pos].situacao == Ocupada) && 
         igual(t->itens[pos].item.chave, item.chave))
         return false;

      pos= proximaPosicao(pos);
   }

   // Coloca o dado na primeira posicao vaga encontrada
   t->itens[posInsercao].item = item;
   t->itens[posInsercao].situacao = Ocupada;
   t->tamanho++;
   return true;
}


bool encontrarPos(TIPOCHAVE chave, int *pos, TABELAHASH *t)
{
   int i = hash(chave);
   int cont = 0;

   // Comeca a procurar na posicao retornada pela funcao Hash e avanca
   //  ate encontrar uma posicao que nunca foi usada (isso indica que
   //  dali para frente, nao ha possibilidade de encontrar a chave
   //  procurada) ou ate percorrer toda a tabela
   while ( (t->itens[i].situacao != NuncaUsada) && (cont < MAX) )
   {
      if ( (t->itens[i].situacao == Ocupada) && 
           igual(t->itens[i].item.chave, chave) )
      {
         *pos = i;
         return true;
      }
      cont++;
      i = proximaPosicao(i);
   }

   return false;
}


bool obter(TIPOCHAVE chave, ITEM *item, TABELAHASH *t)
{
   int pos;
   if (encontrarPos(chave, &pos, t))
   {
      *item = t->itens[pos].item;
      return true;
   }
   return false;
}


bool alterar(ITEM item, TABELAHASH *t)
{
   int pos;
   if (encontrarPos(item.chave, &pos, t))
   {
      t->itens[pos].item = item; 
      return true;
   }
   return false;
}


bool remover(TIPOCHAVE chave, TABELAHASH *t)
{
   int pos;
   if (encontrarPos(chave, &pos, t))
   {
      t->itens[pos].situacao = Desocupada; 
      t->tamanho--;
      return true;
   }
   return false;
}


void exibirTab(TABELAHASH *t)
{
  printf("Posicao | Situacao/Item\n");
  for (int i = 0; i < MAX; i++)
  {
    printf("[%d] | ", i); 
    if (t->itens[i].situacao == Ocupada)
       printf("(%d,%s)\n", t->itens[i].item.chave, t->itens[i].item.valor);
    else
       printf(t->itens[i].situacao == NuncaUsada ? "(NU)\n" : "(D)\n");
  }
}

void limpar(TABELAHASH *t)
{
  inicializar(t);
}