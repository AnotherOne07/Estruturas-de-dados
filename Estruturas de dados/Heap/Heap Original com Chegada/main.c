#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "heap.h"

int main() {
    HEAP heap;
    inicializar(&heap);

    int opcao, elemento, prioridade, indice;

    do {
        printf("\nMenu:\n");
        printf("1. Inserir elemento\n");
        printf("2. Inserir varios elementos\n");
        printf("3. Remover elemento\n");
        printf("4. Alterar elemento de uma certa posição\n");
        printf("5. Buscar elemento\n");
        printf("6. Exibir heap\n");
        printf("7. Limpar heap\n");
        printf("8. Ordenar heap\n");
        printf("9. Corrigir heap\n");
        printf("10. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite o elemento a ser inserido: ");
                scanf("%d", &elemento);
                printf("Digite a prioridade dele: ");
                scanf("%d", &prioridade);
                bool deuCerto = inserir(elemento, prioridade, &heap);
                if(deuCerto)
                  printf("\n\nElemento inserido com sucesso!\n\n");
                else
                  printf("\n\nErro ao inserir elemento\n\n");
                break;

            case 2:
                while(true) {
                  printf("\n===Quando quiser parar de inserir itens, digite -1 para o campo prioridade===\n");
                  printf("Digite o elemento a ser inserido: ");
                  scanf("%d", &elemento);
                  
                  printf("Digite a prioridade dele: ");
                  scanf("%d", &prioridade);
                  
                  if(prioridade == -1)
                    break;
                  
                  bool deuCerto = inserir(elemento, prioridade, &heap);
                  if(deuCerto)
                    printf("\n\nElemento inserido com sucesso!\n\n");
                  else
                    printf("\n\nErro ao inserir elemento\n\n");
                }
                break;

            case 3:
                if (remover(&heap)) {
                    printf("\n\nElemento removido com sucesso!\n\n");
                } else {
                    printf("\n\nNão foi possível remover elemento.\n\n");
                }
                break;

            case 4:
                if(heap.tamanho == 0) {
                  printf("\n\nNao ha elementos para alterar!\n\n");
                  break;
                }
                printf("Insira o valor que quer colocar em lugar de outro: ");
                scanf("%d", &elemento);
                printf("Insira a prioridade dele: ");
                scanf("%d", &prioridade);
                printf("Agora escolha o indice em que quer inserir: ");
                scanf("%d", &indice);
                if(alterar(&heap, indice, elemento, prioridade)) {
                  printf("\n\nAlteracao realizada com sucesso!\n\n");
                } else {
                  printf("\n\nAlteracao nao funcionou!\n\n");
                }
                break;

            case 5:
              if(heap.tamanho == 0) {
                printf("\n\nNao ha nada para buscar... ಥ_ಥ\n\n");
                break;
              }
              printf("Digite o valor do elemento que deseja buscar: ");
              scanf("%d", &elemento);
              if(buscar(&heap, elemento)) {
                printf("\n\nElemento encontrado! (●'◡'●)\n\n");
              } else {
                printf("\n\nElemento nao encontrado... ಥ_ಥ\n\n");
              }
              break;
          
            case 6:
              imprimir(&heap);
              break;

            case 7:
              limpar(&heap);
              printf("\n\nHeap limpa!╰(*°▽°*)╯\n\n");
              break;

            case 8:
              if(heap.tamanho == 0) {
                printf("Nao foi possivel ordenar");
                break;
              }
              heapSort(&heap);
              printf("\nHeap ordenada! (●'◡'●)\n");
              break;

            case 9:
              corrigeHeap(&heap);
              printf("\nHeap corrigida! (^///^)\n");
              break;

            case 10:
              printf("\nSaindo do programa.\n");
              destruir(&heap);
              break;

            default:
              printf("\nOpcao invalida. Escolha uma opcao de 1 a 10.\n");
              break;
        }
              

    } while (opcao != 10);

    return 0;
}