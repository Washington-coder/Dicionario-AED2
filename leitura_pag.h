#include "stdio.h"
#include "tab_hash.h"

typedef struct listaPa listaPa;
typedef struct pagina TPagina;
typedef struct palavra TPalavra;
typedef struct slivro TLivro;
listaPa *criaListaPalavras(TPagina *pagina);
DicioSemiDinamico* cria_dicio_lista_palavras(TLivro* lido, long k);
DicioSemiDinamico** criar_dicio_livro(TLivro* lido);