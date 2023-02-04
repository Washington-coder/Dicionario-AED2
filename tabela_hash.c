#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "tab_hash.h"

typedef struct sEstatistica {
    long* v_colisoes;       // Armazena quantas vezes cada posição sofreu uma colisão
    long buscas;            // Número total de buscas
    long comparacoes;       // Número total de comparações
    long f_carga;           // Fator de carga, determina a quantidade média ideal de colisões
    long colisoes;          // Número total de colisões
} Estatistica;


typedef struct sItem {
    long chave;             // Chave do item
    void* info;             // Carga de informação

    struct sItem* prox;     // Ponteiro para o próximmo item 
                            // (para o caso de as colisões serem tratadas com uma lista encadeada)
} Item;


struct sDicioSemiDinamico {
    Item** pos;              // vetor de itens (o ideal seria um vertor de ponteiros para itens)
    Estatistica* stats;     // estatísticas 
    long tamanho;           // tamanho reservado para o dicionário
    long ocupacao;          // a quantidade de posições ocupadas por ele
};


// FUNÇÕES ESPECIALISTAS =================================================================================================

// ESPECIALISTA: Recebe um dado em ponteiro void e retorna a string correspondente
char* cast_string(void* info){
    char* palavra = malloc(sizeof(char) * 48);
    strcpy(palavra, info);

    return palavra;
}


// ESPECIALISTA: Função hash - protótipo: retso da divisão da soma das letras*(peso_n = peso_(n-1)) pelo tamanho do dicio
long proto_hash(long tamanho, void* info){
    char* palavra = cast_string(info);
    long k = 0, peso = 2;

    for (int i = 0; i < strlen(palavra); i++){
        peso *= 1.5;
        k += palavra[i] * peso;
        //printf("%ld\t%ld\n", peso, k);
    }
    k = k % tamanho;
    //printf("%ld\n", k);
    return k;
}


// ESPECIALISTA: Imprime um item quando suas informações forem uma string
void imprime_item(Item* item){
    if (item){
        printf("%s (chave: %ld)\n", cast_string(item->info), item->chave);
    }
}


// ESPECIALISTA: Imprime os conteúdos do dicionário, caso a informação seja uma string
void imprime_dicio_sd_encadeado(DicioSemiDinamico* dsd){
    Item** item = dsd->pos, *aux;
    long n = 0;

    printf("CONTEÚDOS DO DICIONÁRIO:\n");
    for (long i = 0; i < dsd->tamanho; i++){

        if (item[i]){

            printf("índice [%ld]\n", i);

            aux = item[i];
            n = 0;

            while (aux){
                printf("[pos %ld - %s] ", n, cast_string(aux->info));
                aux = aux->prox;
                n++;
            }
            printf("\n");
        }
    }
    printf("\n");
}


// ESPECIALISTA: Compara duas infos, quando ambas forem strings
char compara_string(void* info1, void* info2){
    return strcmp(cast_string(info1), cast_string(info2));
}


// FUNÇÕES GERAIS ========================================================================================================

// Imprime os dados estatísticos do dicionário
void imprime_stats(DicioSemiDinamico* dsd){
    
    printf("DADOS ESTATÍSTICOS DO DICIONÁRIO:\n");

    printf("Fator de Carga: %ld\n\tColisões: %ld", dsd->stats->f_carga, dsd->stats->colisoes);
    printf("\tBuscas: %ld\tComparações: %ld\n", dsd->stats->buscas, dsd->stats->comparacoes);
    printf("Colisões por posição:\n");

    for (long i = 0; i < dsd->tamanho; i++){
        if (dsd->stats->v_colisoes[i]){
            printf("[pos %ld - %ld]\t", i, dsd->stats->v_colisoes[i]);
        }
    }
    printf("\n");
}


// Função hash - apelido para a real função hash, que pode ser uma diferente no futuro
long hash(long tamanho, void* info){
    //printf("%s\n", cast_string(info));
    
    return proto_hash(tamanho, info);
}

// Cria o dicionário
DicioSemiDinamico* criar_dicio_sd(long f_carga, long tam){
    
    DicioSemiDinamico* dsd = malloc(sizeof(DicioSemiDinamico));

    dsd->stats = malloc(sizeof(Estatistica));
    dsd->stats->v_colisoes = (long*) malloc(sizeof(long) * tam);

    //printf("b, c, cmp ok\n");       // <=== MVP dos dicionários

    dsd->stats->buscas = 0;
    dsd->stats->colisoes = 0;
    dsd->stats->comparacoes = 0;
    dsd->stats->f_carga = f_carga;

    dsd->tamanho = tam;
    dsd->ocupacao = 0;
    dsd->pos = malloc(sizeof(Item*) * tam);

    return dsd;
}


