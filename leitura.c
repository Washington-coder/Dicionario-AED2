#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "leitura_pag.h"

struct pagina{
    char p[1000][48];
    int num_pal;
};

typedef struct slivro{
    TPagina* ps[1000];
    int num_pag;
}TLivro;

// imprime uma página
void imprime_pagina(TPagina* p){
    for (int j = 0; j < p->num_pal; j++) {
        printf("%s ", p->p[j]);
    }
    printf("\n");
}

void printPag(TPagina* pagina) {
    for (int j = 0; j < pagina->num_pal; j++)
    {
        printf("%s ", pagina->p[j]);
    }
    printf("\n\n");
}

// imprime um livro inteiro, indicando as páginas 
void imprime_livro(TLivro* l){
    for (int i = 0; i < l->num_pag; i++){
        printf("PÁGINA %d ###########\n", i+1);
        printf("NÚMERO DE PALAVRAS: %d \n", l->ps[i]->num_pal);
        printPag(l->ps[i]);
        printf("\n\n");
    }

    printf("NÚMERO DE PÁGINAS: %d\n", l->num_pag);
}

TPagina* criaPagina(){
    TPagina *pagina = malloc(sizeof(TPagina));
    pagina->num_pal = 0;
    return pagina;
}

TPagina *lerPagina(FILE *fl)
{
    char palavra[48];
    TPagina* pagina = criaPagina();

    short estaNaPagina = 1;
    int i = 0;

    while (estaNaPagina)
    {
        fscanf(fl, "%*[^A-Za-zãõâêîôûáéíóúàèìòùÃÕÂÊÎÔÛÁÉÍÓÚÀÈÌÒÙçÇ]");

        if ((fscanf(fl, "%49[A-Za-zãõâêîôûáéíóúàèìòùÃÕÂÊÎÔÛÁÉÍÓÚÀÈÌÒÙçÇ]", palavra) != 1) || (!strcmp(palavra, "PA")))
        {
            break;
        }

        strcpy(pagina->p[i], palavra);
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



TLivro* lerLivro(FILE* fl) {
    TLivro* livro = malloc(sizeof(TLivro));
    livro->num_pag = 0;

    TPagina *pagina = lerPagina(fl);
    pagina = lerPagina(fl); // por melhorar k
    while (pagina)
    {
        livro->ps[livro->num_pag] = pagina;
        livro->num_pag++;
        pagina = lerPagina(fl);
    }
    
    return livro;
}

int main()
{
    FILE *fl;
    char *livro = "Paralelismo.base";
    fl = fopen(livro, "r");

    TLivro* lido = lerLivro(fl);
    
    imprime_livro(lido);
    
    
}

// chcp 65001