#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "tab_hash.h"
#include <math.h>
#include <stdbool.h>
#include <ctype.h>

struct sEstatistica {
    long buscas;            // Número total de buscas
    long colisoes;          // Número total de colisões
    long comparacoes;       // Número total de comparações
    long f_carga;           // Fator de carga, determina a quantidade média ideal de colisões
    long maior_colisao;     // Guarda a maior quantidade de colisões no vetor de colisões
    long* v_colisoes;       // Armazena quantas vezes cada posição sofreu uma colisão
};


struct sItem {
    long chave;             // Chave do item
    void* info;             // Carga de informação

    struct sItem* ant;      // Ponteiro para o item anterior
    struct sItem* prox;     // Ponteiro para o próximmo item 
                            // (para o caso de as colisões serem tratadas com uma lista encadeada)
};


struct sDicioSemiDinamico {
    long tamanho;           // tamanho reservado para o dicionário
    long ocupacao;          // a quantidade de posições ocupadas por ele
    Item** pos;              // vetor de itens (o ideal seria um vertor de ponteiros para itens)
    Estatistica* stats;     // estatísticas 
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
    }
    k = abs(k % tamanho);
    
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
    long n = 0, k = 0;

    printf("CONTEÚDOS DO DICIONÁRIO:\n");
    for (long i = 0; i < dsd->tamanho; i++){
        

        if ((dsd->stats->v_colisoes[i]) && (item[i])){
            k = hash(dsd->tamanho, item[i]->info);
            if (k == item[i]->chave){
                printf("índice [%ld]:\t", i);
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
    }
    printf("\n");
}


// ESPECIALISTA: Compara duas infos, quando ambas forem strings
char compara_string(void* info1, void* info2){
    return strcmp(cast_string(info1), cast_string(info2));
}


// FUNÇÕES GERAIS ========================================================================================================

// Imprime os dados estatísticos do dicionário
void imprime_stats(DicioSemiDinamico* dsd, char vetor){
    
    printf("DADOS ESTATÍSTICOS DO DICIONÁRIO:\n");
    
    printf("Fator de Carga: %ld\n\tColisões: %ld\tMaior Colisão: %ld", dsd->stats->f_carga, dsd->stats->colisoes,  dsd->stats->maior_colisao);
    printf("\tBuscas: %ld\tComparações: %ld\n", dsd->stats->buscas, dsd->stats->comparacoes);
    printf("\tCapacidade: %ld\tOcupação: %ld\n", dsd->tamanho, dsd->ocupacao);

    if (vetor){
        printf("Colisões por posição:\n");

        for (long i = 0; i < dsd->tamanho; i++){
            if (dsd->stats->v_colisoes[i]){
                printf("[pos %ld - %ld]\t", i, dsd->stats->v_colisoes[i]);
            }
        }
    }
    printf("\n");
}


// Função hash - apelido para a real função hash, que pode ser uma diferente no futuro
long hash(long tamanho, void* info){
    return proto_hash(tamanho, info);
    //return 0;
}

void* retorna_info(Item* item){
    return item->info;
}

void* retorna_stats(DicioSemiDinamico* dsd){
    return dsd->stats;
}

// Cria um item com chave e informação
Item* criar_item(long chave, void* info){
    Item* item = malloc(sizeof(Item));
    item->chave = chave;
    item->info = info;
    return item;
}

// Cria o dicionário
DicioSemiDinamico* criar_dicio_sd(long f_carga, long tam){
    
    DicioSemiDinamico* dsd = malloc(sizeof(DicioSemiDinamico));

    dsd->stats = malloc(sizeof(Estatistica));
    dsd->stats->v_colisoes = (long*) malloc(sizeof(long) * tam);
    memset(dsd->stats->v_colisoes, 0, tam*sizeof(long));
    
    //printf("b, c, cmp ok\n");       // <=== MVP dos dicionários

    dsd->stats->buscas = 0;
    dsd->stats->colisoes = 0;
    dsd->stats->maior_colisao = 0;
    dsd->stats->comparacoes = 0;
    dsd->stats->f_carga = f_carga;

    dsd->tamanho = tam;
    dsd->ocupacao = 0;
    dsd->pos = malloc(sizeof(Item*) * tam);

    for (long i = 0; i < tam; i++){
        dsd->pos[i] = criar_item(-1, NULL);
    }

    return dsd;
}


// Função de busca por um item em um dicionário
Item* buscar_no_dicio_sd(DicioSemiDinamico* dsd, void* info, char imprimir){
    long k = hash(dsd->tamanho, info);
    if (imprimir){
        printf("BUSCAR: (chave = %ld)\t%s\n", k, cast_string(info));
    }
    long n = 0;
    Item* aux;
    
    dsd->stats->buscas++;

    for (long i = 0; i < dsd->stats->v_colisoes[k]+1; i++){
        
        if (dsd->pos[k]){
            
            if (dsd->pos[k]->info){
                if (!compara(dsd->pos[k]->info, info)){
                    dsd->stats->comparacoes++;

                    return dsd->pos[k];
                }

                else if (dsd->pos[k]->info){
                    
                    aux = dsd->pos[k];

                    while ((aux) && (compara(aux->info,info))){
                        dsd->stats->comparacoes++;
                        aux = aux->prox;
                    }

                    if (aux){
                        return aux;
                    }
                }

            }
            n = 0;

        }
    }
    
    return NULL;
}


void* remove_do_dicio_sd(DicioSemiDinamico* dsd, void* info){
    Item* removido = buscar_no_dicio_sd(dsd,info, 0);
    void* carga;
    
    if (removido){
        carga = removido->info;
        if (removido->ant){
            removido->ant->prox = removido->prox;
        }
        else {
            
            dsd->pos[removido->chave] = removido->prox;
        }
    }
    long k = hash(dsd->tamanho, info);
    dsd->stats->v_colisoes[k]--;
    free(removido);
    return carga;
}



// Função que faz a inserção por encadeamento, no começo da lista, nos casos de colisão
void insecao_encadeamento(DicioSemiDinamico* dsd, long k, Item* item){
    Item* aux = dsd->pos[k], *aux2;

    // Atualiza as estatísticas
    dsd->stats->colisoes++;
    dsd->stats->v_colisoes[k]++;
    

    if (dsd->stats->v_colisoes[k] > dsd->stats->maior_colisao){
        dsd->stats->maior_colisao = dsd->stats->v_colisoes[k];
    }

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
    aux->ant = item;
    dsd->pos[k] = item;
}


// Função de inserção no dicionário 
DicioSemiDinamico* inserir_no_dicio_sd(DicioSemiDinamico* dsd, void* info){
    
    dsd->ocupacao++;
    long k = hash(dsd->tamanho, info);
    Item* item = criar_item(k, info);

    //printf("inserir: ([%ld] %s)\t", k, cast_string(info));

    // Checa se a posição está vazia
    if ((dsd->pos[k]->chave != k)){
        dsd->pos[k] = item;
        dsd->stats->v_colisoes[k] = 1;
        dsd->pos[k]->prox = NULL;
        dsd->pos[k]->ant = NULL;
    }
    // Lida com as colisões
    else{
        insecao_encadeamento(dsd, k, item);
        return NULL;
    }
}


// Function to check if a number is prime
bool is_prime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) return false;
    }
    return true;
}

