#ifndef REPOSITORIO_H
#define REPOSITORIO_H

#define MAX 1000
#define MAX_LINE 1024
#define MAX_WORDS 2000
//"Repositorio.h" guarda funções/structs universais de todo o código

//-------------------------------------------------------------------------------------------------------------
typedef long int indice; //definicao do tipo indice

typedef struct DadosCit{  //tipo de dado que guarda os dados da citacao
  char cit[MAX_LINE];   //string que contem a frase de citacao
  char filme[MAX_LINE];  //string que guarda o nome do filme
  int ano;  //variavel que guarda o ano de lancamento do filme
  indice offset;  //variavel que guarda o offset do inicio da linha do arquivo
}DadosCit;
typedef DadosCit* CitacoesArquivo;   //definicao do vetor de dados

typedef struct Citacao {  //tipo de dado da tripla
  char palavra[100];  //string com a palavra de busca padronizada (maior que 3 letras, minuscula e sem caracteres especiais)
  int  frequencia;  //numero de vezes que essa palavra aparece no arquivo
  indice *dados;   //vetor com os offsets de cada citacao
}Citacao;

//-------------------------------------------------------------------------------------------------------------
CitacoesArquivo criaDados(); //criacao de um vetor de dados
Citacao *criaCitacao(char *p); //criacao de uma citacao com uma palavra parametro
int existeOffset(Citacao *citacao, indice id);  //checa se um dado offset pertence ao vetor de offsets daquela citacao
int inserirOffset(Citacao *c, indice id); //funcao que insere um dado offset no vetor de offsets daquela citacao
void processaCitacao(Citacao *c); //funcao que corrige uma citacao que contenha dados errados
DadosCit *buscaOffset(CitacoesArquivo dados, indice id, int *linha);  //funcao que retorna um dado de citacao pelo offset
void mostraCitacao(Citacao c, CitacoesArquivo dados);  //funcao que printa na tela todas os dados de uam citacao
void processaString(char *c);  //funcao que padroniza uma string para sem caracteres especiais
char **getPalavraCitacao(char *cit, int *nPalavras); //funcao que quebra uma frase de citacao em varias palavras com mais de 3 letras

//------------------------------------------------------------------------------------------------------------- 


#endif