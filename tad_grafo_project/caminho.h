/*
 * Arquivo: caminho.h
 * Autor(es): PREENCHER
 * Matricula(s): PREENCHER
 * Data: 19/10/2026
 */

#ifndef CAMINHO_H
#define CAMINHO_H

#include "grafo.h"

/*
 * Imprime um caminho de menor peso de a ate b no grafo dirigido.
 * O vetor pesos deve ser indexado pelo identificador da aresta.
 */
void Gcaminho(Grafo g, float *pesos, int a, int b);

#endif
