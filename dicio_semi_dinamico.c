#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "dicio_semi_dinamico.h"


typedef struct sEstatistica {
    long buscas;            // Número total de buscas
    long comparacoes;       // Número total de comparações
    long colisoes;          // Número total de colisões
    long* v_colisoes;       // Armazena quantas vezes cada posição sofreu uma colisão
} Estatistica;


typedef struct sItem {
    long chave;             // Chave do item
    void* info;             // Carga de informação

    struct sItem* prox;     // Ponteiro para o próximmo item 
                            // (para o caso de as colisões serem tratadas com uma lista encadeada)
} Item;


typedef struct sDicioSemiDinamico {
    Item* pos;              // vetor de itens (o ideal seria um vertor de ponteiros para itens)
    long tamanho;           // tamanho reservado para o dicionário
    long ocupacao;          // a quantidade de posições ocupadas por ele
    Estatistica* stats;     // estatísticas 
} DicioSemiDinamico;


// função que cria uma entrada
static Item criar_entrada(long chave, void* info){
    Item item;
    item.chave = chave;
    item.info = info;
    item.prox = NULL;

    return item;
}

// função hash de teste
static long proto_hash(DicioSemiDinamico* de, long chave, void* item){
    long k = 0;
    // TODO
    
}

// função de hashing
long hashing(DicioSemiDinamico* de, void* item){
    long k = 0;
    // TODO
    //for (long i = 0; i < de->tamanho; )
}


// Lida com colisões durante a inserção, usando listas encadeadas
static char inserir_colisao_lista(DicioSemiDinamico* de, long chave, long k, void* info){

    // checa se não é vazio
    if (de->pos[k].chave != NULL){ // malloc retorna NULL?
    // if (de->stats->v_colisoes[k]){
        de->stats->colisoes++;

        // aumenta a quantidade de colisões que aconteceram nessa posição específica "k"
        de->stats->v_colisoes[k]++; 

        // insere a informação na última posição da lista encadeada
        Item* aux = de->pos[k].prox;
        while (aux){
            aux = aux->prox;
        }

        Item item = criar_entrada(chave, info);
        aux = &item;
    }

    // no caso de ser vazio, não há colisões
    else{
        de->stats->v_colisoes[k] = 0;
        de->pos[k] = criar_entrada(chave, info);
    }
}

// Lida com colisões durante a inserção, usando vetores
static char inserir_colisao_vetor(DicioSemiDinamico* de, long chave, long k, void* info){
    // TODO
    return 0;
}


// Lida com colisões durante a busca, usando listas encadeadas
static Item* buscar_colisao_lista(DicioSemiDinamico* de, long chave, long k, void* info){
    Item item = de->pos[k];

    // Checa se a posição está vazia
    if (item.info){
    // if (item.chave){ 
        Item* aux = item.prox;

        // compara as infos e caminha pela lista encadeada
        while ((item.info != info) && (aux)){   // TODO solução temporária
                                                // tem que ser substituído por uma função especialista de comparação
            aux = aux->prox;
            item = *aux;
        }

        // Retorna o item, se achou
        if (item.info == info) {
            return &item; 
        }
        else {
            return NULL;
        }
    }
    else{ return NULL; }
}

// função de criação de um dicionário estático
DicioSemiDinamico* criar_dicio_s_dinamico(long tamanho){
    
    // Inicializa dados do dicionário
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
    // Gera o índice no dicionário pro meio de hashing
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
    Item* item = buscar_colisao_lista(de, chave, ch, info);

    if (!item) { 
        printf("Item não encontrado\n"); 
        return NULL;
    }

    return item;
    // return buscar_colisão_vetor
    
}