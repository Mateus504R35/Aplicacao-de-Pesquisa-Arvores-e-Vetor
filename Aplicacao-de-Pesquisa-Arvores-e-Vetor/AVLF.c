#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AVLF.h"

ConjuntoFrequencias *criaConjunto(){
  ConjuntoFrequencias *cf = (ConjuntoFrequencias*) malloc(MAX_WORDS*sizeof(ConjuntoFrequencias));

  for(int i = 0; i < MAX_WORDS; i++){
    cf[i].valorFreq = 0;
    cf[i].triplasMF = NULL;
    cf[i].qtd = 0;
  }
  return cf;
}

int buscaFreq(ConjuntoFrequencias *cf, int freq){
  if(cf == NULL) return -1;
  if(cf->qtd == 0) return -1;
  if(freq <= 0) return -1;

  for(int i = 0; i < MAX_WORDS; i++){
    if(cf[i].valorFreq == freq)
      return i;
  }

  return -1;
}

int inserirFrequencia(ConjuntoFrequencias *cf, Citacao c){
  if(cf == NULL) return 0;
  if(c.frequencia <= 0) return 0;

  int pos = buscaFreq(cf, c.frequencia);

  if(pos != -1){
    cf[pos].triplasMF = (Citacao*)realloc(cf[pos].triplasMF, (cf[pos].qtd + 1) * sizeof(Citacao));
    cf[pos].triplasMF[cf[pos].qtd] = c;
    cf[pos].qtd++;
    return 1;
  }
  else{
    if(cf[0].qtd == 0){
      cf[0].triplasMF = (Citacao*)realloc(cf[0].triplasMF, (cf[0].qtd + 1) * sizeof(Citacao));
      cf[0].triplasMF[cf[0].qtd] = c;
      cf[0].valorFreq = c.frequencia;
      cf[0].qtd++;
      return 1;
    }
    else{
      int i;
      int cont = 0;
      for(i = 0; i < MAX_WORDS; i++){
        if(cf[i].qtd == 0){
          cont = 1;
          break;
        }
      }
      if(cont != 1) return 0;
      else{
        cf[i].triplasMF = (Citacao*) realloc(cf[i].triplasMF, cf[i].qtd+1*sizeof(Citacao));
        cf[i].triplasMF[cf[i].qtd] = c;
        cf[i].valorFreq = c.frequencia;
        cf[i].qtd++;
        return 1;
      }
    }
  }
}

void preencheVetorCitacoesAVL(NoAVL* no, Citacao* vetor, int* index) {
    if (no != NULL) {
        preencheVetorCitacoesAVL(no->esq, vetor, index);
        vetor[(*index)++] = no->tripla;
        preencheVetorCitacoesAVL(no->dir, vetor, index);
    }
}

Citacao* vetorCitacoesAVL(RepositorioAVL* raiz) {
    if (raiz == NULL || *raiz == NULL) {
        return NULL;
    }

    int tamanho = totalNoAVL(raiz);
    Citacao* vetor = (Citacao*)malloc(sizeof(Citacao) * tamanho);
    if (vetor == NULL) {
        fprintf(stderr, "Erro na alocação de memória.\n");
        exit(1);
    }

    int index = 0;
    preencheVetorCitacoesAVL(*raiz, vetor, &index);

    return vetor;
}

void coletaCitacoes(RepositorioAVL *r, ConjuntoFrequencias *conjuntos){
  int total = totalNoAVL(r);
  Citacao *Nos = vetorCitacoesAVL(r);

  for(int i = 0; i < total; i++){
    inserirFrequencia(conjuntos, Nos[i]);
  }
  free(Nos); 
}

int qtdCitacoes(ConjuntoFrequencias *conjuntos){
  if(conjuntos == NULL) return -1;
  if(conjuntos[0].qtd == 0) return 0;

  int cont = 0;

  for(int i = 0; i < MAX_WORDS; i++){
    if(conjuntos[i].qtd != 0) cont++;
  }
  return cont;
}
//--------------------------------------------------------------------
RepositorioAVLFREQ *criarAVLF(){ //mantem
  RepositorioAVLFREQ *raiz = (RepositorioAVLFREQ*) malloc(sizeof(RepositorioAVLFREQ));
    if(raiz != NULL)
        *raiz = NULL;
    return raiz;
}

