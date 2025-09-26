#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Repositorio.h"
#include "PB.h"


RepositorioPB *criaRepositorioPB(){
  RepositorioPB *r = (RepositorioPB *)malloc(sizeof(RepositorioPB));

  if (r == NULL) {
      printf("Erro ao alocar memória para o Repositorio PB\n");
      exit(1);
  }

  r->triplas = NULL;
  r->qtdTriplas = 0;

  return r;
}

int buscaTriplaPB(RepositorioPB *r, char *palavra){
  if(r == NULL) return -1; //fracasso: repositorio nulo
  if(r->qtdTriplas == 0) return -1; //fracasso: repositorio nulo

  for(int i = 0; i < r->qtdTriplas; i++){
    if(strcmp(r->triplas[i].palavra, palavra) == 0) return i; //sucesso: palavra encontrada na posicao "i"
  }
  return -1; //fracasso: palavra nao encontrada
}//-1: fracasso; != -1: sucesso (indice da palavra)

int inserePB(RepositorioPB *r, Citacao c){
  if(r == NULL) return -1; //erro: repositorio nulo
  if(c.frequencia != 1) return -1; // erro: citacao vazia

  int pos = buscaTriplaPB(r, c.palavra);

  if(pos != -1){ //palavra da citacao ja existe no repositorio
    indice id;
    for(int i = 0; i < r->triplas[pos].frequencia; i++){
      id = c.dados[i];
      if(id != -1){
        inserirOffset(&r->triplas[pos], id);
      }
    }
    return 1;
  }
  else{// palavra da citacao ainda nao existe no repositorio
    if(r->qtdTriplas == 0){ //repositorio vazio
      r->triplas = (Citacao*)realloc(r->triplas, (r->qtdTriplas + 1) * sizeof(Citacao));
      if(r->triplas == NULL){
        printf("Erro ao alocar memória para o vetor de triplas no Repositorio PB\n");
        return -1;
      }
      r->triplas[r->qtdTriplas] = c;
      r->qtdTriplas++;
      return 1;
    }
    else{ //repositorio nao vazio
      r->triplas = (Citacao*)realloc(r->triplas, (r->qtdTriplas + 1) * sizeof(Citacao));
      r->triplas[r->qtdTriplas] = c;
      r->qtdTriplas++;
      return 1;
    } 
  }
  return 0; //fracasso: nao foi possivel adicionar a palavra
}//-1: erro; 0: fracasso; 1: sucesso

void quicksort(Citacao *v, int ini, int fim) {
    int i, j;
    Citacao pivo, temp;
    i = ini;
    j = fim;
    pivo = v[(ini + fim) / 2];

    while (i <= j) {
        while (strcmp(v[i].palavra, pivo.palavra) < 0 && i < fim) {
            i++;
        }
        while (strcmp(v[j].palavra, pivo.palavra) > 0 && j > ini) {
            j--;
        }
        if (i <= j) {
            temp = v[i];
            v[i] = v[j];
            v[j] = temp;
            i++;
            j--;
        }
    }

    if (j > ini) {
        quicksort(v, ini, j);
    }
    if (i < fim) {
        quicksort(v, i, fim);
    }
}

int buscabinariarecursiva(Citacao *c, int ini, int fim, char *palavra) {
  if (ini > fim) {
    return -1;
  }

  int m = (ini + fim) / 2;
  int comp = strcmp(c[m].palavra, palavra);

  if (comp == 0) {
    return m;
  } else if (comp < 0) {
    return buscabinariarecursiva(c, m+1, fim, palavra);
  } else {
    return buscabinariarecursiva(c, ini, m-1, palavra);
  }
}

//------------------------------------------------------------------------

void preenchePB(RepositorioPB *r, CitacoesArquivo dados, int qtdLinhas){
  char **palavrasValidasCit;
  char *temp = (char*) malloc(MAX_LINE*sizeof(char));
  int nPalavrasValidas = 0;
  int p, q;
  indice id; 
  Citacao *atual;

  for(int i = 0; i < qtdLinhas; i++){
    id = dados[i].offset;
    strcpy(temp, dados[i].cit);
    palavrasValidasCit = getPalavraCitacao(temp, &nPalavrasValidas);
    for(int j = 0; j < nPalavrasValidas; j++){
      processaString(palavrasValidasCit[j]);

      atual = criaCitacao(palavrasValidasCit[j]);
      q = inserirOffset(atual, id);


      p = inserePB(r, *atual);
    }
  }
  quicksort(r->triplas, 0, r->qtdTriplas-1);
}
