//Mateus Euripedes Malaquias Soares
//Marcella Silva Figueredo

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <time.h>
#include <link.h>
#include "PB.h"
#include "AVL.h"
#include "AVLF.h"
#include "ABB.h"
#include "Repositorio.h"

int main(void) {
  int sairInicial = 0;
  int sairEstrutura = 0;
  int a, b;
  int parte = 0;
  int qtdLinhas = 0;
  indice offsetAtual;
  CitacoesArquivo linhasArquivo = criaDados();
  char linhaSeparada[3][MAX];
  char conteudoLinha[MAX], temp[MAX];
  char *palavras;
  RepositorioABB ABB = NULL;
  RepositorioPB *PB = criaRepositorioPB(); 
  RepositorioAVL AVL = NULL;
  RepositorioAVLFREQ AVLF = NULL;
  char palavraDigitada[MAX_WORDS];
  int numeroDigitado;

  FILE *arquivoCitacoes;  //arquivo
  arquivoCitacoes = fopen("movie_quotes.csv", "rb");  //abrir arquivo
  if(arquivoCitacoes == NULL){
    printf("Erro ao abrir o arquivo de citações.");
    exit(-1);
  }
  while (fgets(conteudoLinha, MAX, arquivoCitacoes) != NULL) { 
    offsetAtual = ftell(arquivoCitacoes); //armazeno o offset no inicio de cada leitura da linha atual

    int len = strlen(conteudoLinha);
    for (int i = 0; i < len - 1; i++) {
        if (conteudoLinha[i] == ',' && conteudoLinha[i + 1] == '"') {
            conteudoLinha[i] = '=';
            conteudoLinha[i + 1] = '"';
        }
    } //arruma o problema do ";" na coleta da linha
    palavras = strtok(conteudoLinha, "\"=\"");
    parte = 0;

    while (palavras) {
      strcpy(linhaSeparada[parte], palavras);
      palavras = strtok(NULL, "\"=\"");
      parte++;
    } 
    strcpy(linhasArquivo[qtdLinhas].cit, linhaSeparada[0]);
    strcpy(linhasArquivo[qtdLinhas].filme, linhaSeparada[1]);
    linhasArquivo[qtdLinhas].ano = atoi(linhaSeparada[2]);
    linhasArquivo[qtdLinhas].offset = offsetAtual; //guardo esse offset para saber em qual linha o dado foi lido

    qtdLinhas++;
  }
  fclose(arquivoCitacoes);

  //--------------------------------------------------------------------------------------
  // Preencher as estruturas de dados (ABB, PB, AVL)
  clock_t start, end;
  double tempoPB, tempoABB, tempoAVL;

  
  // Menu principal
  printf("\n__________________________________\n");
  printf("***   Trabalho 2 - Árvores    ****");
  printf("\n__________________________________\n");

  printf("\nCarregando arquivo por Pesquisa Binária...\n");
  fflush(stdout);
  sleep(2);
  start = clock();
  preenchePB(PB, linhasArquivo, qtdLinhas);
  end = clock();
  tempoPB = ((double)(end - start)) / CLOCKS_PER_SEC;
  printf("Tempo de insercao na estrutura: %f\n", tempoPB);

  printf("\nCarregando arquivo por Árvore Binária (Sem Balanceamento)...\n");
  fflush(stdout);
  sleep(2);
  start = clock();
  preencheABB(&ABB, linhasArquivo, qtdLinhas);
  end = clock();
  tempoABB = ((double)(end - start)) / CLOCKS_PER_SEC;
  printf("Tempo de insercao na estrutura: %f\n", tempoABB);

  printf("\nCarregando arquivo por Árvore Binária Balanceada (AVL)...\n");
  fflush(stdout);
  sleep(2);
  start = clock();
  preencheAVL(&AVL, linhasArquivo, qtdLinhas);
  end = clock();
  tempoAVL = ((double)(end - start)) / CLOCKS_PER_SEC;
  printf("Tempo de insercao na estrutura: %f\n", tempoAVL);
  preencheAVLF(&AVLF, &AVL);
  

  do {
    printf("\n--Escolha uma opção de busca:\n");
    printf("(1) - Pesquisar por palavra\n");
    printf("(2) - Pesquisar por frequencia (AVL)\n");
    printf("(0) - Sair do programa\n");
    scanf("%d", &sairInicial);
    fflush(stdin);
    printf("\033[H\033[J");


    switch (sairInicial) {

      case 1:
        printf("\033[H\033[J"); 
        printf("\n***OBS: a palavra digitada precisa ser minuscula e sem acento***\n");
        fflush(stdin);
        printf("\nDigite a palavra que deseja pesquisar: ");
        scanf("%s", palavraDigitada);

        start = clock();
        b = buscabinariarecursiva(PB->triplas, 0, PB->qtdTriplas-1, palavraDigitada);
        end = clock();
        tempoPB = ((double)(end - start)) / CLOCKS_PER_SEC;

        start = clock();
        NoABB *buscaABB = buscarABB(ABB, palavraDigitada);
        end = clock();
        tempoABB = ((double)(end - start)) / CLOCKS_PER_SEC;

        start = clock();
        NoAVL *buscaAVL = buscaAVLPalavra(&AVL, palavraDigitada);
        end = clock();
        tempoAVL = ((double)(end - start)) / CLOCKS_PER_SEC;

        printf("Tempos de busca:\n");
        printf("-> %f para Pesquisa Binária\n", tempoPB);
        printf("-> %f para Arvore Binaria\n", tempoABB);
        printf("-> %f para Arvore AVL\n", tempoAVL);

        if(buscaAVL != NULL){
          printf("\nPalavra encontrada!\n");
          mostraCitacao(buscaAVL->tripla, linhasArquivo);
        }else printf("\nPalavra nao encontrada.\n");


        fflush(stdin);
        printf("Pressione uma tecla para continuar...");
        getchar(); // Aguarda o usuário pressionar Enter
        getchar();

        printf("\033[H\033[J"); 
        break;


      case 2:
        printf("\033[H\033[J"); 
        fflush(stdin);
        printf("Digite o numero da frequencia a ser pesquisada:");
        scanf("%d", &numeroDigitado);

        start = clock();
        RepositorioAVLFREQ buscaF = buscaAVLFrequencia(&AVLF, numeroDigitado);
        end = clock();
        tempoAVL = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("Tempo de pesquisa por frequencia: %f\n", tempoAVL);

        if(buscaF != NULL) mostraFrequencia(buscaF);
        else printf("\nFrequencia inexistente.\n");
        
        fflush(stdin);
        printf("Pressione uma tecla para continuar...");
        getchar(); // Aguarda o usuário pressionar Enter
        getchar();

        printf("\033[H\033[J"); 
        break;

        case 0:
          printf("\033[H\033[J");
          printf("\nSaindo...");
        break;
    
        default:
            printf("\033[H\033[J");
            printf("\nErro, opção inválida.\n");
        break;
      printf("\033[H\033[J");
    }

 
    printf("\033[H\033[J"); 
  } while (sairInicial != 0);

  return 0;
}


  

//-----------------------------------------------------------------------------------------------
  