void liberaNoAVLF(NoAVLF *no){ //mantem
    if(no == NULL)
        return;
    liberaNoAVLF(no->esq);
    liberaNoAVLF(no->dir);
    free(no);
    no = NULL;
}

void liberaAVLF(RepositorioAVLFREQ *raiz){ //mantem
    if(raiz == NULL)
        return;
    liberaNoAVLF(*raiz);
    free(raiz);
}

int alturaNoAVLF(NoAVLF *no){ //mantem
    if(no == NULL)
        return -1;
    else
    return no->altura;
}

int fatorBalanceamentoF(NoAVLF *no){ //mantem
    return labs(alturaNoAVLF(no->esq) - alturaNoAVLF(no->dir));
}

int AVLFvazia(RepositorioAVLFREQ *raiz){
    if(raiz == NULL)
        return 1;
    if(*raiz == NULL)
        return 1;
    return 0;
} //mantem

int totalNoAVLF(RepositorioAVLFREQ *raiz){
    if (raiz == NULL)
        return 0;
    if (*raiz == NULL)
        return 0;
    int alt_esq = totalNoAVLF(&((*raiz)->esq));
    int alt_dir = totalNoAVLF(&((*raiz)->dir));
    return(alt_esq + alt_dir + 1);
} //mantem

int alturaAVLF(RepositorioAVLFREQ *raiz){
    if (raiz == NULL)
        return 0;
    if (*raiz == NULL)
        return 0;
    int alt_esq = alturaAVLF(&((*raiz)->esq));
    int alt_dir = alturaAVLF(&((*raiz)->dir));
    if (alt_esq > alt_dir)
        return (alt_esq + 1);
    else
        return(alt_dir + 1);
} //mantem


//--------------------------------------------------------------------
int fatorBalanceamentoFREQ(NoAVLF *no){ //mantem
    return labs(alturaNoAVLF(no->esq) - alturaNoAVLF(no->dir));
}

void freqRotacaoLL(RepositorioAVLFREQ *A){//LL
    NoAVLF *B;
    B = (*A)->esq;
    (*A)->esq = B->dir;
    B->dir = *A;
    (*A)->altura = maior(alturaNoAVLF((*A)->esq), alturaNoAVLF((*A)->dir)) + 1;
    B->altura = maior(alturaNoAVLF(B->esq),(*A)->altura) + 1;
    *A = B;
}

void freqRotacaoRR(RepositorioAVLFREQ *A){//RR
    NoAVLF *B;
    B = (*A)->dir;
    (*A)->dir = B->esq;
    B->esq = (*A);
    (*A)->altura = maior(alturaNoAVLF((*A)->esq), alturaNoAVLF((*A)->dir)) + 1;
    B->altura = maior(alturaNoAVLF(B->dir),(*A)->altura) + 1;
    (*A) = B;
}

void freqRotacaoLR(RepositorioAVLFREQ *A){//LR
    freqRotacaoRR(&(*A)->esq);
    freqRotacaoLL(A);
}

void freqRotacaoRL(RepositorioAVLFREQ *A){//RL
    freqRotacaoLL(&(*A)->dir);
    freqRotacaoRR(A);
}

NoAVLF *procuraMenorAVLF(NoAVLF* atual){
    NoAVLF *no1 = atual;
    NoAVLF *no2 = atual->esq;
    while(no2 != NULL){
        no1 = no2;
        no2 = no2->esq;
    }
    return no1;
}

