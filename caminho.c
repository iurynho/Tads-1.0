/*
 * Arquivo: caminho.c
 * Autor(es): Iury Dias Ribeiro
 * Matricula(s): 0071470
 * Data: 19/10/2026
 *
 * Caminho minimo em grafo dirigido.
 * Para pesos nao negativos, utiliza Dijkstra. Se existir algum peso
 * negativo, utiliza Bellman-Ford, pois Dijkstra nao seria correto.
 */

#include "caminho.h"

#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static void GimprimePartida(int partida)
{
    printf("%d\n", partida);
}

static int GtemPesoNegativo(Grafo g, const float *pesos)
{
    int aresta;

    for (aresta = GAprimeiraAresta(g); aresta != 0;
         aresta = GAproximaAresta(g, aresta)) {
        double peso = (double)pesos[aresta];

        if (isfinite(peso) && peso < 0.0) {
            return 1;
        }
    }

    return 0;
}

static void GexecutaDijkstra(Grafo g, const float *pesos,
                             int destinoFinal, double *distancia,
                             int *anterior, int *visitado)
{
    for (;;) {
        int v;
        int escolhido = 0;
        double menorDistancia = DBL_MAX;

        /*
         * Os vertices sao percorridos em ordem crescente. Em caso de
         * empate, permanece escolhido o menor identificador.
         */
        for (v = GVprimeiroVertice(g); v != 0;
             v = GVproximoVertice(g, v)) {
            if (!visitado[v] && distancia[v] < menorDistancia) {
                menorDistancia = distancia[v];
                escolhido = v;
            }
        }

        if (escolhido == 0 || distancia[escolhido] == DBL_MAX) {
            break;
        }

        visitado[escolhido] = 1;
        if (escolhido == destinoFinal) {
            break;
        }

        {
            int aresta;

            for (aresta = GAprimaSaida(g, escolhido); aresta != 0;
                 aresta = GAproxSaida(g, escolhido, aresta)) {
                int destino = GVomega(g, aresta);
                double peso = (double)pesos[aresta];

                if (!isfinite(peso) || visitado[destino]) {
                    continue;
                }

                if (distancia[escolhido] + peso < distancia[destino]) {
                    distancia[destino] = distancia[escolhido] + peso;
                    anterior[destino] = escolhido;
                }
            }
        }
    }

}

static void GexecutaBellmanFord(Grafo g, const float *pesos,
                                int numeroVertices, double *distancia,
                                int *anterior)
{
    int iteracao;

    /* Em um grafo sem ciclo negativo, |V|-1 passagens sao suficientes. */
    for (iteracao = 1; iteracao < numeroVertices; ++iteracao) {
        int aresta;
        int alterou = 0;

        for (aresta = GAprimeiraAresta(g); aresta != 0;
             aresta = GAproximaAresta(g, aresta)) {
            int origem = GValfa(g, aresta);
            int destino = GVomega(g, aresta);
            double peso = (double)pesos[aresta];

            if (!isfinite(peso) || distancia[origem] == DBL_MAX) {
                continue;
            }

            if (distancia[origem] + peso < distancia[destino]) {
                distancia[destino] = distancia[origem] + peso;
                anterior[destino] = origem;
                alterou = 1;
            }
        }

        if (!alterou) {
            break;
        }
    }
}

void Gcaminho(Grafo g, float *pesos, int a, int b)
{
    double *distancia;
    int *anterior;
    int *visitado;
    int *caminho;
    int maxVertices;
    int numeroVertices;
    int atual;
    int tamanhoCaminho;
    int chegouNaPartida;

    if (g == NULL || pesos == NULL
        || !GBexisteIdVertice(g, a)
        || !GBexisteIdVertice(g, b)) {
        GimprimePartida(a);
        return;
    }

    if (a == b) {
        GimprimePartida(a);
        return;
    }

    maxVertices = GInumeroVerticesMax(g);
    numeroVertices = GInumeroVertices(g);

    distancia = (double *)malloc(((size_t)maxVertices + 1U)
                                  * sizeof(*distancia));
    anterior = (int *)calloc((size_t)maxVertices + 1U,
                             sizeof(*anterior));
    visitado = (int *)calloc((size_t)maxVertices + 1U,
                             sizeof(*visitado));
    caminho = (int *)malloc(((size_t)numeroVertices + 1U)
                            * sizeof(*caminho));

    if (distancia == NULL || anterior == NULL
        || visitado == NULL || caminho == NULL) {
        free(caminho);
        free(visitado);
        free(anterior);
        free(distancia);
        GimprimePartida(a);
        return;
    }

    for (atual = 0; atual <= maxVertices; ++atual) {
        distancia[atual] = DBL_MAX;
    }
    distancia[a] = 0.0;

    if (GtemPesoNegativo(g, pesos)) {
        GexecutaBellmanFord(g, pesos, numeroVertices, distancia, anterior);
    } else {
        GexecutaDijkstra(g, pesos, b, distancia, anterior, visitado);
    }

    if (distancia[b] == DBL_MAX) {
        free(caminho);
        free(visitado);
        free(anterior);
        free(distancia);
        GimprimePartida(a);
        return;
    }

    tamanhoCaminho = 0;
    atual = b;
    chegouNaPartida = 0;

    /* O limite evita ciclo infinito se houver ciclo negativo nos dados. */
    while (atual != 0 && tamanhoCaminho <= numeroVertices) {
        caminho[tamanhoCaminho] = atual;
        ++tamanhoCaminho;

        if (atual == a) {
            chegouNaPartida = 1;
            break;
        }

        atual = anterior[atual];
    }

    if (!chegouNaPartida) {
        GimprimePartida(a);
    } else {
        int indice;

        for (indice = tamanhoCaminho - 1; indice >= 0; --indice) {
            printf("%d", caminho[indice]);
            if (indice > 0) {
                printf(" -> ");
            }
        }
        printf("\n");
    }

    free(caminho);
    free(visitado);
    free(anterior);
    free(distancia);
}
