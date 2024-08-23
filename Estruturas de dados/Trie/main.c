#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "TRIE.h"

void testarBuscar (TRIE *t, char *texto)
{
  if (buscar(t,texto) == true)
    printf ("%s está na TRIE\n", texto);
  else
    printf ("%s Não está na TRIE\n", texto);
}

void testarRemover(TRIE**t, char *texto)
{
  if (deletar(t,texto) == true)
    printf ("String removida\n");
  else
    printf ("Não foi possivel encontrar a String\n");
}

void testarListar (TRIE *t)
{
  if (t == NULL){
    return;
    printf("Vazio");// caso em que a TRIE está vazia
  }
  listarRecursivo(t, NULL, 0);
}

void testarAutoCompletar(TRIE *t)
{
  inserir(&t, "bola");
  inserir(&t, "bolacha");
  inserir(&t, "boladassa");
  inserir(&t, "bolado");
  inserir(&t, "boleiro");
  inserir(&t, "bolo");
  inserir(&t, "bolona");
  inserir(&t, "bolonha");

  char palavra[50];
  scanf("%s", palavra);

  autoCompletar(t, palavra);
}



int main() 
{
  TRIE *t = criarNo();
  int opcao;
  while (true)
    {
    printf("---------------------\n");
    printf("1 -- Inserir\n2 -- Remover\n3 -- Listar\n4 -- Procurar\n5 -- Auto Completar\n");
    printf("---------------------\n");
    printf("R : ");
    scanf("%d", &opcao);
    printf("\n");
    switch(opcao)
    {
      case 1:
          printf("Insira o texto : ");
          char texto[50];
          scanf(" %49[^\n]s", texto);
          inserir(&t, texto);
          break;
      case 2:
          printf("Insira o texto : ");
          char textor[50];
          scanf(" %49[^\n]s", textor);
          testarRemover(&t, textor);
          if (t == NULL)
            t = criarNo();
          break;
      case 3:
          testarListar(t);
          break;
      case 4:
          printf("Insira o texto : ");
          char textos[50];
          scanf(" %49[^\n]s", textos);
          testarBuscar(t, textos);
          break;
      case 5:
          printf("Insira a palavra : ");
          testarAutoCompletar(t);
          break;
    }
  
   }
  
  return 0;
}
