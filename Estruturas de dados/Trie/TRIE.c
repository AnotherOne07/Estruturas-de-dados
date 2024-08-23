#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "TRIE.h"

#define alfabeto 256

TRIE* criarNo()  // Cria um no que aponta para i valores do alfabeto 
{
  TRIE *t = (TRIE*) malloc(sizeof(TRIE));
  for (int i = 0 ; i < alfabeto ; i++)
    t->filhos[i] = NULL; // para todos os possiveis valores do alfabeto um ponteiro é criado
    
  t->final = false;
  return t;
}

bool inserir (TRIE **t, char *texto)
{
  TRIE *temp = *t;
  int tamanho = strlen(texto);

  for (int i = 0 ; i < tamanho ; i++) // percorre do valor 0 até a última letra
    {
      if (temp->filhos[texto[i]] == NULL) // Se o nó com o valor i não existir cria um novo nó
        temp->filhos[texto[i]] = criarNo(); // o caractere escolhido é transformado em ASCII e é acessado seu indice no array filhos
      temp = temp->filhos[texto[i]];
    }
  if (temp->final == true)
    return false; // a palavra inserida já está na árvore
  
  temp->final = true; // o ultimo caractere não era terminal logo a palavra foi inserida
  return true;
}

void listarRecursivo (TRIE *t, char *prefixo, int tamanho) 
{ 
  char novoPrefixo[tamanho+2]; // Garante que haja espaço para um novo caractere e o caractere vazio \0
  memcpy(novoPrefixo, prefixo, tamanho); // Copia os dados de prefixo para o novoPrefixo
  novoPrefixo[tamanho+1] = 0;
    
  if (t->final)// Atribui o caracter nulo ao final da string
    printf("PALAVRA : %s\n", prefixo); // Imprime uma palavra caso um ponto terminal seja encontrado

  for (int i = 0 ; i < alfabeto ; i++)
  {
    if (t->filhos[i] != NULL)
    {
      novoPrefixo[tamanho] = i; // Adiciona o caractere novo no prefixo
      listarRecursivo(t->filhos[i], novoPrefixo, tamanho+1);
    }
  }  
}

bool buscar (TRIE *t, char *texto)
{
  int tamanho = strlen(texto);
  TRIE *temp = t; // No temporario
  
  if (t == NULL) // No raiz nao inicializado
    return false;
  
  for (int i = 0; i < tamanho ; i++)
    {
      if (temp->filhos[texto[i]] == NULL) // neste caso um determinado filho do nó ainda não existe, logo a palavra não existe na minha trie
        return false;
      temp = temp->filhos[texto[i]];
    }
  return temp->final; // retorna o valor do terminal. true se for um no final e false caso contrário
}

bool temFilhos (TRIE *t)
{
  if (t == NULL)
    return false;

  for (int i = 0 ; i < alfabeto ; i++)
    {
      if (t->filhos[i] != NULL)
        return true; // Caso exista algum filho a funcao retorna verdadeiro
    }
  return false;
}

TRIE* deletarRecursivo(TRIE *no, char *texto, bool *deletado)
{
  if (*texto == '\0') // Caso base
  {
    if (no->final)
    {
      no->final = false; // O nó não é mais final após ser deletado
      *deletado = true;
      if (temFilhos(no) == false) // caso em que é retirado o valor terminal de um nó sem filhos
      {
        free(no);
        no = NULL;
      }
      return no;
    }
  }
  no->filhos[texto[0]] = deletarRecursivo(no->filhos[texto[0]],texto + 1, deletado);
  if (*deletado && temFilhos(no) == false && no->final == false) // após realizar tudo checa se é possível liberar outros nós
  {
    free(no);
    no = NULL;
  }
  return no;
}

bool deletar(TRIE **t, char *texto)
{
  if (t == NULL)
    return false;
  if (buscar(*t, texto) == false) // Busco no inicio para evitar gastos na recursao
    return false;
  bool resultado = false; // variavel que me diz se algo foi removido
  *t = deletarRecursivo(*t, texto, &resultado); 
  return true;
}



// ---------------------------------- APLICAÇÃO TRIE ---------------------------------------



void pegaMenorPalavra (TRIE *t, char *prefixo, int tamanho, char *menorString)
{
  char novoPrefixo[tamanho+2]; // garante que haja espaço para um novo caractere e o caractere vazio 0/
  strcpy(novoPrefixo, prefixo); // copia os dados de prefixo para o novoprefixo
  novoPrefixo[tamanho+1] = 0; // atribui o caracter nulo ao final da string
  
  if (t->final)
  {   
    if (menorString[0] == 0) // Caso seja a primeira palavra encontrada atribui como a menor
      strcpy(menorString, prefixo);
      
    else if (strlen(prefixo) < strlen(menorString)) // menorString vira o prefixo, caso ele seja menor
      strcpy(menorString, prefixo);
  }

  for (int i = 0 ; i < alfabeto ; i++)
  {
    if (t->filhos[i] != NULL)
    {
      novoPrefixo[tamanho] = i;
      pegaMenorPalavra(t->filhos[i], novoPrefixo, tamanho+1, menorString);
    }
  }  
}

TRIE* posicionaNo (TRIE *t, char *prefixo)
{
  TRIE *temp = t;
  int tamanho = strlen(prefixo);

  for(int i = 0; i < tamanho; i++)
    {
      if (temp->filhos[prefixo[i]] == NULL)
        return NULL;
      temp = temp->filhos[prefixo[i]];
    }

  return temp;
}

void autoCompletar(TRIE *t, char *palavra)
{
  TRIE* tNo;
  char textoCorrigido[50];
  textoCorrigido[0] = '\0'; // Inicializa como caractere nulo
  
  tNo = posicionaNo(t, palavra); // Posiciona o no na ultima letra da palavra
  if (tNo == NULL) 
  {
    printf("\nNenhuma palavra parecida com essa no dicionario\n\n");
    return;
  }
  
  pegaMenorPalavra(tNo, palavra, strlen(palavra), textoCorrigido);
  printf("\nPalavra Sugerida : ");
  printf("%s\n\n", textoCorrigido);
  
  
}