// Function to find the closest greater prime number
int closest_greater_prime(int n) {
    int i = n + 1;
    while (!is_prime(i)) {
        // Keep incrementing the number until it is prime
        i++;
    }
    return i;
}


DicioSemiDinamico* rehashing(DicioSemiDinamico* dsd){

    double diferenca = dsd->stats->maior_colisao/(double)dsd->stats->f_carga;

    if (diferenca > 1.2){
        printf("\n################################\nREDIMENSIONANDO\n");

        Item* aux, *aux2;
        long tamanho = closest_greater_prime(dsd->tamanho * diferenca), n = 0;
        
        // FAZER UM NOVO DICIO, REINSERIR OS DADOS
        DicioSemiDinamico* new_dsd = criar_dicio_sd(dsd->stats->f_carga, tamanho);

        new_dsd->ocupacao = 0;
        new_dsd->tamanho = tamanho;

        new_dsd->stats->buscas = dsd->stats->buscas;
        new_dsd->stats->comparacoes = dsd->stats->comparacoes;
        new_dsd->stats->f_carga = dsd->stats->f_carga;

        for (long i = 0; i < dsd->tamanho; i++){

            if ((dsd->stats->v_colisoes[i]) && (dsd->pos[i])){
                
                long k = hash(dsd->tamanho, dsd->pos[i]->info);
                
                if (k == dsd->pos[i]->chave){
                    aux = dsd->pos[i];
                    n = 0;
                    while (aux){
                        
                        aux2 = aux->prox;
                        inserir_no_dicio_sd(new_dsd, aux->info);
                        remove_do_dicio_sd(dsd, aux->info);
                        aux = aux2;
                        n++;
                    }
                    
                }
            }
        }
        printf("\n[%ld] %ld <= %ld (%f)\n", dsd->tamanho,dsd->stats->f_carga, dsd->stats->maior_colisao, diferenca);
        printf("\nnovo: [%ld] %ld <= %ld (%f)\n", new_dsd->tamanho,new_dsd->stats->f_carga, new_dsd->stats->maior_colisao, diferenca);
        
        printf("\n###################### NOVO DICIO:\n");
        imprime_stats(new_dsd, 1);
        free(dsd->stats);
        free(dsd);
        dsd = new_dsd;
        
        return new_dsd;
    }
    return NULL;
}

// Função de comparação
char compara(void* info1, void* info2){
    return compara_string(info1, info2);
}


void teste_de_busca(DicioSemiDinamico* dsd, char* pal){
    
    printf("####################################\n");
    printf("BUSCANDO POR \"%s\"\n", pal);

    imprime_item(buscar_no_dicio_sd(dsd, pal, 1));
    
    printf("DADOS DEPOIS DA BUSCA: \n");
    imprime_stats(dsd, 1);
    printf("####################################\n");
}

/*
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
*/