#include "stdio.h"
#include "stdlib.h"
#include "string.h"

typedef struct sEstatistica {
    long buscas;
    long comparacoes;
} Estatistica;

typedef struct sItem {
    long chave;
    void* info;
} Item;

typedef struct sDicioEstatico {
    Item* pos;
    long tamanho;
    long ocupacao;
    Estatistica* stats;
} DicioEstatico;


// função que cria uma entrada
Item* criar_entrada(DicioEstatico* de, void* info){
    Item* item = malloc(sizeof(Item));
    long k = hashing(de, item);
    item->chave = k;
    item->info = info;

    return item;
}

// função de hashing
long hashing(DicioEstatico* de, void* item){
    long k = 0;
    // TODO
    //for (long i = 0; i < de->tamanho; )
}

// função de criação de um dicionário estático
DicioEstatico* criar_dicio_estatico(long tamanho){
    DicioEstatico* de = malloc(sizeof(DicioEstatico));
    de->tamanho = tamanho;
    de->ocupacao = 0;
    de->stats->buscas = 0;
    de->stats->comparacoes = 0;
    de->pos = malloc(sizeof(Item*) * tamanho);

    return de;
}

// função de inserção em um dicionário estático
char inserir_no_dicio_estatico(DicioEstatico* de, void* info){
    long k = hashing(de, info);
    Item* item = criar_entrada(de, info);
    de->pos[k] = item; // ???

    return 1;
}

// função de busca em um dicionário estático
Item* buscar_dicio_estatico(DicioEstatico* de, void* info){
    de->stats->buscas++;

    long chave = hashing(de, info);
    // TODO
}

