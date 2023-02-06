#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "leitura_pag.h"
#include "tab_hash.h"
#include "tf_idf.h"

int main(){
    
    char obra[48];
    long fator_de_carga = 3;
    
    printf("Nome da obra (que esteja no mesmo diretório, ou o path):\t");
    scanf("%s", obra);
    
    printf("Lendo o livro . . .\n");
    TLivro* livro = ler_livro_main(obra);
    
    printf("Número de páginas: %d\n", retorna_num_pags(livro));

    printf("Criando os dicionários do livro . . .\n");
    DicioSemiDinamico** dsd_livro = criar_dicio_livro(livro, fator_de_carga);
    printf("\t(fator de carga: %d)", fator_de_carga);

    





    //imprime_livro(livro);

    

}