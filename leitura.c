#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "leitura_pag.h"
#include "tab_hash.h"
#include <math.h>
#include <stdbool.h>
#include <ctype.h>
#include "tf_idf.h"

typedef struct listaPa{
    long num_lista;
    TPalavra *lista;
}listaPa;

// Struct tipo página, que contém um vetor de strings, e o número de strings que possui
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

// Struct tipo livro, que contém um vetor de tipos-página, e o número de páginas que possui
struct slivro
{
    TPagina *ps[1000];// TODO - tornar dinâmico, usando a quantidade de páginas do livro
    int num_pag;
};

typedef struct stats{
    long buscas;            // Número total de buscas
    long colisoes;          // Número total de colisões
    long comparacoes;       // Número total de comparações
    long f_carga;           // Fator de carga, determina a quantidade média ideal de colisões
    long maior_colisao;     // Guarda a maior quantidade de colisões no vetor de colisões
    long* v_colisoes;       // Armazena quantas vezes cada posição sofreu uma colisão
} Stats;


int retorna_num_pags(TLivro* livro){
    return livro->num_pag;
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


// Cria lista de palavras (únicas)
listaPa *criaListaPalavras(TPagina *pagina)
{
    if (pagina)
    {
        int qtd_de_palavras = 0, indice = 0;
        struct palavra *lista_de_palavras;
        char* espaco = " ";
        listaPa* lp = malloc(sizeof(listaPa));

        lista_de_palavras = (struct palavra *)malloc(1 * sizeof(struct palavra));

        //printf("\n\t\tP Á G I N A\n");
        for (int i = 0; i < pagina->num_pal; i++)
        {
            
            if (pagina->p[i][0]){

                // Inicializa a lista de palavras
                if (!qtd_de_palavras)
                {
                    strcpy(lista_de_palavras[0].nome, pagina->p[i]);
                    lista_de_palavras[0].qtd_repeticoes = 1;
                    qtd_de_palavras++;
                    
                }
                else
                {
                    indice = estaNaLista(lista_de_palavras, pagina->p[i], qtd_de_palavras);

                    if (indice == -1)
                    {
                        lista_de_palavras = (struct palavra *)realloc(lista_de_palavras, (qtd_de_palavras + 1) * sizeof(struct palavra));
                        strcpy(lista_de_palavras[qtd_de_palavras].nome, pagina->p[i]);
                        lista_de_palavras[qtd_de_palavras].qtd_repeticoes = 1;
                        qtd_de_palavras++;
                    }

                    else
                    {
                        lista_de_palavras[indice].qtd_repeticoes++;
                    }
                }
            }
        }
        lp->lista = lista_de_palavras;
        lp->num_lista = qtd_de_palavras;
        //imprime_lista_palavras(lp->lista, lp->num_lista);
        return lp;
    }
}



// imprime uma página
void imprime_pagina(TPagina *pagina)
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
        imprime_pagina(l->ps[i]);
        printf("\n\n");
    }

    printf("NÚMERO DE PÁGINAS: %d\n", l->num_pag);
}


