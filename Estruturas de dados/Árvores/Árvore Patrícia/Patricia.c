#include <stdio.h>
#include <stdlib.h>
#include "Patricia.h"

char Caractere(short i, ITEM k)
{
    /* Retorna o i-esimo Caractere da chave k a partir da esquerda */
    return i > strlen(k)? NULL: k[i];
}

// Compara os valores de a e b. Se a for menor ou igual a b, a função retorna TRUE, caso contrário, ela retorna FALSE.

boolean MenorIgual(char a, char b)
{
    if(a == NULL)
       return NULL;
    if( b == NULL)
       return NULL;
    return a <= b ? TRUE:FALSE;
}

void inicializar(ARVORE_PATRICIA *arvore)
{
    arvore = NULL;
}

// A função verifica se o campo nt da estrutura do nó p é igual a Externo (como definido no enum TipoNo)
boolean EExterno(ARVORE_PATRICIA p)
{
    /* Verifica se p^ e nó externo */
    return (p->nt == Externo)?TRUE:FALSE; 
}

// Cria um novo nó interno com índice i, ponteiros Esq e Dir e char Caractere
ARVORE_PATRICIA CriaNoInt(short i, ARVORE_PATRICIA *Esq,  ARVORE_PATRICIA *Dir, char Caractere)
{
    ARVORE_PATRICIA p;
    p = (ARVORE_PATRICIA)malloc(sizeof(TipoPatNo));
    p->nt = Interno;
    // Define os ponteiros para os filhos esquerdo e direito do nó interno, copiando os valores dos ponteiros passados como argumento
    p->NO.NInterno.Esq = *Esq;
    p->NO.NInterno.Dir = *Dir;
    p->NO.NInterno.Index = i;
    p->NO.NInterno.Caractere = Caractere;
    return p;
}

// Esta função cria um novo nó externo com a chave k
ARVORE_PATRICIA CriaNoExt(ITEM k)
{
    ARVORE_PATRICIA p;
    p = (ARVORE_PATRICIA)malloc(sizeof(TipoPatNo));
    p->nt = Externo;
    p->NO.Chave = k;
    return p;
}

// Busca se um dado ITEM está presente na Árvore, se estiver retorna Verdadeiro, senão Falso 
boolean Pesquisa(ITEM k, ARVORE_PATRICIA t)
{
    if (EExterno(t))
    {
        if (strncmp(k,t->NO.Chave,strlen(k)) == 0){
          return TRUE;
        }
       else{
          return FALSE;
       }
    }
    if (MenorIgual(Caractere(t->NO.NInterno.Index, k),t->NO.NInterno.Caractere))
        return Pesquisa(k, t->NO.NInterno.Esq);
    else return Pesquisa(k, t->NO.NInterno.Dir);

}

// Imprime a Árvore
void imprime(ARVORE_PATRICIA t) 
{
    if (t == NULL) {
        return;
    }

    if (EExterno(t)) {
        printf("%s\n", t->NO.Chave);
    } else {
        imprime(t->NO.NInterno.Esq);
        imprime(t->NO.NInterno.Dir);
    }
}

void printNo(ARVORE_PATRICIA no)
{
    // Verifica se o nó é nulo
    if (no == NULL)
        printf("No Nulo\n");
    else if (no->nt == Externo)
    {
        // Imprime informações de um nó externo 
        printf("No{\n Tipo: Externo\n Chave:%s\n};\n", no->NO.Chave);
    }
    /*else{
        printf("No{\n Tipo: Interno\n Indice: %d\n Caractere: %c\n};\n",no->NO.NInterno.Index,no->NO.NInterno.Caractere);
    }*/
}
 //função que insere uma chave k entre os nós
