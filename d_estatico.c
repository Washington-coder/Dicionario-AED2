#include "stdio.h"
#include "stdlib.h"
#include "string.h"


typedef struct sItem {
    long chave;
    void* info;
} Item;

typedef struct sDicioEstatico {
    Item* pos;
    long tamanho;
    long ocupacao;
} DicioEstatico;

// função de hashing
long hashing(DicioEstatico* de, Item* item){

}

// função de criação de um dicionário estático
DicioEstatico* criar_dicio_estatico(int tamanho){

}

// função de inserção em um dicionário estático
char inserir_no_dicio_estatico(void* info){

}

// função de busca em um dicionário estático
Item* buscar_dicio_estatico(void* info){

}

