#include "AVL.h"


typedef struct ConjuntoFrequencias{
  Citacao *triplasMF;
  int valorFreq;
  int qtd;
}ConjuntoFrequencias;

typedef struct NoAVLF{
    ConjuntoFrequencias citacao;
    int altura;
    struct NoAVLF *esq;
    struct NoAVLF *dir;
}NoAVLF;
typedef struct NoAVLF* RepositorioAVLFREQ;


ConjuntoFrequencias *criaConjunto();
int buscaFreq(ConjuntoFrequencias *cf, int freq);
int inserirFrequencia(ConjuntoFrequencias *cf, Citacao c);
void preencheVetorCitacoesAVL(NoAVL* no, Citacao* vetor, int* index);
Citacao* vetorCitacoesAVL(RepositorioAVL* raiz);
void coletaCitacoes(RepositorioAVL *r, ConjuntoFrequencias *conjuntos);
int qtdCitacoes(ConjuntoFrequencias *conjuntos);
RepositorioAVLFREQ *criarAVLF();
void liberaNoAVLF(NoAVLF *no);
void liberaAVLF(RepositorioAVLFREQ *raiz);
int alturaNoAVLF(NoAVLF *no);
int fatorBalanceamentoF(NoAVLF *no);
int AVLFvazia(RepositorioAVLFREQ *raiz);
int totalNoAVLF(RepositorioAVLFREQ *raiz);
int alturaAVLF(RepositorioAVLFREQ *raiz);
int fatorBalanceamentoFREQ(NoAVLF *no);
void freqRotacaoLL(RepositorioAVLFREQ *A);
void freqRotacaoRR(RepositorioAVLFREQ *A);
void freqRotacaoLR(RepositorioAVLFREQ *A);
void freqRotacaoRL(RepositorioAVLFREQ *A);
NoAVLF *procuraMenorAVLF(NoAVLF* atual);
int inserirAVLFrequencia(RepositorioAVLFREQ *raiz, ConjuntoFrequencias c);
int verificaAVLFrequencia(RepositorioAVLFREQ *raiz, int frequencia);
RepositorioAVLFREQ buscaAVLFrequencia(RepositorioAVLFREQ *raiz, int frequencia);
void preencheAVLF(RepositorioAVLFREQ *rf, RepositorioAVL *r);
void mostraFrequencia(RepositorioAVLFREQ raiz);
