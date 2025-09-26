#ifndef AVL_H
#define AVL_H

#include "Repositorio.h"

typedef struct NoAVL{
    Citacao tripla;
    int altura;
    struct NoAVL *esq;
    struct NoAVL *dir;
}NoAVL;
typedef struct NoAVL* RepositorioAVL;

RepositorioAVL *criarAVL();
void liberaNoAVL(NoAVL *no);
void liberaAVL(RepositorioAVL *raiz);
int alturaNoAVL(NoAVL *no);
int fatorBalanceamento(NoAVL *no);
int maior(int x, int y);
int AVLvazia(RepositorioAVL *raiz);
int alturaAVL(RepositorioAVL *raiz);
int totalNoAVL(RepositorioAVL *raiz);
void preencheAVL(RepositorioAVL *r, CitacoesArquivo dados, int qtdLinhas);
int inserirAVLPalavra(RepositorioAVL *raiz, Citacao c);
NoAVL *procuraMenorAVL(NoAVL* atual);
void RotacaoRL(RepositorioAVL *A);
void RotacaoLR(RepositorioAVL *A);
void RotacaoRR(RepositorioAVL *A);
void RotacaoLL(RepositorioAVL *A);
void posOrdemAVL(RepositorioAVL *raiz);
void emOrdemAVL(RepositorioAVL *raiz);
void preOrdemAVL(RepositorioAVL *raiz);
NoAVL *buscaAVLPalavra(RepositorioAVL *raiz, char *palavra);
int verificaAVLPalavra(RepositorioAVL *raiz, char *palavra);

#endif