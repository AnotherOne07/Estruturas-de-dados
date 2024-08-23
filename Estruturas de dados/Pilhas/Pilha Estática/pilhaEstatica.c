#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef char ITEM;

typedef struct estrutura
{
    ITEM item;
    struct estrutura *prox;
} NO;

typedef struct
{
    int capacidade;
    ITEM* itens; //Ponteiro para um vetor
    int tamanho;
} PILHA;

void testarInicializar(PILHA* p);
void testarEmpilhar(PILHA* p);
void testarDesempilhar(PILHA* p);
void testarCompactar(PILHA* p);
void testarParenteses(PILHA* p);
void imprimirPilha(PILHA* p);

bool desempilhar(ITEM *item, PILHA* p);
bool inicializar(PILHA *p, int capacidade);
bool cheia(PILHA* p);
bool empilhar(ITEM item, PILHA* p);
bool compactar(PILHA* p);
bool paranteses(char *expressao, PILHA* p);


///////////////// MAIN //////////////////////////////////


int main(void) {
  PILHA p;
  ITEM item;
  int numItens;
  
  printf("Inicializando Pilha...");
  testarInicializar(&p);
  testarParenteses(&p);
  /*testarEmpilhar(&p);
  testarDesempilhar(&p);
  testarCompactar(&p);*/
  
  return 0;
}


///////////////// FUNCOES TESTE ///////////////////////


void testarInicializar(PILHA* p)
{
  int capacidade;

  printf("\nInsira a capacidade inicial da pilha : ");
  scanf("%d", &capacidade);
  inicializar(p, capacidade);
}

void imprimirPilha(PILHA* p)
{
  printf("\n");
  printf("PILHA : ");
  for(int i = 0; i < p->tamanho; i++)
    printf("%d ", p->itens[i]);
}

void testarEmpilhar(PILHA* p)
{
  ITEM item;
  int numItens;
  
  printf("\nQuantos itens deseja empilhar ? ");
  scanf("%d", &numItens);
  for (int i = 0; i < numItens; i++)
    {
      printf("Digite o item a empilhar : ");
      scanf("%d", &item);
      if (!(empilhar(item, p)))
      {
        printf("Pilha cheia !!!!");
        return;
      }
    }
  imprimirPilha(p);
}

void testarDesempilhar(PILHA* p)
{
  ITEM item;

  desempilhar(&item, p);
  printf("\nItem desempilhado : %d", item);
  imprimirPilha(p);
}

void testarCompactar(PILHA* p)
{
  printf("\n=> Testar Compactar\n");
  compactar(p);
  imprimirPilha(p);
  printf("Capacidade da Pilha : %d", p->capacidade);
}

void testarParenteses(PILHA* p)
{
  char *expressao;
  
  printf("\n=> Testar Parenteses");
  printf("\nDigite a Expressão : ");
  fgets(expressao, 100, stdin);
  if(paranteses(expressao, p))
    printf("Expressao Correta");
  else
    printf("Expressao Incorreta");
}

///////////////// FUNCOES ///////////////////////


bool inicializar(PILHA *p, int capacidade)
{
  ITEM* listaPilha = (ITEM*) malloc(sizeof(ITEM)*capacidade);
  if(listaPilha)
  {
    p->itens = listaPilha;
    p->capacidade = capacidade;
    p->tamanho = 0;
    return true;
  }
  return false;
}

bool cheia(PILHA* p)
{
  return p->tamanho == p->capacidade;
}

bool vazia(PILHA* p)
{
  return p->tamanho == 0;
}

bool empilhar(ITEM item, PILHA* p)
{
  if(cheia(p))
  {
    ITEM* listaPilhaNova = (ITEM*) realloc(p->itens, sizeof(ITEM)*p->capacidade*2);
    if(!(listaPilhaNova))
      return false;
  }
  
  p->itens[p->tamanho] = item;
  p->tamanho++;
  return true;
    
}

bool desempilhar(ITEM *item, PILHA* p)
{
  if (vazia(p))
    return false;
  *item = p->itens[p->tamanho - 1];
  p->tamanho--;
  return true;
}


bool compactar(PILHA* p)
{
  int metade = (p->capacidade) / 2;
  
  if(metade < p->tamanho)
    return false;
  
  while(metade >= p->tamanho)
  {
    if(metade / 2 < p->tamanho) break;
    metade = metade / 2;
  }

  printf("METADE : %d", metade);
  ITEM* listaPilhaNova = (ITEM*) realloc(p->itens, sizeof(ITEM)*metade);
  if (!(listaPilhaNova))
    return false;

  p->itens = listaPilhaNova;
  p->capacidade = metade;
  return true;
}

bool paranteses(char *expressao, PILHA* p)
{
  char item;
  
  for(int i = 0; expressao[i] == '\0'; i++)
  {
    if (expressao[i] == '(')
      empilhar('(', p);
      
    else if (expressao[i] == ')')
      if (!(desempilhar(&item, p)))
        return false;
  }
  
  if (vazia(p))
    return true;

  return false;
}