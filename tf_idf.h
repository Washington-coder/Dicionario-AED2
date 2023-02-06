#include "stdio.h"
#include "leitura_pag.h"
#include "tab_hash.h"

double tf(char* palavra, TPagina* pagina, DicioSemiDinamico* dsd);
long int n_containing(char* palavra, TLivro* livro);
double idf(char *palavra, TLivro *livro);
double tfidf(char *palavra, TPagina *pagina, TLivro *livro, DicioSemiDinamico *dsd);
