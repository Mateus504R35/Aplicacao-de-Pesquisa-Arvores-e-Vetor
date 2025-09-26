#include "Repositorio.h"

typedef struct NoABB{  // nó de uma ABB
    Citacao tripla;  // citacao
    struct NoABB* Esq; // ponteiro para o nó esquero
    struct NoABB* Dir; // ponteiro para o nó direito
}NoABB;
typedef NoABB* RepositorioABB; // definicao de um repositorio

NoABB* criarNoABB(Citacao tripla);  //funcao que cria um nó da ABB com uma palavra
RepositorioABB inserirABB(RepositorioABB raiz, Citacao tripla);  //funcao que insere uma citacao na ABB
RepositorioABB buscarABB(RepositorioABB raiz, char *palavraChave);  //funcao que realiza a busca de uma palavra no repositorio
RepositorioABB removerABB(RepositorioABB raiz, char *palavraChave); //funcao que remove uma palavra do repositorio
NoABB* encontrarMinimoABB(RepositorioABB raiz); 
void centralABB(RepositorioABB raiz);  //funcao que faz o percurso central (em ordem) da ABB
void liberarABB(RepositorioABB raiz);  //funcao que libera a arvore
void preencheABB(RepositorioABB *r, DadosCit *d, int n);  //funcao que preenche automaticamente o RepositorioABB com todas as linhas do arquivo