ARVORE_PATRICIA InsereEntre(ITEM k, ARVORE_PATRICIA *t, short i)
{
    ARVORE_PATRICIA p;
    char caractere;
    if (EExterno(*t) || i < (*t)->NO.NInterno.Index)
    {
//// Verifica se a árvore é externa ou se o índice i é menor que o índice do nó interno
        if (EExterno(*t)){
// Se a árvore for externa, determina o caractere associado
            caractere = Caractere(i, (*t)->NO.Chave);
        }
        else{           // Se a árvore for interna, determina o caractere associado
            caractere = (*t)->NO.NInterno.Caractere;
        } // Cria um novo nó externo com a chave k
        p = CriaNoExt(k);
        // Compara o caractere de k com o caractere associado e insere à esquerda ou à direita
        if (MenorIgual(Caractere(i, k), caractere))
            return (CriaNoInt(i, &p, t, Caractere(i, k)));
        else
            return (CriaNoInt(i, t, &p, caractere));
    }
    else
    {
	        // Caso contrário (se o nó atual for interno)  Compara o caractere de k com o caractere associado ao nó interno atual
        if (MenorIgual(Caractere((*t)->NO.NInterno.Index, k), (*t)->NO.NInterno.Caractere))
            (*t)->NO.NInterno.Esq = InsereEntre(k, &(*t)->NO.NInterno.Esq, i);
        else
            (*t)->NO.NInterno.Dir = InsereEntre(k, &(*t)->NO.NInterno.Dir, i);
        return (*t);
    }
}
ARVORE_PATRICIA Insere(ITEM k, ARVORE_PATRICIA *t)
{
    ARVORE_PATRICIA p;
    int i;
    
    // Verifica se a árvore é nula (vazia)
    if (*t == NULL){
        // Se for nula, cria um novo nó externo com a chave k e retorna a raiz da árvore
        return (CriaNoExt(k));
    }
    else{
        // Caso contrário, a árvore não está vazia, então começa a busca pela posição correta para inserir k
        p = *t;
        while (!EExterno(p))
        {
            // Enquanto p não for um nó externo, navega na árvore com base na comparação de caracteres
            if (MenorIgual(Caractere(p->NO.NInterno.Index, k), p->NO.NInterno.Caractere))
                p = p->NO.NInterno.Esq; // Vai para o filho esquerdo
            else 
                p = p->NO.NInterno.Dir; // Vai para o filho direito
        }
        
        // Encontrou um nó externo, agora procura o primeiro caractere diferente
        i = 0;
        
        // Verifica o comprimento da chave atual e da nova chave k
        if (strlen(k) > strlen(p->NO.Chave)){
            while ((i <= strlen(k)) && (Caractere(i, k) == Caractere(i, p->NO.Chave)))
                i++;
            if (i >= strlen(k)){
                // Se i for igual ao comprimento de k, as chaves são idênticas, retorna a árvore original
                printf("Erro: chave já está na árvore: %s == %s\n", k, p->NO.Chave);
                return (*t);
            }
            else 
                // Chama a função InsereEntre para inserir k na posição correta e retorna a árvore atualizada
                return (InsereEntre(k, t, i));
        }
        else{
            // O mesmo processo é repetido, mas agora comparando com a chave existente
            while ((i <= strlen(p->NO.Chave)) && (Caractere(i, k) == Caractere(i, p->NO.Chave)))
                i++;
            if (i >= strlen(p->NO.Chave)){
                printf("Erro: chave já está na árvore: %s == %s\n", k, p->NO.Chave);
                return (*t);
            }
            else 
                return (InsereEntre(k, t, i));
        }
    }
}
//função para visitar todos os nós em ordem crescente
void Ordem(ARVORE_PATRICIA ap)
{
    // Verifica se o nó atual é nulo (vazio)
    if (ap == NULL)
        return; // Se for nulo, retorna sem fazer nada

    // Verifica se o nó atual não é externo (é interno)
    if (!EExterno(ap))
    {
        // Se não for externo, chama a função Ordem recursivamente para o filho esquerdo
        Ordem(ap->NO.NInterno.Esq);
    }

    // Imprime o nó atual
    printNo(ap);

    // Verifica se o nó atual não é externo (é interno)
    if (!EExterno(ap))
    {
        // Se não for externo, chama a função Ordem recursivamente para o filho direito
        Ordem(ap->NO.NInterno.Dir);
    }
}
// Precisa de Melhorias
boolean Remover(ITEM k, ARVORE_PATRICIA *t) {
    if (*t == NULL) {
        // Árvore vazia, a palavra não está presente
        return FALSE;
    }

    if (EExterno(*t)) {
        if (strcmp(k, (*t)->NO.Chave) == 0) {
            // Encontrou a palavra, remove
            free((*t)->NO.Chave); // Libera a memória alocada para armazenar a palavra no nó folha
            free(*t); // Libera a memória alocada para o próprio nó folha
            *t = NULL;
            return TRUE;
        } else {
            // A palavra não está presente
            return FALSE;
        }
    }

    // Não é um nó externo, continue a busca
    if (MenorIgual(Caractere((*t)->NO.NInterno.Index, k), (*t)->NO.NInterno.Caractere)) {
        if (Remover(k, &(*t)->NO.NInterno.Esq)) {
            // Verifique se o filho esquerdo foi removido e ajuste a árvore
            if (EExterno((*t)->NO.NInterno.Esq)) {
                ARVORE_PATRICIA temp = (*t)->NO.NInterno.Esq;
                free(*t);
                *t = temp;
            }
            return TRUE;
        }
    } else {
        if (Remover(k, &(*t)->NO.NInterno.Dir)) {
            // Verifique se o filho direito foi removido e ajuste a árvore
            if (EExterno((*t)->NO.NInterno.Dir)) {
                ARVORE_PATRICIA temp = (*t)->NO.NInterno.Dir;
                free(*t);
                *t = temp;
            }
            return TRUE;
        }
    }

    return FALSE;
}






