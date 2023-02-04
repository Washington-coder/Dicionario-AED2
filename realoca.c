#include <stdio.h>
#include <stdlib.h>

int main() {
  int n = 0;
  int size = 1;
  int input;
  int *vector = (int *) malloc(size * sizeof(int));

  if (vector == NULL) {
    printf("Memória insuficiente");
    return 1;
  }

  printf("Insira elementos do vetor (para encerrar, digite qualquer letra):\n");
  while (scanf("%d", &input) == 1) {
    if (n == size) {
      size += 1;
      vector = (int *) realloc(vector, size * sizeof(int));
      if (vector == NULL) {
        printf("Memória insuficiente");
        return 1;
      }
    }
    vector[n++] = input;
  }

  printf("Vetor: [ ");
  for (int i = 0; i < n; i++) {
    printf("%d ", vector[i]);
  }
  printf("]\n");

  free(vector);

  return 0;
}
