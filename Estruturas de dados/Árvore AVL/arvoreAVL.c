#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef enum {NoEsquerdo, NoDireito, NoPai, NoRaiz} DIRECAO;

typedef int ITEM;

typedef struct estrutura
{
    ITEM item;
    struct estrutura *esq;
    struct estrutura *dir;
    struct estrutura *pai;
    int altura;     // Altura do No, sendo que um No folha tem altura 0

} ARVORE_BINARIA;


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
    (*arvore)->altura = 0;
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


ARVORE_BINARIA* adicionarFilho(ITEM item, DIRECAO direcao, ARVORE_BINARIA *arvore)
{
   if (vazia(arvore) || (direcao == NoPai) || (direcao == NoRaiz) || existeNo(direcao, arvore))
     return false;  // Criacao ilegal de um filho

   if (direcao == NoEsquerdo)
   {
       criarNo(item, &(arvore->esq));
       arvore->esq->pai = arvore;
       return arvore->esq;
   }
   else
   {
       criarNo(item, &(arvore->dir));
       arvore->dir->pai = arvore;
       return arvore->dir;
   }
   return NULL;
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

   // Testa se nao achou o item na arvore, pois, nesse caso, p 
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


/////////////////////////////////////////////////////////////////
//            FUNCOES ESPECIFICAS DE ARVORES AVL               //
/////////////////////////////////////////////////////////////////


bool eFilhoEsquerdo(ARVORE_BINARIA *no)
{
   return existeNo(NoPai, no) && (no->pai->esq == no); 
}


bool eFilhoDireito(ARVORE_BINARIA *no)
{
   return existeNo(NoPai, no) && (no->pai->dir == no);
}


int alturaNo(ARVORE_BINARIA *no)
{
   return no->altura;
}


int balanceamento(ARVORE_BINARIA *no)
{
   return alturaNo(no->esq) - alturaNo(no->dir);
}


int balanco(ARVORE_BINARIA *no)
{
   int bal = 0;
   if (existeNo(NoEsquerdo, no))
      bal += 1 + alturaNo(no->esq);
   if (existeNo(NoDireito, no))
      bal -= 1 + alturaNo(no->dir);
   return bal;
}


/*
 * Objetivo: Retorna true se o No corrente esta balanceado, ou seja,
 *           tem balanco igual a -1, 0 ou 1.
 */
bool balanceado(ARVORE_BINARIA *no)
{
   return (balanco(no) >= -1) && (balanco(no) <= 1);      
}


/*
 * Objetivo: Retorna true se o No corrente esta desbalanceado, ou seja,
 *           tem balanco fora da faixa -1 a 1.
 */
bool desbalanceado(ARVORE_BINARIA *no)
{
   return !balanceado(no);      
}    


// Retorna o maior valor entre a e b.
int maior(int a, int b)
{
   return a > b ? a : b;
}


// Retorna a altura do filho mais alto.
int alturaFilhoMaisAlto(ARVORE_BINARIA *no) 
{
   int alturaFilhoEsq = existeNo(NoEsquerdo, no) ? alturaNo(no->esq) : -1;
   int alturaFilhoDir = existeNo(NoDireito, no) ? alturaNo(no->dir) : -1;
   return maior(alturaFilhoEsq, alturaFilhoDir);
 }


// Atualiza a altura do No com base na altura do filho mais alto.
void atualizarAltura(ARVORE_BINARIA *no)
{
   no->altura = alturaFilhoMaisAlto(no) + 1;
}


/**
 * Objetivo: Faz com que o No apontado por outroNo passe a ter como 
 *           No pai o pai do No apontado por no. Ao mesmo tempo, faz
 *           com que o pai de no passe a enxergar outroNo como filho.
 */
void trocarPaiComNo(ARVORE_BINARIA *outroNo, ARVORE_BINARIA *no)
{
   outroNo->pai = no->pai;      
   if (eFilhoEsquerdo(no))
      outroNo->pai->esq = outroNo;
   else 
      if (eFilhoDireito(no))
         outroNo->pai->dir = outroNo;
   no->pai = outroNo;
}


/**
 * Objetivo: Efetua uma rotacao simples para a esquerda considerando o No
 * corrente como o pivo.

   Fazendo a rotacao em torno de B teriamos a situacao ao lado

         no -->  B                                D
                / \                            /     \
               A   D  <-- filhoDir     =>     B       F
                  / \                        / \     / \ 
       temp -->  C   F                      A   C   E   G   
                    / \
                   E   G

*/
void rotacaoParaEsquerda(ARVORE_BINARIA *no) {      
   ARVORE_BINARIA *filhoDir = no->dir;
   ARVORE_BINARIA *temp = filhoDir->esq;

   filhoDir->esq = no;
   trocarPaiComNo(filhoDir, no);

   no->dir = temp;
   if (temp)      // temp != NULL
      temp->pai = no;

   atualizarAltura(no);
   atualizarAltura(filhoDir);
}


/**
 * Objetivo: Efetua uma rotacao simples para a direita considerando
 *           o No corrente como o pivo.

   Fazendo a rotacao em torno de F teriamos a situacao ao lado

          no -->  F                         D
                /   \                    /     \
filhoEsq -->  D      G       =>         B       F
             / \                       / \     / \
            B   E  <-- temp           A   C   E   G
           / \
          A   C

*/ 
void rotacaoParaDireita(ARVORE_BINARIA *no) {
   ARVORE_BINARIA *filhoEsq = no->esq;
   ARVORE_BINARIA *temp = filhoEsq->dir;

   filhoEsq->dir = no;      
   trocarPaiComNo(filhoEsq, no);

   no->esq = temp;
   if (temp)      // temp != NULL
      temp->pai = no;

   atualizarAltura(no);
   atualizarAltura(filhoEsq);
}


/*
* Objetivo: Rotacao dupla esquerda direita. Rotaciona primeiro o filho
*           esquerdo para a esquerda e depois o proprio pivo (no atual)
*           como parametro para a direita.
*/
void rotacaoDuplaEsquerdaDireita(ARVORE_BINARIA *no)
{
     rotacaoParaEsquerda(no->esq);
     rotacaoParaDireita(no);
}


/*
 * Objetivo: Rotacao dupla direita esquerda. Rotaciona primeiro o filho
 *           direito para a direita e depois o proprio pivo (no atual)
 *           como parametro para a esquerda
 */
void rotacaoDuplaDireitaEsquerda(ARVORE_BINARIA *no)
{
     rotacaoParaDireita(no->dir);
     rotacaoParaEsquerda(no);
}

/*
 * Objetivo: Verifica os balancos de um No e efetua a rotacao 
 *           adequada para deixar o no com balanco entre -1 e 1.
 */
void rotacionar(ARVORE_BINARIA *no)
{
   if (balanco(no) < -1)   // desbalanceada (subarvore mais alta na direita)
   {
      if (balanco(no->dir) <= 0)
      {
         //printf("\nRotacao simples para Esquerda");
         rotacaoParaEsquerda(no);
      }
      else
      {
         //printf("\nRotacao Direita e Esquerda");
         rotacaoDuplaDireitaEsquerda(no);
      }
   } 
   else
   { 
      if (balanco(no) > 1)  // desbalanceada (subarvore mais alta na esquerda)
      {
         if (balanco(no->esq) >= 0)
         {
            //printf("\nRotacao simples para Direita");
            rotacaoParaDireita(no);
         }
         else
         {
            //printf("\nRotacao para Esquerda Direita");
            rotacaoDuplaEsquerdaDireita(no);
         }
      }              
   }
}


/**
 * Verifica o balanco e efetua rotacoes visando corrigir o
 * desbalanceamento provodado pela remocao.
 */
void balancearAscendentes(ARVORE_BINARIA *no)
{
   if (no) // Ainda nao chegou na Raiz
   {
      ARVORE_BINARIA *pai = no->pai;
      atualizarAltura(no);
      
      if (desbalanceado(no))
         rotacionar(no);

      //printf("\nbalancearAscendentes do no (%d)", no->item); 
      balancearAscendentes(pai);       
   }
}


/*
| Objetivos: Tenta inserir um No na ABB apontada por arvore.
|            Se conseguir, retorna o No inserido. 
|            Caso nao consiga, retorna NULL.
*/
ARVORE_BINARIA* inserirBinaria(ITEM item, ARVORE_BINARIA **arvore)
{
   ARVORE_BINARIA *pPai;
   bool inseriu = true;

   // Se arvore estiver vazia entao so e necessario criar o No, mas se nao
   // estiver, entao sera feita a procura (pela item) na arvore. Se for achada
   // alguma ocorrencia do item na arvore (duplicado), entao retornara
   // false. Caso contrario o item sera adicionado em uma das subarvores de Arvore.
   if (vazia(*arvore))
   {
      criarNo(item, arvore);
      return *arvore;
   }

   if (encontrarNo(item, &pPai, *arvore))
      return NULL;    // item duplicado
   
   if (compare(item, pPai->item) == -1)
      return adicionarFilho(item, NoEsquerdo, pPai);   // Inseriu na esquerda
   else
      return adicionarFilho(item, NoDireito, pPai);    // Inseriu na direita
}


ARVORE_BINARIA* inserir(ITEM item, ARVORE_BINARIA **arvore)
{
   ARVORE_BINARIA *noInserido = inserirBinaria(item, arvore);
   balancearAscendentes(noInserido);
   deslocar(NoRaiz, arvore);  // Depois das rotacoes, a raiz pode mudar
   return noInserido;
}


// Retorna um apontador para o No sucessor do parametro arvore
ARVORE_BINARIA* sucessor(ARVORE_BINARIA *arvore)
{
   ARVORE_BINARIA* suc = arvore->dir;

   // Desloca o sucessor pelas subarvores ate chegar em um No 
   // sem subarvore esquerda
   while (existeNo(NoEsquerdo, suc))
      deslocar(NoEsquerdo, &suc);

   return suc;
}

/*
  Objetivo: Substitui o ITEM contido No apontado pelo parametro arvore
            pelo valor contido em seu sucessor imediato.
*/
ARVORE_BINARIA* substituirPorSucessor(ARVORE_BINARIA *arvore)
{
   ARVORE_BINARIA *suc = sucessor(arvore);
   ARVORE_BINARIA *pApagar = suc;
   arvore->item = suc->item;

   // Se existir, corrige o apontador pai do seu filho direito
   // de sucessor, fazendo-o apontar para o pai do sucessor
   if (existeNo(NoDireito, suc))
      suc->dir->pai = suc->pai;

   // Ajusta o apontador que o pai tem para o sucessor para apontar
   // para o filho direito do sucessor (que pode ser NULL)
   if (eFilhoDireito(suc))
      suc->pai->dir = suc->dir;
   else
      suc->pai->esq = suc->dir;

   return pApagar;
}


/*
| Objetivos: Retira o No contendo o item da arvore apontada por arvore. Retorna
|            o No removido ou NULL, caso contrario.
*/
ARVORE_BINARIA* removerBinaria(ITEM item, ARVORE_BINARIA **arvore)
{
   ARVORE_BINARIA *pApagar;

   /* Se a arvore estiver vazia, o No nao sera retirado, pois nao existe. Mas
      se nao estiver vazia, sera feita a procura atraves de chamadas
      recursivas de remover, pegando a subarvore esquerda quando o item for
      menor que o valor do item no No ou a subarvore direita quando for maior.
      Existem dois pontos de parada, o primeiro quando a subarvore onde esta
      sendo feita a busca esta vazia e o segundo quando o item for encontrada.
      Nesse caso acontecera a remocao */
   if (vazia(*arvore))
      return NULL;

   int comp = compare(item, (*arvore)->item); 
   if (comp == -1) // item < item da arvore
      return removerBinaria(item, &((*arvore)->esq));

   if (comp == 1) // item > item da arvore
      return removerBinaria(item, &((*arvore)->dir));

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

      *arvore = (*arvore)->dir;
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
      }
      else
         pApagar = substituirPorSucessor(*arvore);
   }

   return pApagar;
}



bool remover(ITEM item, ARVORE_BINARIA **arvore)
{
   ARVORE_BINARIA* noRemovido = removerBinaria(item, arvore);
   if (noRemovido == NULL)
      return false;

   balancearAscendentes(noRemovido->pai);
    
   if (!vazia(*arvore))
      deslocar(NoRaiz, arvore);  // Depois das rotacoes, a raiz pode mudar
   
   free(noRemovido);
   return true;
}