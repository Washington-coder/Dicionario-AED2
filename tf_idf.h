#include "stdio.h"
#include "leitura_pag.h"
#include "tab_hash.h"

double tf(char* palavra, TPagina* pagina, DicioSemiDinamico* dsd);
long int n_containing(char* palavra, TLivro* livro);
long idf(TPalavra* palavra, TLivro* livro);
//long tfidf(TPalavra* palavra, TPagina* pagina, TLivro* livro);