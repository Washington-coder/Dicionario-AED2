typedef struct sDicioSemiDinamico DicioSemiDinamico;

DicioSemiDinamico* criar_dicio_sd(long f_carga, long tam);
void inserir_no_dicio_sd(DicioSemiDinamico* dsd, void* info);
void imprime_dicio_sd_encadeado(DicioSemiDinamico* dsd);
void imprime_stats(DicioSemiDinamico* dsd);
//void insecao_encadeamento(DicioSemiDinamico* dsd, long k, void* info);