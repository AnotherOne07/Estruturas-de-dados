#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "ArvBin.h"


char compare(ITEM x, ITEM y)
{
    return x > y ? 1 : (x < y ? -1 : 0);
}


bool igual(ITEM x, ITEM y)
{
    return compare(x,y) == 0;
}


void inicializar(ARVORE_BINARIA *arvore)
{
    arvore = NULL;
}


bool vazia(ARVORE_BINARIA *arvore)
{
    return arvore == NULL;
}


void criarNo(ITEM item, ARVORE_BINARIA **arvore)
{
    if (!vazia(*arvore))
    {
       printf("ERRO: O no deve estar vazio para ser criado.");
       exit(EXIT_FAILURE);
    }

    *arvore = (ARVORE_BINARIA*) malloc(sizeof(ARVORE_BINARIA));
    (*arvore)->item = item;
    (*arvore)->pai = NULL;
    (*arvore)->esq = NULL;
    (*arvore)->dir = NULL;
}


bool existeNo(DIRECAO direcao, ARVORE_BINARIA *arvore)
{
   if (vazia(arvore))
      return false;

   if (direcao == NoRaiz)
      return true;
   
   if (direcao == NoPai)
      return !vazia(arvore->pai);

   if (direcao == NoEsquerdo)
      return !vazia(arvore->esq);

   if (direcao == NoDireito)
      return !vazia(arvore->dir);

   return false;
}


// Deslocar o apontador Arvore para o No indicado por Direcao
void deslocar(DIRECAO direcao, ARVORE_BINARIA **arvore)
{
   if (direcao == NoRaiz)
      while (existeNo(NoPai, *arvore))
         *arvore = (*arvore)->pai;

   if (direcao == NoPai)
      *arvore = (*arvore)->pai;

   if (direcao == NoEsquerdo)
      *arvore = (*arvore)->esq;

   if (direcao == NoDireito)
      *arvore = (*arvore)->dir;
}


bool adicionarFilho(ITEM item, DIRECAO direcao, ARVORE_BINARIA *arvore)
{
   if (vazia(arvore) || (direcao == NoPai) || (direcao == NoRaiz) || existeNo(direcao, arvore))
     return false;  // Criacao ilegal de um filho

   if (direcao == NoEsquerdo)
   {
       criarNo(item, &(arvore->esq));
       arvore->esq->pai = arvore;
   }
   else
   {
       criarNo(item, &(arvore->dir));
       arvore->dir->pai = arvore;
   }
   return true;
}


void disposeArvore(ARVORE_BINARIA *arvore)
{
   if (!vazia(arvore))
   {
      disposeArvore(arvore->esq);
      disposeArvore(arvore->dir);
      free(arvore);
   }
}


void deltree(ARVORE_BINARIA **arvore)
{
   ARVORE_BINARIA *pTemp = *arvore;

   /* 
     Testa se Arvore tem pai. Caso tenha, arvore se desloca para 
     ele e pTemp continua apontando para o inicio da arvore a ser
     deletada, depois a arvore e apagada e o apontador do pai e
     atualizado com NULL. Caso Arvore nao tenha pai, a arvore e
     eliminada usando pTemp e arvore recebe NULL */
   if (existeNo(NoPai, *arvore))
   {
      deslocar(NoPai, arvore);
      disposeArvore(pTemp);
      if ((*arvore)->esq == pTemp)
         (*arvore)->esq = NULL;
      else
         (*arvore)->dir = NULL;
   }
   else
   {
      disposeArvore(pTemp);
      arvore = NULL;
   }
}


void preOrdem(ARVORE_BINARIA *arvore, void (*visite)(ARVORE_BINARIA*) )
{
   if (!vazia(arvore))
   {         
      visite(arvore);
      preOrdem(arvore->esq, visite);
      preOrdem(arvore->dir, visite);
   }
}


void inOrdem(ARVORE_BINARIA *arvore, void (*visite)(ARVORE_BINARIA*) )
{
   if (!vazia(arvore))
   {         
      inOrdem(arvore->esq, visite);
      visite(arvore);
      inOrdem(arvore->dir, visite);
   }
}


void posOrdem(ARVORE_BINARIA *arvore, void (*visite)(ARVORE_BINARIA*) )
{
   if (!vazia(arvore))
   {         
      posOrdem(arvore->esq, visite);
      posOrdem(arvore->dir, visite);
      visite(arvore);
   }
}


//////////////////////////////////////////////////////////////
// FUNCOES ESPECIFICAS DA ARVORE BINARIA DE BUSCA
//////////////////////////////////////////////////////////////

bool encontrarNo(ITEM item, ARVORE_BINARIA **p, ARVORE_BINARIA *arvore)
{
   ARVORE_BINARIA *pAnt = NULL;
   bool achou = false;
   *p = arvore;

   // Laco que fara o deslocamento de p ate que tenha chegado 
   // ao local onde deveria estar o No ou tenha o encontrado
   while (!vazia(*p) && !achou)
   {
      pAnt = *p;
      int comp = compare(item, (*p)->item); 
      if (comp == 0) // igual
         achou = true;
      else
      {
         if (comp == -1) // menor
            deslocar(NoEsquerdo, p);
         else // maior
            deslocar(NoDireito, p);
      }
   }

   // Testa se nao achou a chave na arvore, pois, nesse caso, p 
   // devera estar apontando para o No que seria seu pai (pAnt)
   if (!achou)
      *p = pAnt;

   return achou;
}


