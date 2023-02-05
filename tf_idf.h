#include "stdio.h"
#include "leitura_pag.h"

long tf(TPalavra* palavra, TPagina* pagina);
long int n_containing(TPalavra* palavra, TLivro* livro);
long idf(TPalavra* palavra, TLivro* livro);
long tfidf(TPalavra* palavra, TPagina* pagina, TLivro* livro);