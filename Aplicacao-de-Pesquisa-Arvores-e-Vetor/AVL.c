#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AVL.h"


RepositorioAVL *criarAVL(){ //mantem
  RepositorioAVL *raiz = (RepositorioAVL*) malloc(sizeof(RepositorioAVL));
    if(raiz != NULL)
        *raiz = NULL;
    return raiz;
}

void liberaNoAVL(NoAVL *no){ //mantem
    if(no == NULL)
        return;
    liberaNoAVL(no->esq);
    liberaNoAVL(no->dir);
    free(no);
    no = NULL;
}

void liberaAVL(RepositorioAVL *raiz){ //mantem
    if(raiz == NULL)
        return;
    liberaNoAVL(*raiz);
    free(raiz);
}

int alturaNoAVL(NoAVL *no){ //mantem
    if(no == NULL)
        return -1;
    else
    return no->altura;
}

int fatorBalanceamento(NoAVL *no){ //mantem
    return labs(alturaNoAVL(no->esq) - alturaNoAVL(no->dir));
}

int maior(int x, int y){
    if(x > y)
        return x;
    else
        return y;
}

int AVLvazia(RepositorioAVL *raiz){
    if(raiz == NULL)
        return 1;
    if(*raiz == NULL)
        return 1;
    return 0;
} //mantem

int totalNoAVL(RepositorioAVL *raiz){
    if (raiz == NULL)
        return 0;
    if (*raiz == NULL)
        return 0;
    int alt_esq = totalNoAVL(&((*raiz)->esq));
    int alt_dir = totalNoAVL(&((*raiz)->dir));
    return(alt_esq + alt_dir + 1);
} //mantem

int alturaAVL(RepositorioAVL *raiz){
    if (raiz == NULL)
        return 0;
    if (*raiz == NULL)
        return 0;
    int alt_esq = alturaAVL(&((*raiz)->esq));
    int alt_dir = alturaAVL(&((*raiz)->dir));
    if (alt_esq > alt_dir)
        return (alt_esq + 1);
    else
        return(alt_dir + 1);
} //mantem

//=================================
void preOrdemAVL(RepositorioAVL *raiz){
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        printf("%s: %d(altura)\n",(*raiz)->tripla.palavra, alturaNoAVL(*raiz));
        preOrdemAVL(&((*raiz)->esq));
        preOrdemAVL(&((*raiz)->dir));
    }
}

void emOrdemAVL(RepositorioAVL *raiz){
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        emOrdemAVL(&((*raiz)->esq));
        printf("%s: %d(altura) %d(fator balanceamento)\n", (*raiz)->tripla.palavra, alturaNoAVL(*raiz), fatorBalanceamento(*raiz));
        emOrdemAVL(&((*raiz)->dir));
    }
}

void posOrdemAVL(RepositorioAVL *raiz){
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        posOrdemAVL(&((*raiz)->esq));
        posOrdemAVL(&((*raiz)->dir));
        printf("%s\n",(*raiz)->tripla.palavra);
    }
}

//=================================
int verificaAVLPalavra(RepositorioAVL *raiz, char *palavra){
    if(raiz == NULL) return 0;
    NoAVL* atual = *raiz;
    while(atual != NULL){
      int comp = strcmp(palavra, atual->tripla.palavra);
      if(comp == 0) return 1;  //
      if(comp > 0) atual = atual->dir;
      else atual = atual->esq;
    }
    return 0;
} 

NoAVL *buscaAVLPalavra(RepositorioAVL *raiz, char *palavra){
  if(raiz == NULL) return NULL;
  if(verificaAVLPalavra(raiz, palavra) == 0) return NULL;
  
  NoAVL* atual = *raiz;
  int comp = strcmp(palavra, atual->tripla.palavra);

  if(comp < 0) return buscaAVLPalavra(&(atual->esq), palavra);
  
  if(comp > 0) return buscaAVLPalavra(&(atual->dir), palavra);

  else return *raiz;
}

//=================================
void RotacaoLL(RepositorioAVL *A){//LL
    NoAVL *B;
    B = (*A)->esq;
    (*A)->esq = B->dir;
    B->dir = *A;
    (*A)->altura = maior(alturaNoAVL((*A)->esq), alturaNoAVL((*A)->dir)) + 1;
    B->altura = maior(alturaNoAVL(B->esq),(*A)->altura) + 1;
    *A = B;
}

void RotacaoRR(RepositorioAVL *A){//RR
    NoAVL *B;
    B = (*A)->dir;
    (*A)->dir = B->esq;
    B->esq = (*A);
    (*A)->altura = maior(alturaNoAVL((*A)->esq), alturaNoAVL((*A)->dir)) + 1;
    B->altura = maior(alturaNoAVL(B->dir),(*A)->altura) + 1;
    (*A) = B;
}

void RotacaoLR(RepositorioAVL *A){//LR
    RotacaoRR(&(*A)->esq);
    RotacaoLL(A);
}

void RotacaoRL(RepositorioAVL *A){//RL
    RotacaoLL(&(*A)->dir);
    RotacaoRR(A);
}

NoAVL *procuraMenorAVL(NoAVL* atual){
    NoAVL *no1 = atual;
    NoAVL *no2 = atual->esq;
    while(no2 != NULL){
        no1 = no2;
        no2 = no2->esq;
    }
    return no1;
}

int inserirAVLPalavra(RepositorioAVL *raiz, Citacao c){
  if(*raiz == NULL){
    NoAVL *novo;
    novo = (NoAVL*)malloc(sizeof(NoAVL));
      
    if(novo == NULL) return 0;

    novo->tripla = c;
    novo->altura = 0;
    novo->esq = NULL;
    novo->dir = NULL;
    *raiz = novo;
    return 1;
  }

  NoAVL *atual = *raiz;

  int comp = strcmp(c.palavra, atual->tripla.palavra);
  
  if(comp < 0){
    if((inserirAVLPalavra(&(atual->esq), c)) == 1){
      if(fatorBalanceamento(atual) >= 2){
          if(strcmp(c.palavra, (*raiz)->esq->tripla.palavra) < 0){
            RotacaoLL(raiz);
          }
          else{
            RotacaoLR(raiz);
          }
      }
    }
  }
  
  if(comp > 0){
    if((inserirAVLPalavra(&(atual->dir), c)) == 1){
      if(fatorBalanceamento(atual) >= 2){  
        if(strcmp(c.palavra, (*raiz)->dir->tripla.palavra) > 0){ 
          RotacaoRR(raiz);
        }else{
          RotacaoRL(raiz);
        }
      }
    }
  }
  else{
      for(int i = 0; i < c.frequencia; i++)
        inserirOffset(&(*raiz)->tripla, c.dados[i]);
  }

  atual->altura = maior(alturaNoAVL(atual->esq),alturaNoAVL(atual->dir)) + 1;
  return 1;
} 

//===================================
void preencheAVL(RepositorioAVL *r, CitacoesArquivo dados, int qtdLinhas){
  char **palavrasValidasCit;
  char temp[MAX_WORDS];
  int nPalavrasValidas = 0;
  indice id;
  int p, q;
  Citacao *atual;

  for(int i = 0; i < qtdLinhas; i++){
    id = dados[i].offset;
    strcpy(temp, dados[i].cit);
    palavrasValidasCit = getPalavraCitacao(temp, &nPalavrasValidas);
    for(int j = 0; j < nPalavrasValidas; j++){
      processaString(palavrasValidasCit[j]);

      atual = criaCitacao(palavrasValidasCit[j]);
      p = inserirOffset(atual, id);

      q = inserirAVLPalavra(r, *atual);
    }
  }
}
