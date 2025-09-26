#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ABB.h"

NoABB* criarNoABB(Citacao tripla) {
    NoABB* novoNo = (NoABB*)malloc(sizeof(NoABB));  // Aloca memória para o novo nó

    if (novoNo == NULL) {
        printf("Erro ao alocar memória para o novo nó.\n");
        exit(1);
    }

    novoNo->tripla = tripla;
    novoNo->Esq = NULL;
    novoNo->Dir = NULL;

    return novoNo;
}

RepositorioABB inserirABB(RepositorioABB raiz, Citacao t) {
    if (raiz == NULL) {
        raiz = criarNoABB(t);
      return raiz;
    }
    else {
        int comparacao = strcmp(t.palavra, raiz->tripla.palavra);
        if (comparacao < 0) {
            raiz->Esq = inserirABB(raiz->Esq, t);
        } 
        else if (comparacao > 0) {
            raiz->Dir = inserirABB(raiz->Dir, t);
        } 
        else {
          for(int i = 0; i < t.frequencia; i++){
            inserirOffset(&raiz->tripla, t.dados[i]);
          }
        }
    }
    return raiz;
}

RepositorioABB buscarABB(RepositorioABB raiz, char* palavraChave) {
    if (raiz == NULL) {
        // A árvore está vazia ou a palavra-chave não foi encontrada, retorne NULL.
        return NULL;
    }

    int comparacao = strcmp(palavraChave, raiz->tripla.palavra);

    if (comparacao == 0) {
        // A palavra-chave foi encontrada neste nó, retorne o nó atual.
        return raiz;
    } else if (comparacao < 0) {
        // A palavra-chave é menor do que a palavra-chave no nó atual, portanto, continue a busca na subárvore esquerda.
        return buscarABB(raiz->Esq, palavraChave);
    } else {
        // A palavra-chave é maior do que a palavra-chave no nó atual, portanto, continue a busca na subárvore direita.
        return buscarABB(raiz->Dir, palavraChave);
    }
}

RepositorioABB removerABB(RepositorioABB raiz, char* palavraChave) {
    if (raiz == NULL) {
        // Caso base: a árvore está vazia ou a palavra-chave não foi encontrada, retorne NULL.
        return NULL;
    }

    int comparacao = strcmp(palavraChave, raiz->tripla.palavra);

    if (comparacao < 0) {
        // A palavra-chave é menor do que a palavra-chave no nó atual, continue a busca na subárvore esquerda.
        raiz->Esq = removerABB(raiz->Esq, palavraChave);
    } else if (comparacao > 0) {
        // A palavra-chave é maior do que a palavra-chave no nó atual, continue a busca na subárvore direita.
        raiz->Dir = removerABB(raiz->Dir, palavraChave);
    } else {
        // Caso contrário, a palavra-chave foi encontrada neste nó.
        if (raiz->Esq == NULL) {
            // Se não houver subárvore esquerda, simplesmente libere o nó atual e retorne o nó direito.
            NoABB* temp = raiz;
            raiz = raiz->Dir;
            free(temp);
        } else if (raiz->Dir == NULL) {
            // Se não houver subárvore direita, simplesmente libere o nó atual e retorne o nó esquerdo.
            NoABB* temp = raiz;
            raiz = raiz->Esq;
            free(temp);
        } else {
            // Se o nó a ser removido tiver ambos os filhos, encontre o nó mais à esquerda na subárvore direita
            // para substituir o nó a ser removido e atualize a árvore.
            NoABB* temp = encontrarMinimoABB(raiz->Dir);
            raiz->tripla = temp->tripla;
            raiz->Dir = removerABB(raiz->Dir, temp->tripla.palavra);
        }
    }
    return raiz;
}

NoABB* encontrarMinimoABB(RepositorioABB raiz) {
    // Função auxiliar para encontrar o nó com a palavra-chave mínima na árvore.
    while (raiz->Esq != NULL) {
        raiz = raiz->Esq;
    }
    return raiz;
}

void centralABB(RepositorioABB raiz) {
    if (raiz != NULL) {
        // Percorre a subárvore esquerda
        centralABB(raiz->Esq);

        // Processa o nó atual (por exemplo, imprime a palavra-chave)
        printf("%s\n", raiz->tripla.palavra);

        // Percorre a subárvore direita
        centralABB(raiz->Dir);
    }
}

void liberarABB(RepositorioABB raiz) {
    if (raiz != NULL) {
        // Libera a subárvore esquerda
        liberarABB(raiz->Esq);

        // Libera a subárvore direita
        liberarABB(raiz->Dir);

        // Libera a memória alocada para a palavra-chave no nó
        free(raiz->tripla.palavra);

        // Libera a memória alocada para o nó
        free(raiz);
    }
}

void preencheABB(RepositorioABB *r, CitacoesArquivo dados, int qtdLinhas){
  char **palavrasValidasCit;
  char temp[MAX_WORDS];
  int nPalavrasValidas = 0;
  indice id;
  int p;
  Citacao *atual;

  for(int i = 0; i < qtdLinhas; i++){
    id = dados[i].offset;
    strcpy(temp, dados[i].cit);
    palavrasValidasCit = getPalavraCitacao(temp, &nPalavrasValidas);
    for(int j = 0; j < nPalavrasValidas; j++){
      processaString(palavrasValidasCit[j]);

      atual = criaCitacao(palavrasValidasCit[j]);
      p = inserirOffset(atual, id);

      *r = inserirABB(*r, *atual);
    }
  }
}
