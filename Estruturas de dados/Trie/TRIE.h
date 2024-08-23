#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#ifndef TRIE_FUNCTIONS
#define TRIE_FUNCTIONS

#define alfabeto 256

typedef struct TRIE 
{
  bool final;
  struct TRIE *filhos[alfabeto];
} TRIE;


// Cria um novo Nó 
TRIE* criarNo();

// Insere uma string na TRIE
bool inserir (TRIE **t,char* texto);

// Lista todas as strings presentes na TRIE
void listarRecursivo (TRIE *t, char *prefixo,int tamanho);

// Busca e verifica se uma palavra está na TRIE
bool buscar (TRIE *t, char *texto);

// Deleta uma String da Trie
bool deletar(TRIE** t,char * texto);

// Deleta uma palavra da TRIE
TRIE* deletarRecursivo(TRIE * no, char *texto, bool * deletado);

// Verifica se um determinado nó possui algum filho
bool temFilhos (TRIE *t);

// Dado um prefixo, presente na TRIE, devolve um ponteiro para o nó do último caractere
TRIE* posicionaNo(TRIE *t, char *prefixo);

// Dado um prefixo, presente na TRIE, salva a menor palavra possível a partir do prefixo no endereço apontado por menorString
void pegaMenorPalavra (TRIE *t, char *prefixo, int tamanho, char *menorString);

// Completa a palavra com base nas presentes na TRIE
void autoCompletar(TRIE *t, char *palavra);

#endif // TRIE_FUNCTIONS