int inserirAVLFrequencia(RepositorioAVLFREQ *raiz, ConjuntoFrequencias c){
  if(*raiz == NULL){
    NoAVLF *novo;
    novo = (NoAVLF*)malloc(sizeof(NoAVLF));

    if(novo == NULL) return 0;

    novo->citacao = c;
    novo->altura = 0;
    novo->esq = NULL;
    novo->dir = NULL;
    *raiz = novo;
    return 1;
  }

  NoAVLF *atual = *raiz;

    //0 igual = aumentar o numero de frequencia da palavra com a função inserirOffset
    //< 0 atual->tripla.palavra é maior que c.palavra = adicionar a esquerda
    //> 0 c.palavra é maior que atual->tripla.palavra = adicionar a direita

  if(c.valorFreq < atual->citacao.valorFreq){
    if((inserirAVLFrequencia(&(atual->esq), c)) == 1){
      if(fatorBalanceamentoFREQ(atual) >= 2){
          if(c.valorFreq < (*raiz)->esq->citacao.valorFreq){
            freqRotacaoLL(raiz);
          }
          else{
            freqRotacaoLR(raiz);
          }
      }
    }
  } //frequencia menor = ir para esquerda

  if(c.valorFreq > atual->citacao.valorFreq){
    if((inserirAVLFrequencia(&(atual->dir), c)) == 1){
      if(fatorBalanceamentoFREQ(atual) >= 2){  
        if(c.valorFreq > (*raiz)->dir->citacao.valorFreq){ 
          freqRotacaoRR(raiz);
        }else{
          freqRotacaoRL(raiz);
        }
      }
    }
  }  //frequencia maior = ir para direita
  
  else{  //frequencia igual = impossivel
    return 0;
  }

  atual->altura = maior(alturaNoAVLF(atual->esq),alturaNoAVLF(atual->dir)) + 1;
  return 1;
}
//--------------------------------------------------------------------
int verificaAVLFrequencia(RepositorioAVLFREQ *raiz, int frequencia){
    if(raiz == NULL) return 0;
    NoAVLF* atual = *raiz;
    while(atual != NULL){
      if(frequencia == atual->citacao.valorFreq) return 1;
      if(frequencia > atual->citacao.valorFreq) atual = atual->dir;
      else atual = atual->esq;
    }
    return 0;
}

RepositorioAVLFREQ buscaAVLFrequencia(RepositorioAVLFREQ *raiz, int frequencia){
  if(raiz == NULL) return NULL;
  if(verificaAVLFrequencia(raiz, frequencia) == 0) return NULL;

  NoAVLF* atual = *raiz;

  if(frequencia < atual->citacao.valorFreq) return buscaAVLFrequencia(&(atual->esq), frequencia);
  if(frequencia > atual->citacao.valorFreq) return buscaAVLFrequencia(&(atual->dir), frequencia);
  else return *raiz;
}

void preencheAVLF(RepositorioAVLFREQ *rf, RepositorioAVL *r){
  RepositorioAVL *tmp = r;
  Citacao *aux = vetorCitacoesAVL(tmp);
  int total = totalNoAVL(r);
  ConjuntoFrequencias *conjunto = criaConjunto();
  
  for(int i = 0; i < total; i++){
    processaCitacao(&aux[i]);
    if(inserirFrequencia(conjunto, aux[i]) != 1) printf("\nAQUI\n");
  }

  for(int i = 0; i < conjunto->qtd; i++){
    inserirAVLFrequencia(rf, conjunto[i]);
  }
  
}

void mostraFrequencia(RepositorioAVLFREQ raiz){
  printf("\n<<<Frequencia: %d>>>\n", (raiz)->citacao.valorFreq);
  printf("(%d palavras com essa frequencia)\n", (raiz)->citacao.qtd);
  for(int i = 0; i < (raiz)->citacao.qtd; i++){
     printf("\n   ->Palavra: %s (%d)\n", (raiz)->citacao.triplasMF[i].palavra, (raiz)->citacao.triplasMF[i].frequencia);
    for(int j = 0; j < (raiz)->citacao.triplasMF[i].frequencia; j++){
      printf("(offset: %ld)\n", (raiz)->citacao.triplasMF[i].dados[j]);
    }
    printf("\n");
  }
}