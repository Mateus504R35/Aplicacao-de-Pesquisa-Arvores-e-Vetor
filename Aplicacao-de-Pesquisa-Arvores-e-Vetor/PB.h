#include "Repositorio.h"

typedef struct repositorioPB{  //Repositorio p/ pesquisa binaria
  Citacao *triplas;  //vetor de citacoes
  int qtdTriplas; //numero de elementos do repositorio
}RepositorioPB;

RepositorioPB *criaRepositorioPB();  //funcao que cria o repositorio para Pesquisa Binaria
int buscaTriplaPB(RepositorioPB *r, char *palavra);  //coleta o indice de uma palavra no repositorio
int inserePB(RepositorioPB *r, Citacao c);  //insere uma tripla no repositorio
void quicksort(Citacao *v, int ini, int fim); //ordena o repositorio com quicksort em ordem alfabetica
int buscabinariarecursiva(Citacao *c, int ini, int fim, char *palavra);  //funcao que realiza a busca binaria
void preenchePB(RepositorioPB *r, CitacoesArquivo dados, int qtdLinhas);  //funcao que preenche o RepositorioPB automaticamente com todas as linhas do arquivo
