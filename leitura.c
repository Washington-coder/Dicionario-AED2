#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "leitura_pag.h"
#include <ctype.h>


// Struct tipo página, que contém um vetor de strings, e o número de strings que possui
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
    int qtd_de_palavras;
};


// Checa se uma palavra está na lista de palavras (únicas)
int estaNaLista(TPalavra *lista_de_palavras, char * palavra, int qtd_de_palavras)
{
    
    for (int i = 0; i < qtd_de_palavras; i++)
    {
        //printf("%s\t%s %d\n", palavra, lista_de_palavras[i].nome, i);
        if (strcmp(palavra, lista_de_palavras[i].nome) == 0)
        {
            return i;
        }
    }
    return -1;
}

// 
void imprime_lista_palavras(struct palavra* lista_de_palavras, int qtd_de_palavras){
    
    printf("PÁGINA\n");
    for (int i = 0; i < qtd_de_palavras; i++)
    {
        printf("palavra[%d]: %s\t", i, lista_de_palavras[i].nome);
        printf("repete: %d vezes\n", lista_de_palavras[i].qtd_repeticoes);
    }
    printf("\n");
}

// Cria lista de palavras (únicas)
TPalavra *criaListaPalavras(TPagina *pagina)
{
    if (pagina)
    {
        int qtd_de_palavras = 0, indice = 0;
        struct palavra *lista_de_palavras;
        char* espaco = " ";

        lista_de_palavras = (struct palavra *)malloc(pagina->num_pal * sizeof(struct palavra));
        //lista_de_palavras[0] = NULL;

        //printf("\n\t\tP Á G I N A\n");
        for (int i = 0; i < pagina->num_pal; i++)
        {
            
            if (pagina->p[i][0]){
                //printf("%s\t", pagina->p[i]);

                // Inicializa a lista de palavras
                if (!qtd_de_palavras)
                {
                    strcpy(lista_de_palavras[0].nome, pagina->p[i]);
                    lista_de_palavras[0].qtd_repeticoes = 1;
                    qtd_de_palavras++;
                    
                    //printf("primeira: %s\tq: %d\ti: %d\tr: %d\n", pagina->p[i], qtd_de_palavras, i, lista_de_palavras[0].qtd_repeticoes);
                }

                else
                {
                    indice = estaNaLista(lista_de_palavras, pagina->p[i], qtd_de_palavras);
                    //printf("%s",lista_de_palavras[0].nome);
                    //printf("indice: %d, %s == %s\t", indice, pagina->p[i], lista_de_palavras[qtd_de_palavras].nome);

                    // Adiciona palavra à lista de palavras
                    if (indice == -1)
                    {
                        // printf("nao esta na lista\n");
                        strcpy(lista_de_palavras[qtd_de_palavras].nome, pagina->p[i]);
                        lista_de_palavras[qtd_de_palavras].qtd_repeticoes = 1;
                        qtd_de_palavras++;

                        //printf("new - r: %d\tq: %d\t",lista_de_palavras[qtd_de_palavras].qtd_repeticoes, qtd_de_palavras );

                    }

                    else
                    {
                        lista_de_palavras[indice].qtd_repeticoes++;
                        //printf("rep - r: %d\tq: %d\t",lista_de_palavras[indice].qtd_repeticoes, qtd_de_palavras );
                    }
                }
                //printf("\n");
            }
        }
        imprime_lista_palavras(lista_de_palavras, qtd_de_palavras);
    }
}

// Struct tipo livro, que contém um vetor de tipos-página, e o número de páginas que possui
typedef struct slivro
{
    TPagina *ps[1000];// TODO - tornar dinâmico, usando a quantidade de páginas do livro
    int num_pag;
} TLivro;

// imprime uma página
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


// Checa se a palavra é uma stopword
int ehStopword(char **stopwords, char *palavra)
{
    // Itera por cada stop word do vetor, e compara com a palavra
    for (int i = 0; i < 392; i++)
    {
        // Se forem iguais, retorna positivo
        if (strcmp(stopwords[i], palavra) == 0)
        {
            return 1;
        }
    }

    // Se não, negativo
    return 0;
}


