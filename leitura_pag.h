#include "stdio.h"

typedef struct pagina TPagina;
TPagina* le_palavra(FILE* fl);

typedef struct slivro TLivro;

void imprime_livro(TLivro *l);

TLivro *lerLivro(FILE *fl, char **stopwords);