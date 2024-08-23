#include "arvore_B.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void inicializa(TApontador *arvB) { *arvB = NULL; }

void inOrder(TApontador tree) {
  int i;

  if (tree != NULL) {

    for (i = 0; i < tree->n; i++) {
      inOrder(tree->apontadoresPagina[i]);
      printf("%ld ", tree->itensPagina[i].item);
    }

    inOrder(tree->apontadoresPagina[i]);
  }
  return;
}

bool pesquisa(TRegistro *elem, TApontador apontador) {
  long i = 1;
  if (apontador == NULL) {
    printf("TRegistro nao esta presente na arvore\n");
    return FALSE;
  }
  while (i < apontador->n && elem->item > apontador->itensPagina[i - 1].item) {
    i++;
  }

  if (elem->item == apontador->itensPagina[i - 1].item) {
    // printf("%lu", apontador->itensPagina[i - 1].item);
    *elem = apontador->itensPagina[i - 1];

    return TRUE;
  }
  if (elem->item < apontador->itensPagina[i - 1].item) {
    pesquisa(elem, apontador->apontadoresPagina[i - 1]);
  }

  else {
    pesquisa(elem, apontador->apontadoresPagina[i]);
  }
}

bool pesquisaValorNumerico(ITEM item, TApontador apontador) {
  long i = 1;
  if (apontador == NULL) {
    printf("Valor nao esta presente na arvore\n");
    return FALSE;
  }
  while (i < apontador->n && item > apontador->itensPagina[i - 1].item) {
    i++;
  }

  if (item == apontador->itensPagina[i - 1].item) {
    // printf("%lu", apontador->itensPagina[i - 1].item);
    return TRUE;
  }
  if (item < apontador->itensPagina[i - 1].item) {
    pesquisaValorNumerico(item, apontador->apontadoresPagina[i - 1]);
  }

  else {
    pesquisaValorNumerico(item, apontador->apontadoresPagina[i]);
  }
}

void insereNaPagina(TApontador apontador, TRegistro registro,
                    TApontador apontadorDireto) {
  short naoAchouPosicao;
  int tamanhoPagina;
  tamanhoPagina = apontador->n;
  naoAchouPosicao = (tamanhoPagina > 0);
  while (naoAchouPosicao) {
    if (registro.item >= apontador->itensPagina[tamanhoPagina - 1].item) {
      naoAchouPosicao = FALSE;
      break;
    }

    apontador->itensPagina[tamanhoPagina] =
        apontador->itensPagina[tamanhoPagina - 1];

    apontador->apontadoresPagina[tamanhoPagina + 1] =
        apontador->apontadoresPagina[tamanhoPagina];

    tamanhoPagina--;
    if (tamanhoPagina < 1)
      naoAchouPosicao = FALSE;
  }
  apontador->itensPagina[tamanhoPagina] = registro;
  apontador->apontadoresPagina[tamanhoPagina + 1] = apontadorDireto;
  apontador->n++;
}

