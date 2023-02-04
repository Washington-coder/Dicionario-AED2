#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "leitura_pag.h"
#include "dicio_semi_dinamico.h"

int main(){
    FILE *fl;
    char *livro = "teste.base";
    fl = fopen(livro, "r");
    char *stpw = "stopwords_br.txt";

    // Ler e criar um vetor de stop words
    char **vetorDeStopWords = carregarStopwords(stpw);

    // Ler livro
    TLivro *lido = lerLivro(fl, vetorDeStopWords);

    imprime_livro(lido);

    printf("\n\n%s\n", lido->ps[1]->listaPalavras[49].nome);
}