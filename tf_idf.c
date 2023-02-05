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


// retorna a frequência do termo em uma página (tpalavra, tpagina)
long tf(TPalavra* palavra, TPagina* pagina){

}

// retorna a quantidade de páginas que contém um termo (tpalavra, tlivro)
long n_containing(TPalavra* palavra, TLivro* livro){

}

// retorna o quão comum é uma palavra em uma série de páginas (tpalavra, tlivro)
long idf(TPalavra* palavra, TLivro* livro){

}

// retorna o TF-IDF (com dicionário)
long tfidf(TPalavra* palavra, TPagina* pagina, TLivro* livro){
    
    return tf(palavra, pagina) * idf(palavra, livro);
}