void insereAux(TRegistro registro, TApontador apontador, short *cresceu,
               TRegistro *registroRetorno, TApontador *apontadorRetorno) {
  long posAux = 1; // Posição provavel do vetor em que novo indice sera inserido
  long j;
  TApontador apontadorTemporario;

  if (apontador ==
      NULL) { // Critério de parada da recursão. Pode ser usado para arvore
              // vazia, arvore com espaço em folhas ou arvore que explode
    *cresceu = TRUE;
    (*registroRetorno) = registro;
    (*apontadorRetorno) = NULL;
    return;
  }

  while (posAux < apontador->n &&
         registro.item > apontador->itensPagina[posAux - 1].item) {
    posAux++; // Percorrendo vetores dos nós para encontrar valor maior (ou
              // igual) que o novo indice
  }
  if (registro.item == apontador->itensPagina[posAux - 1].item) {
    printf(" Erro: Registro ja esta presente\n");
    *cresceu = FALSE;
    return;
  }

  if (registro.item < apontador->itensPagina[posAux - 1].item) {
    posAux--; // Como o valor nao é igual, só pode ser maior, entao volta-se uma
              // posição
  }
  insereAux(registro, apontador->apontadoresPagina[posAux], cresceu,
            registroRetorno,
            apontadorRetorno); // Chama-se recursivo para descer na arvore

  if (!*cresceu)
    return;

  if (apontador->n < MM) { /* Pagina tem espaco */

    insereNaPagina(apontador, *registroRetorno,
                   *apontadorRetorno); // Chama insere na página pq tem espaço
    *cresceu = FALSE;
    return;
  }

  /* Overflow: Pagina tem que ser dividida */ // Página nao tem espaço
                                              // suficiente
  apontadorTemporario = (TApontador)malloc(sizeof(
      TPagina)); // Cria nova pagina pra ser raiz da subarvore que vem do split
  apontadorTemporario->n = 0;
  apontadorTemporario->apontadoresPagina[0] =
      NULL; // Ela começa com zero indices e primeiro filho pra NULL
  if (posAux < M + 1) {
    insereNaPagina(apontadorTemporario, apontador->itensPagina[MM - 1],
                   apontador->apontadoresPagina[MM]);
    apontador->n--;
    insereNaPagina(apontador, *registroRetorno, *apontadorRetorno);
  } else
    insereNaPagina(apontadorTemporario, *registroRetorno, *apontadorRetorno);
  for (j = M + 2; j <= MM; j++) {
    insereNaPagina(apontadorTemporario, apontador->itensPagina[j - 1],
                   apontador->apontadoresPagina[j]);
  }
  apontador->n = M;
  apontadorTemporario->apontadoresPagina[0] =
      apontador->apontadoresPagina[M + 1];
  *registroRetorno = apontador->itensPagina[M];
  *apontadorRetorno = apontadorTemporario;
}
// desenhar esquema para visualizar melhor para a explicacao
void insere(TRegistro registro, TApontador *apontador) {
  short cresceu;
  TRegistro registroRetorno;
  TPagina *apontadorRetorno, *apontadorTemporario;
  insereAux(registro, *apontador, &cresceu, &registroRetorno,
            &apontadorRetorno); // Chamando funcao insere auxiliar

  /* Arvore cresce na altura pela raiz */
  if (cresceu) {
    apontadorTemporario =
        (TPagina *)malloc(sizeof(TPagina)); // Criando nova raiz
    apontadorTemporario->n = 1; // Definindo que a nova raiz só terá um índice
    apontadorTemporario->itensPagina[0] =
        registroRetorno; // Definindo valor do unico indice da raiz
    apontadorTemporario->apontadoresPagina[1] =
        apontadorRetorno; // Definindo filho da direita da raiz, resultado
                          // do split que causou explosao no tamanho
    apontadorTemporario->apontadoresPagina[0] =
        *apontador; // Definindo filho da esquerda da raiz, resultado do
                    // split que causou explosao no tamanho
    *apontador = apontadorTemporario; // Enderençando nova raiz
  }
}

