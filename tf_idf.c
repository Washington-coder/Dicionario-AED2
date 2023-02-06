#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "leitura_pag.h"
#include "tab_hash.h"
#include "tf_idf.h"
#include "math.h"

// Tipo contendo o dicionário de palavras, com suas ocorrências e páginas
typedef struct sLivro
{
    DicioSemiDinamico *frequencia_livro; // uh oh (pointer?)
    TLivro *livro;                       // uh oh 2
} FrequenciaLivro;

struct pagina
{
    char **p;
    int num_pal;
    int num_pagina;
    listaPa *listaPalavras;
};

struct palavra
{
    char nome[48];
    int qtd_repeticoes;
    int qtd_de_palavras;
    long pag;
    double tf_idf;
};

struct slivro
{
    TPagina *ps[1000];
    int num_pag;
};

typedef struct listaPa
{
    long num_lista;
    TPalavra *lista;
} listaPa;

// função:
// percorrer o livro, criar dicionários de cada lista de palavras de cada página
// manter o número total de palavras

// função:
// fazer um dicion´ário com todas as palavras únicas do livro,
// manter em cada palavra

// retorna a frequência do termo em uma página (tpalavra, tpagina)
double tf(char *palavra, TPagina *pagina, DicioSemiDinamico *dsd)
{
    // quatindade de vezes que a palavra aparece
    // /
    // quantidade total

    // pegar um dicionário da lista de palavras dessa página, pesquisar, e retornar a divisão
    TPalavra* p;
    Item *it = buscar_no_dicio_sd(dsd, palavra,0);
    
    if (it){
        p = retorna_info(it);
        int qtd_total_de_palavras = pagina->num_pal;
        int qtd_de_repeticoes_da_palavra = p->qtd_repeticoes;

        double tf = qtd_de_repeticoes_da_palavra / ((double)qtd_total_de_palavras);
        //printf("t:%d r:%d = tf:%f\n", qtd_total_de_palavras, qtd_de_repeticoes_da_palavra, tf);
        return tf;
    }
    else{
        return 0;
    }
    //printf("aqui??\n");

    
}

// retorna a quantidade de páginas que contém um termo (tpalavra, tlivro)
long int n_containing(char *palavra, TLivro *livro)
{
    // fazer um dicionário de cada página/lista de palavras, procurar pela palavra em cada dicionário de página, retornar um contador

    long int contador = 0;

    // indice da pagina
    for (int i = 0; i < livro->num_pag; i++)
    {
        TPagina *pagina = malloc(sizeof(TPagina));
        pagina = livro->ps[i];

        listaPa *lista_de_palavras = malloc(sizeof(listaPa));
        lista_de_palavras->lista = pagina->listaPalavras->lista;

        char *stringPesquisada = malloc(sizeof(strlen(palavra)));
        strcpy(stringPesquisada, palavra);

        int qtd_palavras_na_lista = pagina->listaPalavras->num_lista;
        // indice da lista de palavras
        for (int j = 0; j < qtd_palavras_na_lista; j++)
        {
            char *palavra_da_lista = malloc(sizeof(strlen(lista_de_palavras->lista[j].nome)));
            strcpy(palavra_da_lista, pagina->listaPalavras->lista[j].nome);

            if(strcmp(stringPesquisada, palavra_da_lista) == 0){
                contador++;
            }
        }
    }
    return contador;
}

// retorna o quão comum é uma palavra em uma série de páginas (tpalavra, tlivro)
double idf(char *palavra, TLivro *livro)
{
    // log do
    // número total de páginas / número de páginas em que a palavra aparece + 1
    // log(num_págs/ n_containing())
    double result = log(livro->num_pag/(n_containing(palavra, livro)+1));
    return result;
}

// retorna o TF-IDF (com dicionário)
double tfidf(char *palavra, TPagina *pagina, TLivro *livro, DicioSemiDinamico *dsd)
{
    // retorna um vetor de tamanho 5, com os maiores TF-IDFs
    // return tf(palavra, pagina, dsd) * idf(palavra, livro);
    double tff = tf(palavra, pagina, dsd);
    //printf("aqui?\n");

    return tff * idf(palavra, livro);
}

TPalavra* cria_p(){
    TPalavra* p = malloc(sizeof(TPalavra));
    p = NULL;
    return p;
}

TPalavra* find_greatest_five(DicioSemiDinamico* *array, long size, void* info, TLivro* livro) {

    // Find the five largest values
    TPalavra* greatest_values[5] = {cria_p(), cria_p(), cria_p(), cria_p(), cria_p()};
    //{NULL, NULL, NULL, NULL, NULL};
    int count = 0;
    printf("Procurando . . .\n");
    for (int i = 0; i < size; i++) {
        Item* it = buscar_no_dicio_sd(array[i], info,0);
        //printf("1 aqui? %d\n", i);
        if (it){
            TPalavra* p = retorna_info(it);
            //printf("2 aqui?\n");
            if (p){
            double current_value = tfidf(info, livro->ps[i], livro, array[i]);
            //printf("3 aqui?\n");
            p->tf_idf = current_value;
            p->pag = i;
            //printf("4 aqui?\n");
            printf("\npágina %ld, TF-IDF: %f ", p->pag, p->tf_idf);
            count++;
                if (count == 5){
                    break;
                }
            }
            // for (int j = 0; j < 5; j++) {
            //     //printf("%p ", greatest_values[j]);
            //     printf("...\n");
            //     if(greatest_values[j]){
            //         //printf("aqui?\n");
            //     if (current_value > greatest_values[j]->tf_idf) {
                    
            //         // Shift the other values to make room for the new one
            //         for (int k = 4; k > j; k--) {
            //             greatest_values[k] = greatest_values[k - 1];
            //         }
            //         greatest_values[j] = p;
            //         break;
            //     }
            //     }
            // }
        }

    }

    return NULL;
}

TPalavra* buscar_indice_remissivo(char* palavra, TLivro* livro, DicioSemiDinamico** dsd){
    long pags = retorna_num_pags(livro), repete = 0;

    return find_greatest_five(dsd, livro->num_pag, palavra, livro);
}