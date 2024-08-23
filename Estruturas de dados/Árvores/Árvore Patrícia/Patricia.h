#ifndef TADPATRICIA_H
#define TADPATRICIA_H

#ifdef __cplusplus
extern "C" {
#endif

#define TRUE 1
#define FALSE !TRUE
#define D 8

typedef  char *ITEM;
typedef  short boolean;

// Tipos do nós da Árvore PATRICIA
typedef enum
{
  Interno, Externo
} TipoNo;

typedef struct TipoPatNo *ARVORE_PATRICIA;
typedef struct TipoPatNo
{
    TipoNo nt;
    union
    {
        struct
        {
            short Index;
            char Caractere;
            ARVORE_PATRICIA Esq, Dir;
        } NInterno ;
        ITEM Chave;
    } NO;
} TipoPatNo;


// Assinaturas das Funções
  
char Caractere(short i, ITEM k);
  
boolean MenorIgual(char a, char b);
  
void inicializar(ARVORE_PATRICIA *arvore);
  
boolean EExterno(ARVORE_PATRICIA p);
  
ARVORE_PATRICIA CriaNoInt(short i, ARVORE_PATRICIA *Esq,  ARVORE_PATRICIA *Dir, char Caractere);
  
ARVORE_PATRICIA CriaNoExt(ITEM k);
  
boolean Pesquisa(ITEM k, ARVORE_PATRICIA t);
  
void imprime(ARVORE_PATRICIA t);
  
void printNo(ARVORE_PATRICIA no);
  
ARVORE_PATRICIA InsereEntre(ITEM k, ARVORE_PATRICIA *t, short i);
  
ARVORE_PATRICIA Insere(ITEM k, ARVORE_PATRICIA *t);
  
void Ordem(ARVORE_PATRICIA ap);
  
boolean Remover(ITEM k, ARVORE_PATRICIA *t);
  
#ifdef __cplusplus
}
#endif

#endif /* TADPATRICIA_H */