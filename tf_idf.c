#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "leitura_pag.h"
#include "dicio_semi_dinamico.h"

typedef struct sLivro{
    DicioSemiDinamico* frequencia_livro; // uh oh (pointer?)
    TLivro* livro; // uh oh 2
} FrequenciaLivro;


// retorna a frequência do termo em um documento
long tf(char* palavra, FrequenciaLivro* livro){

}

// retorna a quantidade de documentos que contém um termo
// necessário?
long n_containing(char* palavra, FrequenciaLivro** livros){

}

// retorna o quão comum é uma palavra em uma série de documentos
// necessário?
long idf(char* palavra, FrequenciaLivro** livros){

}

// retorna o TF-IDF
// necessário?
long tfidf(char* palavra, FrequenciaLivro* livro, FrequenciaLivro** livros){
    return tf(palavra, livro) * idf(palavra, livros);
}