TPagina *criaPagina()
{
    TPagina *pagina = malloc(sizeof(TPagina));
    pagina->num_pal = 0;
    pagina->p = (char **)malloc(1 * sizeof(char *));
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
    int i = 0;

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
            pagina->p = (char **)realloc(pagina->p, (pagina->num_pal + 1) * sizeof(char *));
            pagina->p[i] = (char *)malloc((strlen(string) + 1) * sizeof(char));
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


DicioSemiDinamico* cria_dicio_lista_palavras(TLivro* lido, long k, long f_carga){

    long tam = lido->ps[k]->listaPalavras->num_lista;
    long primo_tam = closest_greater_prime(tam);

    DicioSemiDinamico* dsd = criar_dicio_sd(f_carga, primo_tam);
    DicioSemiDinamico* new_dsd;
    
    new_dsd = dsd;
    for (int i = 0; i < tam; i++){ 
        TPalavra* palavra = &lido->ps[k]->listaPalavras->lista[i];
        inserir_no_dicio_sd(dsd, palavra);            // se tudo der errado

        /*
        // INSERÇÃO COM REDIMENSIONAMENTO
        if (dsd == new_dsd){
            printf("aquioo?\n");
            new_dsd = inserir_no_dicio_sd(dsd, palavra);
            //printf("%ld\n", new_dsd.)
        }
        else {
            printf("aqui?\n");
            new_dsd = inserir_no_dicio_sd(new_dsd, palavra);
        }
        dsd = new_dsd;
        */

    }
    //new_dsd = rehashing(dsd);
    new_dsd = dsd;
    return new_dsd;
}


DicioSemiDinamico** criar_dicio_livro(TLivro* lido, long f_carga){
    DicioSemiDinamico** lista_dsd = malloc(sizeof(DicioSemiDinamico*) * lido->num_pag), *new_dsd;
    long ultrapassou = 0;
    for (int i = 0; i < lido->num_pag; i++){
        //printf("\n#################### PÁGINA %d\n", i);
        DicioSemiDinamico* dsd = cria_dicio_lista_palavras(lido, i,f_carga);
        
        new_dsd = rehashing(dsd);
        if (new_dsd){
            ultrapassou++;
            dsd = new_dsd;
        };
        lista_dsd[i] = dsd;
        //imprime_stats(dsd, 0);
        
    }
    printf("Dicionários redimensionados:\t%ld\n", ultrapassou);
    return lista_dsd;
}


// Abre o arquivo do livro, e chamar as funções pra ler
TLivro* ler_livro_main(char* obra){
    FILE *fl;
    
    //char *livro = "Paralelismo.base";
    fl = fopen(obra, "r");

    // Ler e criar um vetor de stop words
    char **vetorDeStopWords = carregarStopwords();
    // Ler livro
    TLivro *lido = lerLivro(fl, vetorDeStopWords);

    return lido;
}


int funcao_teste(char* obra){
    TLivro* lido = ler_livro_main(obra);
    DicioSemiDinamico* dsd = cria_dicio_lista_palavras(lido, 0, 5);
    // imprime_dicio_sd_encadeado(dsd);
    // //printf("aaa");
    // imprime_stats(dsd, 1);

    DicioSemiDinamico** lista_dsd = criar_dicio_livro(lido, 5);
    printf("\n");


    long indice = lido->num_pag-1;
    Item* item = buscar_no_dicio_sd(lista_dsd[indice], "cher", 1);
    if(item){
        TPalavra* p = retorna_info(item);
        printf("\n\n\"%s\" se repete %d vezes\n",p->nome, p->qtd_repeticoes);
    }
    else{
        printf("\n\nNão encontrado\n");
    }

    Stats* stats = retorna_stats(lista_dsd[indice]);
    printf("pág 292: %ld colisões, %ld buscas, fator de carga = %ld\n\n", stats->colisoes, stats->buscas, stats->f_carga);

    imprime_stats(lista_dsd[indice], 1);
    printf("\n");


    printf("################ TESTES DO TF-IDF\n");

    double num_tf = tf("universidade", lido->ps[0], lista_dsd[0]);
    printf("TF: %f\n", num_tf);

    long int num_con = n_containing("universidade", lido);
    printf("n_containing: %ld\n", num_con); 

    double num_idf = idf("universidade", lido);
    printf("num_idf: %lf\n", num_idf); 

    double num_tfidf = tfidf("universidade", lido->ps[0], lido, dsd);
    printf("tfidf: %lf\n", num_tfidf);

    // Item* item = buscar_no_dicio_sd(lista_dsd[292], "cher");
    // TPalavra* p = retorna_info(item);
    // printf("%s se repete %d vezes\n",p->nome, p->qtd_repeticoes);

    //Stats* stats = retorna_stats(lista_dsd[292]);
    //printf("pág 292: %ld colisões, %ld buscas, fator de carga = %ld\n", stats->colisoes, stats->buscas, stats->f_carga);



}

/*
int main()
{
    
    funcao_teste("Paralelismo.base");

    //imprime_livro(lido);

    
}
*/
// chcp 65001