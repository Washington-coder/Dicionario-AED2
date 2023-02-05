#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "leitura_pag.h"
#include "dicio_semi_dinamico.h"

// Tipo contendo o dicionário de palavras, com suas ocorrências e páginas
typedef struct sLivro{
    DicioSemiDinamico* frequencia_livro; // uh oh (pointer?)
    TLivro* livro; // uh oh 2
} FrequenciaLivro;

struct pagina
{
    char **p;
    int num_pal;
    int num_pagina;
    listaPa* listaPalavras;
};

struct palavra
{
    char nome[48];
    int qtd_repeticoes;
    int qtd_de_palavras;
};

struct slivro
{
    TPagina *ps[1000];
    int num_pag;
};

typedef struct listaPa{
    long num_lista;
    TPalavra *lista;
}listaPa;

// função:
// percorrer o livro, criar dicionários de cada lista de palavras de cada página
// manter o número total de palavras

// função:
// fazer um dicion´ário com todas as palavras únicas do livro,
// manter em cada palavra

// retorna a frequência do termo em uma página (tpalavra, tpagina)
long tf(TPalavra* palavra, TPagina* pagina){
    // quatindade de vezes que a palavra aparece
    // /
    // quantidade total

    // pegar um dicionário da lista de palavras dessa página, pesquisar, e retornar a divisão
    int qtd_total_de_palavras = pagina->num_pal;
    int qtd_de_repeticoes_da_palavra = palavra->qtd_repeticoes;

    long tf = qtd_de_repeticoes_da_palavra / qtd_total_de_palavras;

    return tf;
}

// retorna a quantidade de páginas que contém um termo (tpalavra, tlivro)
long int n_containing(TPalavra* palavra, TLivro* livro){
    // fazer um dicionário de cada página/lista de palavras, procurar pela palavra em cada dicionário de página, retornar um contador

    long int contador = 0;

    // indice da pagina
    for (int i = 0; i < livro->num_pag; i++)
    {
        TPagina* pagina = malloc(sizeof(TPagina));
        pagina = livro->ps[i];
        // indice da lista de palavras
        for (int j = 0; j < pagina->listaPalavras->num_lista; j++)
        {
            TPalavra* string = malloc(sizeof(TPalavra));
            strcpy(string->nome, pagina->listaPalavras->lista[j].nome);

            if(strcmp(string->nome, palavra->nome) == 0);{
                contador++;
            }
        }
    }
    return contador;
}

// retorna o quão comum é uma palavra em uma série de páginas (tpalavra, tlivro)
long idf(TPalavra* palavra, TLivro* livro){
    // log do
    // número total de páginas / número de páginas em que a palavra aparece + 1
    // log(num_págs/ n_containing())
}

// retorna o TF-IDF (com dicionário)
long tfidf(TPalavra* palavra, TPagina* pagina, TLivro* livro){
    // retorna um vetor de tamanho 5, com os maiores TF-IDFs
    return tf(palavra, pagina) * idf(palavra, livro);
}