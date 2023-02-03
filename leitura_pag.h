#include "stdio.h"

typedef struct pagina TPagina;
typedef struct palavra TPalavra;
TPagina* le_palavra(FILE* fl);
TPalavra *criaListaPalavras(TPagina *pagina);