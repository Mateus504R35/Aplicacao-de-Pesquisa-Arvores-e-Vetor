#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Repositorio.h"


CitacoesArquivo criaDados(){
    DadosCit *dados = (DadosCit *)malloc(MAX_LINE * sizeof(DadosCit));

    if (dados == NULL) {
        printf("Erro ao alocar memória para o vetor de dados do arquivo\n");
        exit(1);
    }

    return dados;
}

Citacao *criaCitacao(char *p){
  Citacao *C = (Citacao*)malloc(sizeof(Citacao));
  if(C == NULL){
    printf("\nErro na criacao da citacao.\n");
    exit(-1);
  }
  C->dados = (indice*) malloc(MAX_LINE*sizeof(indice));
  for(int i = 0; i < MAX_LINE; i++){
    C->dados[i] = -1;  //preencho com -1 para saber que nao é offset
  }
  strcpy(C->palavra, p);
  C->frequencia = 1;

  return C;  //retorno uma citacao com palavra e frequencia mas sem os offsets ainda
}

int existeOffset(Citacao *citacao, indice id){//verificar se ja existe um offset na tripla
    for (int i = 0; i < citacao->frequencia; i++) {
        if (citacao->dados[i] == id) {
            return 1; //sucesso: existe esse offset
        }
    }
    return 0; //fracasso: nao existe esse offset
}//1: existe esse offset; 0: nao existe esse offset

int inserirOffset(Citacao *c, indice id){ //inserir offset novo em uma tripla
  if(c == NULL) return 0; //fracasso: citacao nao existe
  if(c->dados[0] == -1){ //citacao recem criada sem offsets
    c->dados[0] = id;
    return 1;
  }
  else{ //citacao que ja contem offsets inseridos
    if(existeOffset(c, id) == 0){
      c->dados[c->frequencia] = id; //insiro o offset
      c->frequencia++; //aumento o numero de frequencia
      return 1; //sucesso
    }
    else   return 0; //fracasso: ja existe esse offset
  }
}//0: fracasso; 1: sucesso; 

void processaCitacao(Citacao *c){
    if(c->frequencia == 1) return; //citacao recem criada sem offsets
    int cont = 0;
    if(c->dados[0] == -1){ //se a citacao tem -1 na posicao 1
      for(int i = 0; i < c->frequencia; i++){ 
        c->dados[i] = c->dados[i+1]; //movo todos os elementos
      }
      c->frequencia--; //diminuo o numero da frequencia
    }

    for (int i = 0; i < c->frequencia; i++) {
        if (c->dados[i] == -1)  cont++; //conto a ocorrencia de -1 dentro do limite de frequencia
    }

    c->frequencia -= cont; //diminuo o numero de frequencia pela quantidade de -1 que encontrei
}

DadosCit *buscaOffset(CitacoesArquivo dados, indice id, int *linha){
  DadosCit *dado = (DadosCit*) malloc(sizeof(DadosCit));

  for(int i = 0; i < MAX_LINE; i++){
    if(dados[i].offset == id){
      dado = &dados[i];
      *linha = i+1;
      break;
    }
  }

  return dado;
}

void mostraCitacao(Citacao c, CitacoesArquivo dados){
  DadosCit *dado;
  int l;
  printf(" _____________________________________________________\n");
  printf("\n             Palavra:    %s \n", c.palavra);
  printf("             Frequência:   %d\n", c.frequencia);  
  printf("_____________________________________________________");
  printf("\n             Citações com essa palavra:\n");


  for (int i = 0; i < c.frequencia; i++) {
      dado = buscaOffset(dados, c.dados[i], &l);
      printf("_____________________________________________________");
      printf("\n  -> Linha %d (Offset %ld):\n\n", l, c.dados[i]);
      printf("  \"%s\"\n", dado->cit);
      printf("\n  (Filme: %s)\n", dado->filme);
      printf("  (Ano:   %d)\n", dado->ano);
  }
}

void processaString(char *c){
    int t = strlen(c); 
    for (int i = 0; i < t; i++) { 
        if ((((int)c[i] >= 192) && ((int)c[i] <= 197)) || (((int)c[i] >= 224) && ((int)c[i] <= 229))) c[i] = 'a';
        if ((((int)c[i] >= 200) && ((int)c[i] <= 203)) || (((int)c[i] >= 232) && ((int)c[i] <= 235))) c[i] = 'e';
        if ((((int)c[i] >= 204) && ((int)c[i] <= 207)) || (((int)c[i] >= 236) && ((int)c[i] <= 239))) c[i] = 'i';
        if ((((int)c[i] >= 210) && ((int)c[i] <= 214)) || (((int)c[i] >= 242) && ((int)c[i] <= 246))) c[i] = 'o';
        if ((((int)c[i] >= 217) && ((int)c[i] <= 220)) || (((int)c[i] >= 249) && ((int)c[i] <= 252))) c[i] = 'u';
        if (((int)c[i] == 199) || ((int)c[i] == 231)) c[i] = 'c';


        if (c[i] != ' ') {
            c[i] = tolower(c[i]);
        }
    }
}

char **getPalavraCitacao(char *cit, int *nPalavras){  //responsavel por quebrar a citacao em palavras, criar um vetor de string dessas palavras (que sejam >=3) -- adiciona-las depois ao RepositorioPB
  if(cit == NULL){
    *nPalavras = 0;
    return NULL;
  }

  char **aux = NULL; //declaracao vetor de string (ponteiro p/ ponteiro)
  int nPalavrasM3 = 0;  //numero de palavras que sao validas
  char separadoresLinha[] = "-“...'’, . !?\"";  //delimitadores que separam a linha
  char *palavra = strtok(cit, separadoresLinha);  //quebra da frase de citacao em palavras

  while(palavra != NULL){
    if(strlen(palavra) > 3){ //se o tamanho da palavra for maior do que 3
      aux = (char**) realloc(aux, ((nPalavrasM3 + 1)*sizeof(char*)));  //aumento o tamanho do vetor de strings
      aux[nPalavrasM3] = strdup(palavra); //duplico a palavra para o vetor com a funcao strdup
      nPalavrasM3++;  //aumento o numero de palavras validas existentes
    }
    palavra = strtok(NULL, separadoresLinha);  //vou para a proxima palavra e repito o loop
  }
  *nPalavras = nPalavrasM3; //passo o numero de palavras validas para o main
  return aux;  //retorno o vetor de strings com as palavras obtidas da frase de citacao
}
