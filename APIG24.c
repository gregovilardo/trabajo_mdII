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

  // Ignorar las líneas que comienzan con 'c'
  while (1) {
    if (fgets(line, sizeof(line), stdin) == NULL) {
      printf("Error al leer la entrada.\n");
      exit(EXIT_FAILURE);
    }
    if (line[0] != 'c')
      break;
  }

  scanf("p edge %d %d", &n, &m);
  G->n_vertices = n;
  G->m_lados = m;

  G->vxs_color = (color *)calloc(G->n_vertices, sizeof(color));
  if (G->vxs_color == NULL) {
    fprintf(stderr, "Error: No se pudo asignar memoria para los colores.\n");
    exit(EXIT_FAILURE);
  }
  G->vertices = (u32 **)malloc(G->n_vertices * sizeof(u32 *));
  if (G->vertices == NULL) {
    fprintf(stderr, "Error: No se pudo asignar memoria para los vertices.\n");
    exit(EXIT_FAILURE);
  }
  G->grados = (u32 *)calloc(G->n_vertices, sizeof(u32));
  if (G->grados == NULL) {
    fprintf(stderr, "Error: No se pudo asignar memoria para los grados.\n");
    exit(EXIT_FAILURE);
  }
  G->vecinos = (u32 *)calloc(G->n_vertices, sizeof(u32));
  if (G->vecinos == NULL) {
    fprintf(stderr, "Error: No se pudo asignar memoria para los vecinos.\n");
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < m; i++) {
    scanf("e %d %d", &u, &v);
    G->grados[v] += 1;
    G->grados[u] += 1;

    // G->vxs_color[v] = 0; //Ya lo hizo calloc  (?
    // G->vxs_color[u] = 0;
    G->vertices[v][u] = 1;
    G->vertices[u][v] = 1;
    G->vecinos[v] = u;
    G->vecinos[u] = v;
  }

  G->delta = 0;
  for (int i = 0; i < n; i++) {
    if (G->delta < G->grados[i]) {
      G->delta = G->grados[i];
    }
  }

  return G;
}

void DestruirGrafo(Grafo G) {
  free(G->vxs_color);
  free(G->grados);
  for (int i = 0; i < G->n_vertices; i++) {
    free(G->vertices[i]);
  }
  free(G);
}

u32 NumeroDeVertices(Grafo G) { return G->n_vertices; }

u32 NumeroDeLados(Grafo G) { return G->m_lados; }

u32 Delta(Grafo G) { return G->delta; }

u32 Grado(u32 i, Grafo G) {
  if (i >= G->n_vertices)
    return 0;
  return G->grados[i];
}

color Color(u32 i, Grafo G) {
  if (i >= G->n_vertices)
    return 4294967295; // 2^32 - 1

  return G->vxs_color[i];
}

u32 Vecino(u32 j, u32 i, Grafo G) {
  if (i >= G->n_vertices || j >= G->grados[i])
    return 4294967295; // 2^32 - 1

  return G->vecinos[j];
}

void AsignarColor(color x, u32 i, Grafo G) {
  if (i < G->n_vertices)
    G->vxs_color[i] = x;
}

void ExtraerColores(Grafo G, color *Color) {
  for (int i = 0; i < G->n_vertices; i++)
    Color[i] = G->vxs_color[i];
}

void ImportarColores(color *Color, Grafo G) {
  for (int i = 0; i < G->n_vertices; i++)
    G->vxs_color[i] = Color[i];
}