// Passa por cada caractere da string, e transforma em minúsculo
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


// Ler página, filtrando fora as stopwords
TPagina *lerPagina(FILE *fl, char **stopwords, int num_pagina)
{
    char palavra[48];
    TPagina *pagina = criaPagina();

    short estaNaPagina = 1;
    int i = 0, paginaIndex = 0;

    while (estaNaPagina)
    {
        // Ler tudo que não for uma palavra com caracteres comuns, e descarta
        fscanf(fl, "%*[^A-Za-zãõâêîôûáéíóúàèìòùÃÕÂÊÎÔÛÁÉÍÓÚÀÈÌÒÙçÇ]");
        //fscanf(fl, "%*[\t]");

        // Ler a palavra, e checar se chegou no fim do arquivo, ou se é igual ao marcador "PA"
        if ((fscanf(fl, "%49[A-Za-zãõâêîôûáéíóúàèìòùÃÕÂÊÎÔÛÁÉÍÓÚÀÈÌÒÙçÇ]", palavra) != 1) || (!strcmp(palavra, "PA")))
        {
            // Se sim, pára a leitura
            break;
        }

        // Transforma a palavra em minúsculo, para evitar repetições
        char *string = malloc(strlen(palavra));
        strcpy(string, passarParaMinusculo(palavra));

        // Checa se é uma stopword
        if (!ehStopword(stopwords, string))
        {
            // Se não, adiciona na página
            strcpy(pagina->p[i], string);
            pagina->num_pal++;
            i++;
        }
    }

    // condição de parada para a leitura de livros (na função lerLivro(.))
    if (!pagina->num_pal)
    {
        return NULL;
    }
    pagina->num_pagina = num_pagina;
    pagina->listaPalavras = criaListaPalavras(pagina);
    return pagina;
}


// Ler e retornar um livro, sem stopwords
TLivro *lerLivro(FILE *fl, char **stopwords)
{
    // Criar um livro do tipo TLivro e inicializar
    TLivro *livro = malloc(sizeof(TLivro));
    livro->num_pag = 0;

    // Ler a "primeira" página (buffer NULL) 
    // (chamar a função pela primeira vez no arquivo sempre retorna NULL, por motivos misteriosos)
    TPagina *pagina = lerPagina(fl, stopwords, livro->num_pag);

    // Ler a primeira página (de verdade)
    pagina = lerPagina(fl, stopwords, livro->num_pag); // por melhorar k

    // Ler todas as páginas
    while (pagina)
    {
        // Inserir dentro do livro
        livro->ps[livro->num_pag] = pagina;
        livro->num_pag++;
        
        // Ler a próxima página
        pagina = lerPagina(fl, stopwords, livro->num_pag);
    }

    return livro;
}


// Cria e retorna um vetor de stopwords
char **carregarStopwords()
{
    // Abre arquivo de stopwords
    FILE *fl;
    char *livro = "stopwords_br.txt";
    fl = fopen(livro, "r");
    int i;

    // Cria um vetor de palavras com a quantidade de stopwords
    char **stopwords = malloc(392 * sizeof(char *));
    for (i = 0; i < 392; ++i)
        stopwords[i] = malloc(48 * sizeof(char));

    char palavra[48];
    i = 0;

    // Percorre o arquivo de stopwords e adiciona no vetor
    while (fscanf(fl, "%s", palavra) == 1)
    {
        strcpy(stopwords[i], palavra);
        i++;
    }

    return stopwords;
}


// Abre o arquivo do livro, e chamar as funções pra ler
int main()
{
    FILE *fl;
    char *livro = "teste.base";
    fl = fopen(livro, "r");

    // Ler e criar um vetor de stop words
    char **vetorDeStopWords = carregarStopwords();

    // Ler livro
    TLivro *lido = lerLivro(fl, vetorDeStopWords);

    imprime_livro(lido);
}

// chcp 65001