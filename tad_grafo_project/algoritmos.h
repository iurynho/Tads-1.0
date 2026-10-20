#ifndef ALGORITMOS_H
#define ALGORITMOS_H

#include "grafo.h"

/*
 * Implementações pedidas no TP, com entrada/saída em modo texto.
 *
 * Convenções:
 * - A saída do histórico usa o formato v<id> e a<id>.
 * - Sempre que necessário, o vetor pesos deve estar indexado por id de aresta.
 *   Ou seja: pesos[a] é o peso da aresta de identificador a.
 */

/* Árvore Geradora Mínima (AGM) */
void AGM(Grafo g, const float *pesos);

/* Busca em Largura (BEL) */
void BEL(Grafo g, int partida);

/* Busca em Profundidade (BEP) */
void BEP(Grafo g, int partida);

/* Caminho mais curto (CMC): caminho + distância total */
void CMC(Grafo g, const float *pesos, int partida, int chegada);

/* Componentes Conexos (CC) */
void CC(Grafo g);

#endif
