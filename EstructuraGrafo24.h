#ifndef Graf_H
#define Graf_H
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Declaraciones

typedef uint32_t u32;

typedef u32 color;

typedef struct {
  u32 n_vertices;
  u32 m_lados;
  u32 delta;
  u32 *grados;
  color *vxs_color; // array dinamico con el color de cada vertice
  // u32 grafo[MAX_G][MAX_G];
  u32 **vertices; // un array de dos dimensiones dinamico con los vecinos de
                  // cada vertice
  // u32 id;      // Nose si esto sirva para busqueda, lo pongo por si las dudas
  u32 *vecinos; // para Vecino() creo q es mejor que lo definamos asi
} GrafoSt;

#endif