// Cria um item com chave e informação
Item* criar_item(long chave, void* info){
    Item* item = malloc(sizeof(Item));
    item->chave = chave;
    item->info = info;
    return item;
}


// Função que faz a inserção por encadeamento, no começo da lista, nos casos de colisão
void insecao_encadeamento(DicioSemiDinamico* dsd, long k, Item* item){
    Item* aux = dsd->pos[k], *aux2;

    // Atualiza as estatísticas
    dsd->stats->colisoes++;
    dsd->stats->v_colisoes[k]++;

    /* // Inserção no final
    while(aux){
        printf("* ");
        aux2 = aux;
        aux = aux->prox;
    }
    aux2->prox = item;
    */
    
    // Inserção no começo
    item->prox = aux;
    dsd->pos[k] = item;

    //printf("%p\t%s\n",dsd->pos[k]->prox, cast_string(dsd->pos[k]->info));
}


// Função de inserção no dicionário 
void inserir_no_dicio_sd(DicioSemiDinamico* dsd, void* info){
    //printf("vai inserir %s\n", cast_string(info));

    long k = hash(dsd->tamanho, info);

    Item* item = criar_item(k, info);
    
    // Checa se a posição está vazia
    if (!dsd->pos[k]){
        dsd->pos[k] = item;
        
    }
    // Lida com as colisões
    else {
        insecao_encadeamento(dsd, k, item);
    }
}


// Função de comparação
char compara(void* info1, void* info2){
    return compara_string(info1, info2);
}


// Função de busca por um item em um dicionário
Item* buscar_no_dicio_sd(DicioSemiDinamico* dsd, void* info){
    long k = hash(dsd->tamanho, info);
    long n = 0;
    Item* aux;
    
    dsd->stats->buscas++;

    for (long i = 0; i < dsd->stats->v_colisoes[k]+1; i++){
        //printf("%ld aqui?\n", k);
        if (dsd->pos[k]){
            if (!compara(dsd->pos[k]->info, info)){
                dsd->stats->comparacoes++;
                //printf("Encontrou %s, indice %ld pos %ld\n", cast_string(dsd->pos[k]->info), k, n);
                return dsd->pos[k];
            }

            else if (dsd->pos[k]->info){
                aux = dsd->pos[k];

                while ((aux) && (compara(aux->info,info))){
                    dsd->stats->comparacoes++;
                    aux = aux->prox;
                }

                if (aux){
                    //printf("Encontrou %s, indice %ld pos %ld\n", cast_string(aux->info), k, n);
                    return aux;
                }
            }
            n = 0;

        }
    }
    //printf("%s? Não encontrado\n", cast_string(info));

    return NULL;
}


void teste_de_busca(DicioSemiDinamico* dsd, char* pal){
    //char pal[48] = pal;
    printf("####################################\n");
    printf("BUSCANDO POR \"%s\"", pal);

    imprime_item(buscar_no_dicio_sd(dsd, pal));
    
    printf("DADOS DEPOIS DA BUSCA: \n");
    imprime_stats(dsd);
    printf("####################################\n");
}

int main(){
    DicioSemiDinamico* dsd = criar_dicio_sd(3, 101);
    //printf("%ld\n", dsd->stats->f_carga);
    
    
    char p1[48] = "sofrimento";
    inserir_no_dicio_sd(dsd, p1);

    char p2[48] = "dor";
    inserir_no_dicio_sd(dsd, p2);

    char p3[48] = "dejavu";
    inserir_no_dicio_sd(dsd, p3);
    

    //printf("\t%ld %s\t%s\t%s\n", dsd->stats->v_colisoes[0],
    //cast_string(dsd->pos[46]->info),cast_string(dsd->pos[14]->info)
    //,cast_string(dsd->pos[11]->info));

    imprime_dicio_sd_encadeado(dsd);
    imprime_stats(dsd);
    
    teste_de_busca(dsd, "dor");
    teste_de_busca(dsd, "felicidade");
    teste_de_busca(dsd, "sofrimento");
    teste_de_busca(dsd, "paz");
    teste_de_busca(dsd, "dor");
}