void reconstitui(TApontador apontadorPagina, TApontador apontadorPai,
                 int posicaoPai, short *diminuiu) {
  TPagina *aux;
  long dispAux, j;
  if (posicaoPai <
      apontadorPai->n) { /* aux = TPagina a direita de apontadorPagina */
    aux = apontadorPai->apontadoresPagina[posicaoPai + 1];
    dispAux = (aux->n - M + 1) / 2;
    apontadorPagina->itensPagina[apontadorPagina->n] =
        apontadorPai->itensPagina[posicaoPai];
    apontadorPagina->apontadoresPagina[apontadorPagina->n + 1] =
        aux->apontadoresPagina[0];
    apontadorPagina->n++;
    if (dispAux > 0) { /* : aux para apontadorPagina */
      for (j = 1; j < dispAux; j++)
        insereNaPagina(apontadorPagina, aux->itensPagina[j - 1],
                       aux->apontadoresPagina[j]);
      apontadorPai->itensPagina[posicaoPai] = aux->itensPagina[dispAux - 1];
      aux->n -= dispAux;
      for (j = 0; j < aux->n; j++) {
        aux->itensPagina[j] = aux->itensPagina[j + dispAux];
      }
      for (j = 0; j <= aux->n; j++) {
        aux->apontadoresPagina[j] = aux->apontadoresPagina[j + dispAux];
      }
      *diminuiu = FALSE;
    } else { /* Fusao: intercala aux em apontadorPagina e libera aux */
      for (j = 1; j <= M; j++)
        insereNaPagina(apontadorPagina, aux->itensPagina[j - 1],
                       aux->apontadoresPagina[j]);
      free(aux);
      for (j = posicaoPai + 1; j < apontadorPai->n; j++) {
        apontadorPai->itensPagina[j - 1] = apontadorPai->itensPagina[j];
        apontadorPai->apontadoresPagina[j] =
            apontadorPai->apontadoresPagina[j + 1];
      }
      apontadorPai->n--;
      if (apontadorPai->n >= M)
        *diminuiu = FALSE;
    }
  } else {  /* aux = TPagina a esquerda de apontadorPagina */
    aux = apontadorPai->apontadoresPagina[posicaoPai - 1];
    dispAux = (aux->n - M + 1) / 2;
    for (j = apontadorPagina->n; j >= 1; j--)
      apontadorPagina->itensPagina[j] = apontadorPagina->itensPagina[j - 1];
    apontadorPagina->itensPagina[0] = apontadorPai->itensPagina[posicaoPai - 1];
    for (j = apontadorPagina->n; j >= 0; j--)
      apontadorPagina->apontadoresPagina[j + 1] =
          apontadorPagina->apontadoresPagina[j];
    apontadorPagina->n++;
    if (dispAux > 0) /* Existe folga: transf. de aux para apontadorPagina */
    {
      for (j = 1; j < dispAux; j++)
        insereNaPagina(apontadorPagina, aux->itensPagina[aux->n - j],
                       aux->apontadoresPagina[aux->n - j + 1]);
      apontadorPagina->apontadoresPagina[0] =
          aux->apontadoresPagina[aux->n - dispAux + 1];
      apontadorPai->itensPagina[posicaoPai - 1] =
          aux->itensPagina[aux->n - dispAux];
      aux->n -= dispAux;
      *diminuiu = FALSE;
    } else { /* Fusao: intercala apontadorPagina em aux e libera apontadorPagina
              */
      for (j = 1; j <= M; j++)
        insereNaPagina(aux, apontadorPagina->itensPagina[j - 1],
                       apontadorPagina->apontadoresPagina[j]);
      free(apontadorPagina);
      apontadorPai->n--;
      if (apontadorPai->n >= M)
        *diminuiu = FALSE;
    }
  }
}

void antecessor(TApontador apontador, int indice, TApontador apontadorPai,
                short *diminuiu) {
  if (apontadorPai->apontadoresPagina[apontadorPai->n] != NULL) {
    antecessor(apontador, indice,
               apontadorPai->apontadoresPagina[apontadorPai->n], diminuiu);
    if (*diminuiu)
      reconstitui(apontadorPai->apontadoresPagina[apontadorPai->n],
                  apontadorPai, (long)apontadorPai->n, diminuiu);
    return;
  }
  apontador->itensPagina[indice - 1] =
      apontadorPai->itensPagina[apontadorPai->n - 1];
  apontadorPai->n--;
  *diminuiu = (apontadorPai->n < M);
}

void ret(ITEM item, TApontador *apontador, short *diminuiu) {
  long j, indice = 1;
  TApontador pagina;
  if (*apontador == NULL) {
    printf("Erro: registro nao esta na arvore\n");
    *diminuiu = FALSE;
    return;
  }
  pagina = *apontador;
  while (indice < pagina->n && item > pagina->itensPagina[indice - 1].item)
    indice++;

  if (item == pagina->itensPagina[indice - 1].item) {
    if (pagina->apontadoresPagina[indice - 1] == NULL) /* TPagina folha */ {
      pagina->n--;
      *diminuiu = (pagina->n < M);          // Detecta underflow
      for (j = indice; j <= pagina->n; j++) // Deslocando vetor
      {
        pagina->itensPagina[j - 1] = pagina->itensPagina[j];
        pagina->apontadoresPagina[j] = pagina->apontadoresPagina[j + 1];
      }
      return;
    }
    /* A página em questão não é folha, então realizamos a troca com o
     * antecessor imediato do mesmo */
    antecessor(*apontador, indice, pagina->apontadoresPagina[indice - 1],
               diminuiu);
    if (*diminuiu)
      reconstitui(pagina->apontadoresPagina[indice - 1], *apontador, indice - 1,
                  diminuiu);
    return;
  }
  if (item > pagina->itensPagina[indice - 1].item)
    indice++;
  ret(item, &pagina->apontadoresPagina[indice - 1], diminuiu);
  if (*diminuiu)
    reconstitui(pagina->apontadoresPagina[indice - 1], *apontador, indice - 1,
                diminuiu);
}

