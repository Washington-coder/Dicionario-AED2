#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "dicio_semi_dinamico.h"

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

typedef struct sDicioSemiDinamico {
    Item* pos;
    long tamanho;
    long ocupacao;
    Estatistica* stats;
} DicioSemiDinamico;


// função que cria uma entrada
static Item criar_entrada(long chave, void* info){
    Item item;
    item.chave = chave;
    item.info = info;
    item.prox = NULL;

    return item;
}

static long proto_hash(DicioSemiDinamico* de, long chave, void* item){
    long k = 0;
    
}

// função de hashing
long hashing(DicioSemiDinamico* de, void* item){
    long k = 0;
    // TODO
    //for (long i = 0; i < de->tamanho; )
}

static char inserir_colisao_lista(DicioSemiDinamico* de, long chave, long k, void* info){

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

static Item* buscar_colisao_lista(DicioSemiDinamico* de, long chave, long k){
    Item item = de->pos[k];

    if (item.chave){ 
        Item* aux = item.prox;
        while ((item.chave != chave) && (aux)){
            aux = aux->prox;
            item = *aux;
        }
        return &item; 
    }
    else{ return NULL; }
}

// função de criação de um dicionário estático
DicioSemiDinamico* criar_dicio_s_dinamico(long tamanho){
    DicioSemiDinamico* de = malloc(sizeof(DicioSemiDinamico));
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
char inserir_no_dicio_s_dinamico(DicioSemiDinamico* de, long chave, void* info){
    long k = hashing(de, chave);
    
    // colisões:
    inserir_colisao_lista(de, chave, k, info);
    // inserir_colisao_vetor(de, chave, k, info);

    return 1;
}

// função de busca em um dicionário estático
Item* buscar_dicio_s_dinamico(DicioSemiDinamico* de, long chave, void* info){
    de->stats->buscas++;

    long ch = hashing(de, chave);

    // colisões
    return buscar_colisao_lista(de, chave, ch);
    // return buscar_colisão_vetor
    
}

