#include "stdio.h"
#include "tab_hash.h"

typedef struct listaPa listaPa;
typedef struct pagina TPagina;
typedef struct palavra TPalavra;
typedef struct slivro TLivro;
listaPa *criaListaPalavras(TPagina *pagina);
DicioSemiDinamico* cria_dicio_lista_palavras(TLivro* lido, long k, long f_carga);
DicioSemiDinamico** criar_dicio_livro(TLivro* lido, long f_carga);
TLivro *lerLivro(FILE *fl, char **stopwords);
TLivro* ler_livro_main(char* obra);

DicioSemiDinamico* cria_dicio_lista_palavras(TLivro* lido, long k, long f_carga);
DicioSemiDinamico** criar_dicio_livro(TLivro* lido, long f_carga);
void imprime_lista_palavras(struct palavra* lista_de_palavras, int qtd_de_palavras);
void imprime_pagina(TPagina *pagina);
void imprime_livro(TLivro *l);
int retorna_num_pags(TLivro* livro);

int funcao_teste(char* obra);