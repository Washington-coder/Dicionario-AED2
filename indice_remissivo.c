#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "leitura_pag.h"
#include "tab_hash.h"
#include "tf_idf.h"

// compilar como: gcc indice_remissivo.c leitura.c tabela_hash.c tf_idf.c -o indice_remissivo -lm

int main(){
    
    char obra[48];
    char palavra[48];
    long fator_de_carga = 3;
    
    printf("Nome da obra (que esteja no mesmo diretório, ou o path):\t");
    scanf("%s", obra);
    //strcpy(obra,"Paralelismo.base");
    
    printf("Lendo o livro . . .\n");
    TLivro* livro = ler_livro_main(obra);
    
    printf("Número de páginas: %d\n", retorna_num_pags(livro));

    printf("Criando os dicionários do livro . . .\n");
    DicioSemiDinamico** dsd_livro = criar_dicio_livro(livro, fator_de_carga);
    printf("\t(fator de carga: %ld)\n", fator_de_carga);

    printf("INDICE REMISSIVO\nQue palavra?\t");
    scanf("%s", palavra);
    //strcpy(palavra,"universidade");
    buscar_indice_remissivo(palavra, livro, dsd_livro);


}