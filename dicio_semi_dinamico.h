typedef struct sEstatistica Estatistica;

typedef struct sItem Item;

typedef struct sDicioSemiDinamico DicioSemiDinamico;

long hashing(DicioSemiDinamico* de, void* item);

DicioSemiDinamico* criar_dicio_s_dinamico(long tamanho);

char inserir_no_dicio_s_dinamico(DicioSemiDinamico* de, long chave, void* info);

Item* buscar_dicio_s_dinamico(DicioSemiDinamico* de, long chave, void* info);