void retira(ITEM item, TApontador *apontador) {
  short diminuiu;
  TApontador apontadorAux;
  ret(item, apontador, &diminuiu);
  if (diminuiu && (*apontador)->n == 0) /* Arvore diminui na altura */
  {
    apontadorAux = *apontador;
    *apontador = apontadorAux->apontadoresPagina[0]; // Elimina antiga raiz
    free(apontadorAux);
  }
}

void imprimeInterface(TApontador apontador, int nivel) {
  long i;
  if (apontador == NULL)
    return;
  printf("Nivel %d : ", nivel);
  for (i = 0; i < apontador->n; i++)
    printf("%ld ", (long)apontador->itensPagina[i].item);
  putchar('\n');
  nivel++;
  for (i = 0; i <= apontador->n; i++)
    imprimeInterface(apontador->apontadoresPagina[i], nivel);
}

void imprime(TApontador apontador) {
  int nivel = 0;
  imprimeInterface(apontador, nivel);
}

// void TestaI(TApontador apontador, int pai, short direita) {
//   int i;
//   int antecessor = 0;
//   if (apontador == NULL)
//     return;
//   if (apontador->itensPagina[0].item > pai && direita == FALSE) {
//     printf("Erro: filho %12ld maior que pai %d\n",
//            apontador->itensPagina[0].item, pai);
//     return;
//   }
//   for (i = 0; i < apontador->n; i++) {
//     if (apontador->itensPagina[i].item <= antecessor) {
//       printf("Erro: irmao %ld maior que irmao a esquerda %d\n",
//              (long)apontador->itensPagina[i].item, antecessor);
//       return;
//     }
//     antecessor = apontador->itensPagina[i].item;
//   }
//   for (i = 0; i < apontador->n; i++)
//     TestaI(apontador->apontadoresPagina[i], apontador->itensPagina[i].item,
//            FALSE);
//   TestaI(apontador->apontadoresPagina[apontador->n],
//          apontador->itensPagina[i].item, TRUE);
// }

// void testa(TApontador p) {
//   int i;
//   if (p == NULL)
//     return;
//   for (i = 0; i < p->n; i++)
//     TestaI(p->apontadoresPagina[i], p->itensPagina[i].item, FALSE);
//   TestaI(p->apontadoresPagina[p->n], p->itensPagina[i].item, TRUE);
// }

int main(int argc, char *argv[]) {

  TRegistro x;
  TPagina *arvB;

  inicializa(&arvB);
  x.item = 2;
  insere(x, &arvB);

  x.item = 12;
  insere(x, &arvB);

  x.item = 4;
  insere(x, &arvB);

  x.item = 5;
  insere(x, &arvB);

  x.item = 6;
  insere(x, &arvB);

  x.item = 23;
  insere(x, &arvB);

  x.item = 32;
  insere(x, &arvB);

  x.item = 7;
  insere(x, &arvB);

  x.item = 8;
  insere(x, &arvB);

  x.item = 9;
  insere(x, &arvB);

  x.item = 10;
  insere(x, &arvB);

  x.item = 14;
  insere(x, &arvB);

  x.item = 18;
  insere(x, &arvB);

  x.item = 27;
  insere(x, &arvB);

  x.item = 28;
  insere(x, &arvB);

  x.item = 33;
  insere(x, &arvB);

  x.item = 30;
  insere(x, &arvB);

  retira(23, &arvB);
  imprime(arvB);

  // printf("############################################################\n");
  // TRegistro itemRegistro;
  // TPagina *arvB_exemplo2;
  // inicializa(&arvB_exemplo2);
  // printf("item: ");
  // scanf("%ld%*[^\n]", &itemRegistro.item);
  // getchar();
  // while (itemRegistro.item != 0) {
  //   insere(itemRegistro, &arvB_exemplo2);
  //   imprime(arvB_exemplo2);
  //   // inOrder(arvB_exemplo2);
  //   printf("\n");
  //   printf("item: ");
  //   scanf("%ld%*[^\n]", &itemRegistro.item);
  //   getchar();
  // }

  // imprime(arvB_exemplo2);

  
  //printf("############################################################\n");
  // printf("item: ");
  // scanf("%ld%*[^\n]", &x.item);
  // getchar();
  // while (x.item != 0) {
  //   retira(x.item, &arvB);
  //   imprime(arvB);
  //   printf("item: ");
  //   scanf("%ld%*[^\n]", &x.item);
  //   getchar();
  // }
  // testa(arvB);
  return 0;
}