bool contem(ITEM item, ARVORE_BINARIA *arvore)
{
   ARVORE_BINARIA *p;
   return encontrarNo(item, &p, arvore);
}


bool inserir(ITEM item, ARVORE_BINARIA **arvore)
{
   ARVORE_BINARIA *pPai;

   // Se arvore estiver vazia entao so e necessario criar o No.
   // Se nao estiver, entao fara a procura (pela chave) na arvore. 
   // Se for achada alguma ocorrencia da chave na arvore (chave
   // duplicada), entao retornara false. Caso contrario item
   // sera adicionado em uma das subarvores de Arvore.
   if (vazia(*arvore))
      criarNo(item, arvore);
   else
   {
      if (encontrarNo(item, &pPai, *arvore)) // testa se ha duplicacao
         return false;
      else
      {
         if (compare(item, pPai->item) == -1) // item < pPai->item
            adicionarFilho(item, NoEsquerdo, pPai);
         else
            adicionarFilho(item, NoDireito, pPai);
      }
   }
   return true;
}


// Determina o sucessor imediato do No apontado por Arvore.
// Quando encontrar, copia para arvore os dados contidos no 
// Sucessor e muda o apontador sucessor para o seu No direito. 
// No final, apaga o No onde se encontrava o Sucessor.
void substituir(ARVORE_BINARIA **sucessor, ARVORE_BINARIA **arvore)
{

   ARVORE_BINARIA *pApagar;
   // Se nao ha mais Nos a esquerda, sucessor ja eh o sucessor imediato
   if (vazia((*sucessor)->esq))
   {
       (*arvore)->item = (*sucessor)->item;
       pApagar = *sucessor;

       // Se existir, corrige o apontador pai do seu filho direito
       // de sucessor, fazendo-o apontar para o pai do sucessor
       if (!vazia((*sucessor)->dir))
          (*sucessor)->dir->pai = (*sucessor)->pai;

       *sucessor = (*sucessor)->dir;
       free(pApagar);
   }
   else
      substituir(&((*sucessor)->esq), arvore);
}


bool remover(ITEM item, ARVORE_BINARIA **arvore)
{
   ARVORE_BINARIA *pApagar;

   /* Se a arvore estiver vazia, o No nao sera retirado, pois nao existe.
      Se nao estiver vazia, sera feita a procura atraves de chamadas
      recursivas de remover, pegando a subarvore esquerda quando chave for
      menor que o valor da chave no No ou a subarvore direita quando for maior.
      Existem dois pontos de parada, o primeiro quando a subarvore onde esta
      sendo feita a busca esta vazia e o segundo quando a chave for encontrada.
      Nesse caso acontecera a remocao */
   if (vazia(*arvore))
      return false;

   int comp = compare(item, (*arvore)->item); 
   if (comp == -1) // item < item da arvore
      return remover(item, &((*arvore)->esq));

   if (comp == 1) // item > item da arvore
      return remover(item, &((*arvore)->dir));

   /* Como nesse ponto item = arvore->item, devemos verificar
     se o No possui duas, uma ou nenhuma subarvore. No primeiro caso
     deve ser procurado na subarvore direita o sucessor imediato do No
     e coloca-lo no lugar do No removido. Nos outros dois casos, so
     e necessario remover o No e ajustar os apontadores */

   if (vazia((*arvore)->esq))   // Arvore nao tem subarvores ou tem somente a direita
   {
      pApagar = *arvore;

      /* Se existir, corrige o apontador pai do filho direito do No a 
         ser removido, fazendo-o apontar para o pai do No a ser removido */
      if (!vazia((*arvore)->dir))
         (*arvore)->dir->pai = (*arvore)->pai;

      (*arvore) = (*arvore)->dir;
      free(pApagar);
   }
   else
   {
      if (vazia((*arvore)->dir)) // Arvore tem somente o filho esquerdo
      {   
         pApagar = (*arvore);

         /* Corrige o apontador pai do filho esquerdo do No a ser removido,
            fazendo-o apontar para o pai do No a ser removido */
         (*arvore)->esq->pai = (*arvore)->pai;
         *arvore = (*arvore)->esq;
         free(pApagar);
      }
      else
         substituir(&((*arvore)->dir), arvore);
   }

   return true;
}

////////////////////////// EXERCICIOS ARVBIN BUSCA ///////////////

bool estaPresente(ITEM valor, ARVORE_BINARIA *arv)
{
  
  if(!arv)
    return false;

  int comp = compare(valor, arv->item);
  
  if(comp == 0)
    return true;

  else if (comp == 1)
    estaPresente(valor, arv->dir);

  else if (comp == -1)
    estaPresente(valor, arv->esq);

  return false;
}

bool contem(ARVORE_BINARIA *arv1, ARVORE_BINARIA *arv2)
{
  ARV_BINARIA *pArv1 = &(*arv1); 
  
}