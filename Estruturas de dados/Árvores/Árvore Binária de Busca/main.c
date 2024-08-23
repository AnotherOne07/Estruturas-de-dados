#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "ArvBin.h"


/////////////////////////////////////////////////////

// Visita um NO da arvore, imprimindo o valor da chave
// entre parenteses
void imprimir(ARVORE_BINARIA *arvore) {
    printf("(%d)", arvore->item);
}


/////////////////////////////////////////////////////

/*
 Objetivos: Partindo do nivel passado como parametro, calcula o numero
 de nos (numNos), a altura da arvore e a soma dos niveis de cada.
*/
void inOrdCarac(int nivel, int *numNos, int *altura, float *soma, ARVORE_BINARIA *arvore)
{
   if (!vazia(arvore))
   {
      inOrdCarac(nivel + 1, numNos, altura, soma, arvore->esq);
      *numNos = *numNos + 1;
      *soma = *soma + nivel;
      if (nivel > *altura)
         *altura = nivel;
      inOrdCarac(nivel + 1, numNos, altura, soma, arvore->dir);
   }
}


/*
| Objetivos: Determinar as caracteristicas de uma arvore, tal como, 
|            o numero de Nos, Altura, e o seu comprimento medio.
*/
void caracteristicas(int *numNos, int *altura, float *compMedio,
                     ARVORE_BINARIA *arvore)
{

   *numNos = 0;
   *altura = 0;
   float soma = 0;
   inOrdCarac(0, numNos, altura, &soma, arvore);
   *compMedio = soma / *numNos;
}

/////////////////////////////////////////////////////

bool encadeamentoComNoPaiCorreto(ARVORE_BINARIA *pai, ARVORE_BINARIA *filhoEsq, 
                                                      ARVORE_BINARIA *filhoDir)
{
   bool ok = true;
   if (!vazia(pai))
   {
      // Checa se o filho esquerdo esta ligado ao no atual corretamente via apontador pai
      // Faz o mesmo para as subarvores deste filho
      if (!vazia(filhoEsq))
         ok = (pai == filhoEsq->pai) &&
              encadeamentoComNoPaiCorreto(filhoEsq, filhoEsq->esq, filhoEsq->dir);
      // Checa se o filho direito esta ligado ao no atual corretamente via apontador pai
      // Faz o mesmo para as subarvores deste filho
      if (!vazia(filhoDir) && ok)
         ok = (pai == filhoDir->pai) &&
              encadeamentoComNoPaiCorreto(filhoDir, filhoDir->esq, filhoDir->dir);
   }
   return ok;
}

void checarEncadeamento(ARVORE_BINARIA *arvore)
{
   if (encadeamentoComNoPaiCorreto(arvore, arvore->esq, arvore->dir))
      printf("Ok: Encadeamento dos filhos com o no pai correto\n");
   else
      printf("Erro: Encadeamento dos filhos com o no pai incorreto\n");
}

int main()
{
   ARVORE_BINARIA *arv = NULL;
   inicializar(arv);
   ITEM item;

   item = 7;
   inserir(item, &arv);
   item = 6;
   inserir(item, &arv);
   item = 5;
   inserir(item, &arv);
   item = 11;
   inserir(item, &arv);
   item = 9;
   inserir(item, &arv);
   item = 8;
   inserir(item, &arv);
   item = 10;
   inserir(item, &arv);
   item = 12;
   inserir(item, &arv);
   item = 15;
   inserir(item, &arv);

   /*          7
           6       11
         5      9     12
              8  10     15
   */

   printf("inOrdem: ");
   inOrdem(arv, imprimir);

   // Obtendo as caracteristicas da arvore
   int numNos, altura;
   float compMedio;
   caracteristicas(&numNos, &altura, &compMedio, arv);
   printf("\nNumero de Nos: %d - Altura: %d - Comprimento Medio: %.2f", numNos, altura, compMedio);

   printf("\nRemovendo 6 (No com filho esquerdo)\n");
   remover(6, &arv);
   printf("inOrdem: ");
   inOrdem(arv, imprimir);

   /*          7
           5       11
                9     12
              8  10     15
   */

   printf("\nRemovendo 5 (No Folha)\n");
   remover(5, &arv);
   printf("inOrdem: ");
   inOrdem(arv, imprimir);

   /*          7
                   11
                9     12
              8  10     15
   */

   printf("\nRemovendo 11 (No com 2 filhos)\n");
   remover(11, &arv);
   printf("inOrdem: ");
   inOrdem(arv, imprimir);
   printf("\n");

   /*
              7
                   12
                9     15
              8  10
   */


   item = 15;
   if (contem(item, arv))
      printf("Ok: O valor %d esta contido na arvore\n", item);
   else
      printf("Erro: nao foi encontrado o item %d\n", item);

   // Checa o encadeamento dos nos, inclusive com seus pais
   checarEncadeamento(arv);
  
   disposeArvore(arv);
   return 0;
}