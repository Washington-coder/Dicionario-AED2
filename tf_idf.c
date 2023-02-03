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


// retorna a frequência do termo em um documento
long tf(char* palavra, FrequenciaLivro* pagina){

}

// retorna a quantidade de documentos que contém um termo
// necessário?
long n_containing(char* palavra, FrequenciaLivro** livro){

}

// retorna o quão comum é uma palavra em uma série de documentos
// necessário?
long idf(char* palavra, FrequenciaLivro** livro){

}

// retorna o TF-IDF
// necessário?
long tfidf(char* palavra, FrequenciaLivro* pagina, FrequenciaLivro** livro){
    return tf(palavra, pagina) * idf(palavra, livro);
}