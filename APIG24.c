#include "APIG24.h"

Grafo ConstruirGrafo() {
  // TODO: leer desde stdin
  Grafo G = (Grafo)malloc(sizeof(GrafoSt));
  if (G == NULL) {
    fprintf(stderr, "Error: No se pudo asignar memoria para el G.\n");
    exit(EXIT_FAILURE);
  }

  // GrafoSt G;
  u32 n, m, v, u;
  char line[1000];

  // printf("HOLA");
  // Ignorar las líneas que comienzan con 'c'
  while (1) {
    if (fgets(line, sizeof(line), stdin) == NULL) {
      printf("Error al leer la entrada.\n");
      exit(EXIT_FAILURE);
    }
    if (line[0] != 'c')
      break;
  }

  if (sscanf(line, "p edge %d %d", &n, &m) != 2) {
    printf("Error al leer la entrada.\n");
    exit(EXIT_FAILURE);
  }

  G->n_vertices = n;
  G->m_lados = m;

  G->vertices = (Vertice *)malloc(G->n_vertices * sizeof(Vertice));
  if (G->vertices == NULL) {
    fprintf(stderr, "Error: No se pudo asignar memoria para los vertices.\n");
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < m; i++) {
    if (fgets(line, sizeof(line), stdin) == NULL) {
      printf("Error al leer la entrada.\n");
      exit(EXIT_FAILURE);
    } else {
      if (sscanf(line, "e %d %d", &v, &u) != 2) {
        printf("Error al leer la entrada.\n");
        exit(EXIT_FAILURE);
      }
    }

    Vertice *V = &(G->vertices[v]);
    V->vecinos = (u32 *)realloc(V->vecinos, (V->grado + 1) * sizeof(Vertice));
    if (V->vecinos == NULL) {
      fprintf(stderr, "Error: No se pudo asignar memoria para los vertices.\n");
      exit(EXIT_FAILURE);
    }

    Vertice *U = &(G->vertices[u]);
    U->vecinos = (u32 *)realloc(U->vecinos, (U->grado + 1) * sizeof(Vertice));
    if (U->vecinos == NULL) {
      fprintf(stderr, "Error: No se pudo asignar memoria para los vertices.\n");
      exit(EXIT_FAILURE);
    }
    U->vecinos[U->grado] = v; // Aca mas que el numero podriamos agregar un nodo
                              // q señale al vertice v
    V->vecinos[V->grado] = u; // pero no creo que sea necesario
    V->grado += 1;
    U->grado += 1;
  }

  G->delta = 0;
  for (int i = 0; i < n; i++) {
    if (G->delta < G->vertices[i].grado) {
      G->delta = G->vertices[i].grado;
    }
  }

  return G;
}

void DestruirGrafo(Grafo G) {
  for (int i = 0; i < G->n_vertices; i++) {
    free(G->vertices[i].vecinos);
    free(&(G->vertices[i]));
  }
  free(G);
}

u32 NumeroDeVertices(Grafo G) { return G->n_vertices; }

u32 NumeroDeLados(Grafo G) { return G->m_lados; }

u32 Delta(Grafo G) { return G->delta; }

u32 Grado(u32 i, Grafo G) {
  if (i >= G->n_vertices)
    return 0;
  return G->vertices[i].grado;
}

color Color(u32 i, Grafo G) {
  if (i >= G->n_vertices)
    return 4294967295; // 2^32 - 1

  return G->vertices[i].color;
}

u32 Vecino(u32 j, u32 i, Grafo G) {
  if (i >= G->n_vertices || j >= G->vertices[i].grado)
    return 4294967295; // 2^32 - 1

  return G->vertices[i].vecinos[j];
}

void AsignarColor(color x, u32 i, Grafo G) {
  if (i < G->n_vertices)
    G->vertices[i].color = x;
}

void ExtraerColores(Grafo G, color *Color) {
  for (int i = 0; i < G->n_vertices; i++)
    Color[i] = G->vertices[i].color;
}

void ImportarColores(color *Color, Grafo G) {
  for (int i = 0; i < G->n_vertices; i++)
    G->vertices[i].color = Color[i];
}
