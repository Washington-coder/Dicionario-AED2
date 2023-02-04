typedef struct sDicioSemiDinamico DicioSemiDinamico;

// Cria o dicionário
DicioSemiDinamico* criar_dicio_sd(long f_carga, long tam);

// Função de inserção no dicionário 
void inserir_no_dicio_sd(DicioSemiDinamico* dsd, void* info);

// Função de busca por um item em um dicionário
Item* buscar_no_dicio_sd(DicioSemiDinamico* dsd, void* info);

// Função hash - apelido para a real função hash, que pode ser uma diferente no futuro
long hash(long tamanho, void* info);

// Função de comparação
char compara(void* info1, void* info2);

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
void imprime_stats(DicioSemiDinamico* dsd);