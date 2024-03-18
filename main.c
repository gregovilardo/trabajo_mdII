#include "APIG24.h"
#include <stdio.h>

int main() {
  Grafo G = ConstruirGrafo();
  printf("Numero de vertices %d\nNumero de lados %d\ndelta: %d\n",
         NumeroDeVertices(G), NumeroDeLados(G), Delta(G));
  for (int i = 0; i < G->vertices[1].grado; i++) {
    printf("%d ", G->vertices[1].vecinos[i]);
  }
}
