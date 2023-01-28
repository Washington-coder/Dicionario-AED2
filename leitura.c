#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "leitura_pag.h"
struct pagina
{
    char p[1000][48];
    int num_pal;
};

typedef struct slivro
{
    TPagina *ps[1000];
    int num_pag;
} TLivro;

// imprime uma página
void imprime_pagina(TPagina *p)
{
    for (int j = 0; j < p->num_pal; j++)
    {
        printf("%s ", p->p[j]);
    }
    printf("\n");
}

void printPag(TPagina *pagina)
{
    for (int j = 0; j < pagina->num_pal; j++)
    {
        printf("%s ", pagina->p[j]);
    }
    printf("\n\n");
}

// imprime um livro inteiro, indicando as páginas
void imprime_livro(TLivro *l)
{
    for (int i = 0; i < l->num_pag; i++)
    {
        printf("PÁGINA %d ###########\n", i + 1);
        printf("NÚMERO DE PALAVRAS: %d \n", l->ps[i]->num_pal);
        printPag(l->ps[i]);
        printf("\n\n");
    }

    printf("NÚMERO DE PÁGINAS: %d\n", l->num_pag);
}

TPagina *criaPagina()
{
    TPagina *pagina = malloc(sizeof(TPagina));
    pagina->num_pal = 0;
    return pagina;
}

void ehStopword(char **stopwords, char * palavra){
    // for (int i = 0; i < 392; i++) {
    //     if(strcmp(stopwords[i], palavra) == 0) {
    //         printf("\n\neh uma stopword");
    //         return 1;
    //     }else{
    //         return 0;
    //     }
    // }

    for (int i = 0; i < 392; i++) {
        if(strcmp(stopwords[i], palavra) == 0) {
            printf("\n\neh uma stopword");
        }
    }
}

TPagina *lerPagina(FILE *fl, char** stopwords)
{
    char palavra[48];
    TPagina *pagina = criaPagina();

    short estaNaPagina = 1;
    int i = 0;

    while (estaNaPagina)
    {
        fscanf(fl, "%*[^A-Za-zãõâêîôûáéíóúàèìòùÃÕÂÊÎÔÛÁÉÍÓÚÀÈÌÒÙçÇ]");

        if ((fscanf(fl, "%49[A-Za-zãõâêîôûáéíóúàèìòùÃÕÂÊÎÔÛÁÉÍÓÚÀÈÌÒÙçÇ]", palavra) != 1) || (!strcmp(palavra, "PA")))
        {
            break;
        }

        ehStopword(stopwords, pagina->p[i]);

        // if (ehStopword(stopwords, pagina->p[i])){
        //     strcpy(pagina->p[i], "*");
        // }else{
        //     strcpy(pagina->p[i], palavra);
        // }

        // strcpy(pagina->p[i], palavra);
        i++;
        pagina->num_pal++;
    }

    // condição de parada para a leitura de livros
    if (!pagina->num_pal)
    {
        return NULL;
    }

    return pagina;
}

TLivro *lerLivro(FILE *fl, char** stopwords)
{
    TLivro *livro = malloc(sizeof(TLivro));
    livro->num_pag = 0;

    TPagina *pagina = lerPagina(fl, stopwords);
    pagina = lerPagina(fl, stopwords); // por melhorar k
    while (pagina)
    {
        livro->ps[livro->num_pag] = pagina;
        livro->num_pag++;
        pagina = lerPagina(fl, stopwords);
    }
    return livro;
}

char **carregarStopwords()
{
    FILE *fl;
    char *livro = "stopwords_br.txt";
    fl = fopen(livro, "r");
    int i;

    char **stopwords = malloc(392 * sizeof(char *));
    for (i = 0; i < 392; ++i)
        stopwords[i] = malloc(48 * sizeof(char));

    char palavra[48];
    i = 0;

    while(fscanf(fl, "%s", palavra) == 1){
        strcpy(stopwords[i], palavra);
        i++;
    }

    return stopwords;
}

int main()
{
    FILE *fl;
    char *livro = "Paralelismo.base";
    fl = fopen(livro, "r");

    char **vetorDeStopWords = carregarStopwords();

    TLivro* lido = lerLivro(fl, vetorDeStopWords);

    imprime_livro(lido);


}

// chcp 65001
// teste (amanda)