# Aplicação de Pesquisa — Árvores e Vetor

![C](https://img.shields.io/badge/language-C-blue)
![Build](https://img.shields.io/badge/build-gcc%20%7C%20make-informational)

Aplicação em **C** que carrega um repositório de **citações de filmes** (`movie_quotes.csv`) e permite pesquisar por **palavra** e por **frequência** usando diferentes estruturas de dados:

- **Vetor ordenado** + **Busca Binária** (`PB.*`)
- **ABB** — Árvore Binária de Busca (`ABB.*`)
- **AVL** — Árvore Binária de Busca Balanceada (`AVL.*`)
- **AVL por Frequência** — índice secundário por frequência das palavras (`AVLF.*`)

O programa também mede **tempos de inserção** e **tempos de consulta** com `clock()` para comparar desempenho das abordagens.

> Autores (do código): informados no cabeçalho de `main.c`.

---

## Estrutura

```
Aplicacao-de-Pesquisa-Arvores-e-Vetor/
├── ABB.c/.h          # Árvore Binária de Busca
├── AVL.c/.h          # Árvore AVL (balanceada por palavras)
├── AVLF.c/.h         # Árvore AVL por frequência (chave = contagem)
├── PB.c/.h           # Vetor + ordenação (quicksort) + busca binária
├── Repositorio.c/.h  # Leitura do CSV, normalização e utilitários
├── main.c            # Interface CLI, medições e orquestração
└── movie_quotes.csv  # Base de dados com citações, filme e ano
```

**Formato do `movie_quotes.csv`** (valores entre aspas, separados por vírgula):

```
"citação","filme","ano"
"Frankly, my dear, I don't give a damn.","Gone with the Wind","1939"
```

---

## Compilação

### Usando Makefile

```bash
make        # compila (alvo padrão)
make run    # compila e executa ./pesquisa_arvores_vetor
make debug  # recompila com símbolos de depuração
make clean  # remove artefatos de build
```

### Compilando manualmente

```bash
gcc -std=c11 -Wall -Wextra -O2 -o pesquisa_arvores_vetor main.c PB.c AVL.c AVLF.c ABB.c Repositorio.c
```

---

## ▶Execução

1. Garanta que **`movie_quotes.csv`** esteja no **mesmo diretório** do executável.
2. Execute:
   ```bash
   ./pesquisa_arvores_vetor
   ```

Você verá um menu como este:

```
(1) - Pesquisar por palavra
(2) - Pesquisar por frequencia (AVL)
(0) - Sair do programa
```

### Observações de uso

- As buscas por **palavra** esperam **texto em minúsculas e sem acento** (há normalização, mas siga o padrão para resultados consistentes).
- A pesquisa por **frequência (AVL)** utiliza uma **árvore AVL indexada pela contagem de ocorrências** (estrutura `AVLF.*`), permitindo consultar todas as palavras com dada frequência.
- O carregamento inicial popula as estruturas (vetor/ABB/AVL/AVLF) e mede os **tempos de inserção**. As consultas também têm tempos registrados para comparação.

---

## Exemplos

- **Pesquisar por palavra**:
  1. Selecione a opção **1**.
  2. Digite, por exemplo, `force` (sem acento/maiúsculas).
  3. O programa exibe as citações, filme e ano correspondentes aos offsets daquela palavra.

- **Pesquisar por frequência (AVL)**:
  1. Selecione a opção **2**.
  2. Informe um número inteiro **f** (frequência desejada).
  3. O programa lista palavras com aquela frequência e algumas amostras de citações.

---

## Requisitos

- **gcc** (C11) e **make**
- Ambiente Unix-like (Linux/macOS) ou Windows (MinGW/WSL)
- Terminal com suporte a UTF-8

---

## Créditos

- Dataset: `movie_quotes.csv` (incluído no projeto)
- Implementação: ver autores em `main.c`
