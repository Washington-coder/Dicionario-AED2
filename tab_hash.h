#include "stdio.h"
#include "stdlib.h"
#include "string.h"

typedef struct sDicioSemiDinamico DicioSemiDinamico;
typedef struct sItem Item;
typedef struct sEstatistica Estatistica;

// Cria o dicionário
DicioSemiDinamico* criar_dicio_sd(long f_carga, long tam);

// Função de inserção no dicionário 
DicioSemiDinamico* inserir_no_dicio_sd(DicioSemiDinamico* dsd, void* info);

// Função de busca por um item em um dicionário
Item* buscar_no_dicio_sd(DicioSemiDinamico* dsd, void* info, char imprimir);

void* remove_do_dicio_sd(DicioSemiDinamico* dsd, void* info);

// Função hash - apelido para a real função hash, que pode ser uma diferente no futuro
long hash(long tamanho, void* info);

DicioSemiDinamico* rehashing(DicioSemiDinamico* dsd);

// Função de comparação
char compara(void* info1, void* info2);

void* retorna_info(Item* item);

void* retorna_stats(DicioSemiDinamico* dsd);

// ESPECIALISTA: Recebe um dado em ponteiro void e retorna a string correspondente
char* cast_string(void* info);

// ESPECIALISTA: Função hash - protótipo: retso da divisão da soma das letras*(peso_n = peso_(n-1)) pelo tamanho do dicio
long proto_hash(long tamanho, void* info);

// ESPECIALISTA: Imprime um item quando suas informações forem uma string
void imprime_item(Item* item);

// ESPECIALISTA: Imprime os conteúdos do dicionário, caso a informação seja uma string
void imprime_dicio_sd_encadeado(DicioSemiDinamico* dsd);

// ESPECIALISTA: Compara duas infos, quando ambas forem strings
char compara_string(void* info1, void* info2);

// Imprime os dados estatísticos do dicionário
void imprime_stats(DicioSemiDinamico* dsd, char vetor);

int closest_greater_prime(int n);