#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#define NWORDS (5000)

int main()
{
    int count = 0;
    FILE *fl;
    char palavra[48];
    short estaNaPagina = 1;

    char *livro = "Paralelismo.base";
    fl = fopen(livro, "r");

    char kelime[NWORDS][48];

    size_t i;
    for (i = 0; i < NWORDS; i++)
    {
        // Toss ("" indicates do not save) characters that are not ("^" indicates not) letters.
        // Ignore return value
        fscanf(fl, "%[^A-Za-zãõâêîôûáéíóúàèìòùÃÕÂÊÎÔÛÁÉÍÓÚÀÈÌÒÙçÇ]");

        // Read letters
        // Expect only a return value of 1:Success or EOF:no more file to read
        // Be sure to limit number of characters read: 49
        if (fscanf(fl, "%49[A-Za-zãõâêîôûáéíóúàèìòùÃÕÂÊÎÔÛÁÉÍÓÚÀÈÌÒÙçÇ]", kelime[i]) != 1)
            break;
        printf("%s\n", kelime[i]);

        if (strcmp(kelime[i], "PA") == 0)
        {
            count++;
        }
    }
    printf("count: %d", count);
}