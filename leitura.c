#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "leitura_pag.h"
#include <ctype.h>
struct pagina
{
    char p[1000][48];
    int num_pal;
    int num_pagina;
    TPalavra *listaPalavras;
};
struct palavra
{
    char nome[48];
    int qtd_repeticoes;
    int pagina;
};

TPalavra *criaListaPalavras(TPagina *pagina)
{
    if (pagina)
    {
        struct palavra *lista_de_palavras;
        lista_de_palavras = (struct palavra *)malloc(pagina->num_pal*sizeof(struct palavra));

        for (int i = 0; i < pagina->num_pal; i++){
            strcpy(lista_de_palavras[i].nome, pagina->p[i]);
            printf("palavra[%d]: %s\n", i, lista_de_palavras[i].nome);
        }

        // for (int i = 0; i < pagina->num_pal; i++)
        // {
        //     if (palavras == NULL)
        //     {
        //         palavras[indexPalavras] = malloc(sizeof(TPalavra));
        //         strcpy(palavras[indexPalavras]->nome, pagina->p[i]);
        //         palavras[indexPalavras]->pagina = pagina->num_pagina; 
        //         indexPalavras++;
        //     }else{
        //         printf("\nnao eh null");   
        //     }
            
        //     printf("Palavra[%d]: %s\n", i, pagina->p[i]);
        // }
    }
}

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

int ehStopword(char **stopwords, char *palavra)
{
    for (int i = 0; i < 392; i++)
    {
        if (strcmp(stopwords[i], palavra) == 0)
        {
            return 1;
        }
    }
    return 0;
}

char *passarParaMinusculo(char *palavra)
{

    char *string = malloc(strlen(palavra));

    strcpy(string, palavra);

    for (int i = 0; i < strlen(string); i++)
    {
        string[i] = tolower(string[i]);
    }
    return string;
}

TPagina *lerPagina(FILE *fl, char **stopwords, int num_pagina)
{
    char palavra[48];
    TPagina *pagina = criaPagina();

    short estaNaPagina = 1;
    int i = 0, paginaIndex = 0;

    while (estaNaPagina)
    {
        fscanf(fl, "%*[^A-Za-zãõâêîôûáéíóúàèìòùÃÕÂÊÎÔÛÁÉÍÓÚÀÈÌÒÙçÇ]");

        if ((fscanf(fl, "%49[A-Za-zãõâêîôûáéíóúàèìòùÃÕÂÊÎÔÛÁÉÍÓÚÀÈÌÒÙçÇ]", palavra) != 1) || (!strcmp(palavra, "PA")))
        {
            break;
        }

        char *string = malloc(strlen(palavra));
        strcpy(string, passarParaMinusculo(palavra));

        if (!ehStopword(stopwords, string))
        {
            strcpy(pagina->p[i], string);
            pagina->num_pal++;
        }
        i++;
    }

    // condição de parada para a leitura de livros
    if (!pagina->num_pal)
    {
        return NULL;
    }
    pagina->num_pagina = num_pagina;
    pagina->listaPalavras = criaListaPalavras(pagina);
    return pagina;
}

TLivro *lerLivro(FILE *fl, char **stopwords)
{
    TLivro *livro = malloc(sizeof(TLivro));
    livro->num_pag = 0;

    TPagina *pagina = lerPagina(fl, stopwords, livro->num_pag);
    pagina = lerPagina(fl, stopwords, livro->num_pag); // por melhorar k
    while (pagina)
    {
        livro->ps[livro->num_pag] = pagina;
        livro->num_pag++;
        pagina = lerPagina(fl, stopwords, livro->num_pag);
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

    while (fscanf(fl, "%s", palavra) == 1)
    {
        strcpy(stopwords[i], palavra);
        i++;
    }

    return stopwords;
}

int main()
{
    FILE *fl;
    char *livro = "teste.base";
    fl = fopen(livro, "r");

    char **vetorDeStopWords = carregarStopwords();

    TLivro *lido = lerLivro(fl, vetorDeStopWords);

    imprime_livro(lido);
}

// chcp 65001
// teste (amanda)