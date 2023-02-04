#include "stdio.h"

typedef struct pagina TPagina;
typedef struct palavra TPalavra;
typedef struct slivro TLivro;
TPalavra *criaListaPalavras(TPagina *pagina);

void imprime_livro(TLivro *l);
TPagina *lerPagina(FILE *fl, char **stopwords, int num_pagina);
TLivro *lerLivro(FILE *fl, char **stopwords);
char **carregarStopwords(char* livro)