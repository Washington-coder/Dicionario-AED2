#include "stdio.h"
#include "stdlib.h"
#include "string.h"

typedef struct sEstatistica {
    long buscas;
    long comparacoes;
    long colisoes;
    long* v_colisoes;
} Estatistica;

typedef struct sItem {
    long chave;
    void* info;

    struct sItem* prox;
} Item;

typedef struct sDicioEstatico {
    Item* pos;
    long tamanho;
    long ocupacao;
    Estatistica* stats;
} DicioEstatico;


// função que cria uma entrada
Item criar_entrada(long chave, void* info){
    Item item;
    //long k = hashing(de, item);
    item.chave = chave;
    item.info = info;
    item.prox = NULL;

    return item;
}

// função de hashing
long hashing(DicioEstatico* de, void* item){
    long k = 0;
    // TODO
    //for (long i = 0; i < de->tamanho; )
}

char colisao_lista(DicioEstatico* de, long chave, long k, void* info){

    if (de->pos[k].chave != NULL){ // malloc retorna NULL?
    // if (de->stats->v_colisoes[k]){
        de->stats->colisoes++;
        de->stats->v_colisoes[k]++;
        Item* aux = de->pos[k].prox;
        while (aux){
            aux = aux->prox;
        }

        Item item = criar_entrada(chave, info);
        aux = &item;
    }
    else{
        de->stats->v_colisoes = 0;
        de->pos[k] = criar_entrada(chave, info);
    }
}

// função de criação de um dicionário estático
DicioEstatico* criar_dicio_estatico(long tamanho){
    DicioEstatico* de = malloc(sizeof(DicioEstatico));
    de->tamanho = tamanho;
    de->ocupacao = 0;

    de->stats->buscas = 0;
    de->stats->comparacoes = 0;
    de->stats->colisoes = 0;
    de->stats->v_colisoes = malloc(sizeof(long) * tamanho);

    de->pos = malloc(sizeof(Item*) * tamanho);

    return de;
}

// função de inserção em um dicionário estático
char inserir_no_dicio_estatico(DicioEstatico* de, long chave, void* info){
    long k = hashing(de, chave);
    
    // colisões:
    colisao_lista(de, chave, k, info);
    // colisao_vetor(de, chave, k, info);

    return 1;
}

// função de busca em um dicionário estático
Item* buscar_dicio_estatico(DicioEstatico* de, void* info){
    de->stats->buscas++;

    long chave = hashing(de, info);
    // TODO
}

