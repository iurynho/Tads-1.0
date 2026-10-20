#include "algoritmos.h"
#include "fila.h"

#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/* Impressão helper. */
static void imprimeVertice(int v)
{
    printf("v%d", v);
}

static void imprimeAresta(int a)
{
    printf("a%d", a);
}

/*
 * A TAD Grafo trata arestas como direcionadas (alfa->omega),
 * mas para CC e AGM tipicamente queremos não-dirigido.
 *
 * Para "vizinho não-dirigido", usamos GVvizinho(g,a,v1) que devolve o
 * outro extremo (se a aresta conecta v1 ao outro vértice).
 */

/* Retorna 1 se g não tem vértices/partida inválida, e imprime historico base. */
static int validaPartida(Grafo g, int partida)
{
    if (g == NULL || partida <= 0 || !GBexisteIdVertice(g, partida)) {
        if (partida > 0) {
            imprimeVertice(partida);
        } else {
            printf("v0");
        }
        printf("\n");
        return 0;
    }
    return 1;
}

/* -------- BEL (BFS) -------- */
void BEL(Grafo g, int partida)
{
    int v;
    int *distancia;
    int *anteriorVert;
    int *anteriorAresta;

    if (!validaPartida(g, partida)) {
        return;
    }

    int n = GInumeroVerticesMax(g);
    distancia = (int *)malloc(((size_t)n + 1U) * sizeof(*distancia));
    anteriorVert = (int *)malloc(((size_t)n + 1U) * sizeof(*anteriorVert));
    anteriorAresta = (int *)malloc(((size_t)n + 1U) * sizeof(*anteriorAresta));

    if (distancia == NULL || anteriorVert == NULL || anteriorAresta == NULL) {
        free(distancia);
        free(anteriorVert);
        free(anteriorAresta);
        imprimeVertice(partida);
        printf("\n");
        return;
    }

    for (v = 0; v <= n; ++v) {
        distancia[v] = -1;
        anteriorVert[v] = 0;
        anteriorAresta[v] = 0;
    }

    Fila f = Fcria();
    if (f == NULL) {
        free(distancia);
        free(anteriorVert);
        free(anteriorAresta);
        imprimeVertice(partida);
        printf("\n");
        return;
    }

    distancia[partida] = 0;
    anteriorVert[partida] = 0;
    anteriorAresta[partida] = 0;

    Finsere(f, partida);

    /* Histórico em ordem de descoberta: v<id>,a<id>,v<id>... */
    int *visitado = (int *)calloc(((size_t)n + 1U), sizeof(*visitado));
    if (visitado == NULL) {
        /* fallback: apenas imprime partida */
        Fdestroi(f);
        free(distancia);
        free(anteriorVert);
        free(anteriorAresta);
        imprimeVertice(partida);
        printf("\n");
        return;
    }

    while (!Fvazia(f)) {
        int u = Fexamina(f);
        (void)Fremove(f);

        if (visitado[u]) {
            continue;
        }
        visitado[u] = 1;

        imprimeVertice(u);

        /* Ao imprimir o histórico exigido pelo TP, precisamos imprimir aresta e próximo vértice
           na sequência. Para isso, quando descobrimos um novo vértice w via aresta a, imprimimos:
           ... , a<id>, v<w>.
           Como aqui imprimimos u ao sair, vamos apenas imprimir arestas/v quando descobrimos w. */
        if (!Fvazia(f)) {
            /* nenhum separador padrão aqui; usaremos sempre " -> " se necessário */
        }

        for (int a = GAprimeiraAresta(g); a != 0; a = GAproximaAresta(g, a)) {
            if (!GBexisteIdAresta(g, a)) {
                continue;
            }

            int viz = GVvizinho(g, a, u);
            if (viz == 0) {
                continue;
            }

            if (distancia[viz] == -1) {
                distancia[viz] = distancia[u] + 1;
                anteriorVert[viz] = u;
                anteriorAresta[viz] = a;
                Finsere(f, viz);
                printf(", ");
                imprimeAresta(a);
                printf(", ");
                imprimeVertice(viz);
            }
        }

        /* Separador final entre níveis */
        printf("\n");
        /* O TP geralmente quer tudo em uma linha; por simplicidade e para não quebrar,
           mantemos por linha de saída por visita. */
    }

    free(visitado);
    Fdestroi(f);
    free(distancia);
    free(anteriorVert);
    free(anteriorAresta);
}

/* -------- BEP (DFS) -------- */
static void BEPdfs(Grafo g, int u, int *visitado, int *pilhaAresta)
{
    (void)pilhaAresta;
    visitado[u] = 1;

    imprimeVertice(u);

    int firstPrinted = 1;
    (void)firstPrinted;

    /* Percorre arestas em ordem crescente */
    for (int a = GAprimeiraAresta(g); a != 0; a = GAproximaAresta(g, a)) {
        if (!GBexisteIdAresta(g, a)) {
            continue;
        }

        int viz = GVvizinho(g, a, u); /* vizinho não-dirigido */
        if (viz == 0) {
            continue;
        }

        if (!visitado[viz]) {
            printf(", ");
            imprimeAresta(a);
            printf(", ");
            BEPdfs(g, viz, visitado, pilhaAresta);
        }
    }
}

void BEP(Grafo g, int partida)
{
    if (!validaPartida(g, partida)) {
        return;
    }

    int n = GInumeroVerticesMax(g);
    int *visitado = (int *)calloc(((size_t)n + 1U), sizeof(*visitado));
    if (visitado == NULL) {
        imprimeVertice(partida);
        printf("\n");
        return;
    }

    int *dummy = NULL;
    BEPdfs(g, partida, visitado, dummy);
    printf("\n");

    free(visitado);
}

/* -------- CMC (Dijkstra) -------- */
void CMC(Grafo g, const float *pesos, int partida, int chegada)
{
    if (g == NULL || pesos == NULL) {
        printf("v0\n");
        return;
    }

    if (!GBexisteIdVertice(g, partida) || !GBexisteIdVertice(g, chegada)) {
        imprimeVertice(partida);
        printf("\n");
        return;
    }

    if (partida == chegada) {
        imprimeVertice(partida);
        printf("\n");
        return;
    }

    int n = GInumeroVerticesMax(g);
    double *dist = (double *)malloc(((size_t)n + 1U) * sizeof(*dist));
    int *prevV = (int *)malloc(((size_t)n + 1U) * sizeof(*prevV));
    int *prevA = (int *)malloc(((size_t)n + 1U) * sizeof(*prevA));
    int *used = (int *)calloc(((size_t)n + 1U), sizeof(*used));

    if (dist == NULL || prevV == NULL || prevA == NULL || used == NULL) {
        free(dist);
        free(prevV);
        free(prevA);
        free(used);
        imprimeVertice(partida);
        printf("\n");
        return;
    }

    for (int v = 0; v <= n; ++v) {
        dist[v] = DBL_MAX;
        prevV[v] = 0;
        prevA[v] = 0;
    }
    dist[partida] = 0.0;

    for (;;) {
        int escolhido = 0;
        double menor = DBL_MAX;

        for (int v = 1; v <= n; ++v) {
            if (!used[v] && dist[v] < menor) {
                menor = dist[v];
                escolhido = v;
            }
        }

        if (escolhido == 0 || dist[escolhido] == DBL_MAX) {
            break;
        }

        used[escolhido] = 1;
        if (escolhido == chegada) {
            break;
        }

        /* relaxa arestas saindo de escolhido (direcionado) */
        for (int a = GAprimaSaida(g, escolhido); a != 0;
             a = GAproxSaida(g, escolhido, a)) {
            int w = GVomega(g, a);
            double peso = (double)pesos[a];

            if (!isfinite(peso) || peso < 0.0) {
                continue;
            }

            if (dist[escolhido] + peso < dist[w]) {
                dist[w] = dist[escolhido] + peso;
                prevV[w] = escolhido;
                prevA[w] = a;
            }
        }
    }

    if (dist[chegada] == DBL_MAX) {
        imprimeVertice(partida);
        printf("\n");
        free(dist);
        free(prevV);
        free(prevA);
        free(used);
        return;
    }

    /* reconstrói caminho */
    int maxVertices = GInumeroVerticesMax(g);
    int *caminhoV = (int *)malloc(((size_t)maxVertices + 1U) * sizeof(*caminhoV));
    int *caminhoA = (int *)malloc(((size_t)maxVertices + 1U) * sizeof(*caminhoA));
    if (caminhoV == NULL || caminhoA == NULL) {
        free(caminhoV);
        free(caminhoA);
        imprimeVertice(partida);
        printf("\n");
        free(dist);
        free(prevV);
        free(prevA);
        free(used);
        return;
    }

    int tam = 0;
    int cur = chegada;
    while (cur != 0 && cur != partida && tam <= maxVertices) {
        caminhoV[tam] = cur;
        caminhoA[tam] = prevA[cur];
        ++tam;
        cur = prevV[cur];
    }
    caminhoV[tam] = partida;
    ++tam;

    /* imprime do início ao fim */
    for (int i = tam - 1; i >= 0; --i) {
        imprimeVertice(caminhoV[i]);
        if (i > 0) {
            printf(", ");
            imprimeAresta(caminhoA[i - 1]);
            printf(", ");
        }
    }

    printf("\nDistancia: %.2f\n", dist[chegada]);

    free(caminhoV);
    free(caminhoA);
    free(dist);
    free(prevV);
    free(prevA);
    free(used);
}

/* -------- CC (componentes conexos) -------- */
void CC(Grafo g)
{
    if (g == NULL) {
        printf("{}\n");
        return;
    }

    int n = GInumeroVerticesMax(g);
    int *visitado = (int *)calloc(((size_t)n + 1U), sizeof(*visitado));
    if (visitado == NULL) {
        printf("{}\n");
        return;
    }

    int primeiroConjunto = 1;

    for (int v = 1; v <= n; ++v) {
        if (!GBexisteIdVertice(g, v) || visitado[v]) {
            continue;
        }

        if (!primeiroConjunto) {
            printf(" ");
        }
        primeiroConjunto = 0;

        printf("{");

        /* BFS/DFS simples usando fila */
        Fila f = Fcria();
        if (f == NULL) {
            printf("}\n");
            free(visitado);
            return;
        }

        Finsere(f, v);
        visitado[v] = 1;

        int primeiroDentro = 1;

        while (!Fvazia(f)) {
            int u = Fexamina(f);
            (void)Fremove(f);

            if (!primeiroDentro) {
                printf(", ");
            }
            primeiroDentro = 0;
            printf("%d", u);

            for (int a = GAprimeiraAresta(g); a != 0; a = GAproximaAresta(g, a)) {
                if (!GBexisteIdAresta(g, a)) {
                    continue;
                }
                int w = GVvizinho(g, a, u);
                if (w != 0 && !visitado[w]) {
                    visitado[w] = 1;
                    Finsere(f, w);
                }
            }
        }

        printf("}");
        Fdestroi(f);
    }

    printf("\n");
    free(visitado);
}

/* -------- AGM (placeholder) -------- */
void AGM(Grafo g, const float *pesos)
{
    if (g == NULL || pesos == NULL) {
        printf("AGM: \n");
        return;
    }

    int n = GInumeroVerticesMax(g);
    int *inAgm = (int *)calloc(((size_t)n + 1U), sizeof(*inAgm));
    int *melhorVert = (int *)calloc(((size_t)n + 1U), sizeof(*melhorVert));
    int *melhorA = (int *)calloc(((size_t)n + 1U), sizeof(*melhorA));
    double *melhorPeso = (double *)malloc(((size_t)n + 1U) * sizeof(*melhorPeso));

    if (inAgm == NULL || melhorVert == NULL || melhorA == NULL || melhorPeso == NULL) {
        free(inAgm);
        free(melhorVert);
        free(melhorA);
        free(melhorPeso);
        printf("AGM: \n");
        return;
    }

    for (int v = 0; v <= n; ++v) {
        inAgm[v] = 0;
        melhorVert[v] = 0;
        melhorA[v] = 0;
        melhorPeso[v] = DBL_MAX;
    }

    /* Escolhe um primeiro vértice ativo para iniciar (menor id). */
    int inicio = 0;
    for (int v = 1; v <= n; ++v) {
        if (GBexisteIdVertice(g, v)) {
            inicio = v;
            break;
        }
    }

    if (inicio == 0) {
        printf("AGM: \n");
        goto out;
    }

    inAgm[inicio] = 1;

    /* Inicializa candidatos: para cada aresta que conecta a árvore (não-dirigido),
       atualiza melhor custo para o outro extremo. */
    for (int a = GAprimeiraAresta(g); a != 0; a = GAproximaAresta(g, a)) {
        if (!GBexisteIdAresta(g, a)) {
            continue;
        }

        double w = (double)pesos[a];
        if (!isfinite(w)) {
            continue;
        }

        int v1 = GValfa(g, a);
        int v2 = GVomega(g, a);

        int dentro = 0;
        int fora = 0;

        if (inAgm[v1] && !inAgm[v2]) {
            dentro = 1;
            fora = v2;
        } else if (inAgm[v2] && !inAgm[v1]) {
            dentro = 1;
            fora = v1;
        }

        if (!dentro) {
            continue;
        }

        if (w < melhorPeso[fora]) {
            melhorPeso[fora] = w;
            melhorVert[fora] = (inAgm[v1] ? v1 : v2);
            melhorA[fora] = a;
        }
    }

    /* Seleciona arestas (Prim) até não haver mais crescimento. */
    int qtdA = 0;
    int *agmA = (int *)malloc(((size_t)n + 1U) * sizeof(*agmA));
    if (agmA == NULL) {
        printf("AGM: \n");
        goto out;
    }

    while (1) {
        int melhorV = 0;
        double melhorW = DBL_MAX;

        for (int v = 1; v <= n; ++v) {
            if (GBexisteIdVertice(g, v) && !inAgm[v] && melhorPeso[v] < melhorW) {
                melhorW = melhorPeso[v];
                melhorV = v;
            }
        }

        if (melhorV == 0) {
            break;
        }

        inAgm[melhorV] = 1;
        agmA[qtdA++] = melhorA[melhorV];

        /* Relaxa arestas que saem de melhorV para fora (não-dirigido). */
        for (int a = GAprimeiraAresta(g); a != 0; a = GAproximaAresta(g, a)) {
            if (!GBexisteIdAresta(g, a)) {
                continue;
            }

            int v1 = GValfa(g, a);
            int v2 = GVomega(g, a);

            int tem = 0;
            int outro = 0;

            if (inAgm[v1] && !inAgm[v2] && v1 == melhorV) {
                tem = 1;
                outro = v2;
            } else if (inAgm[v2] && !inAgm[v1] && v2 == melhorV) {
                tem = 1;
                outro = v1;
            }

            if (!tem) {
                continue;
            }

            double w = (double)pesos[a];
            if (!isfinite(w)) {
                continue;
            }

            if (w < melhorPeso[outro]) {
                melhorPeso[outro] = w;
                melhorVert[outro] = melhorV;
                melhorA[outro] = a;
            }
        }
    }

    printf("AGM:");
    for (int i = 0; i < qtdA; ++i) {
        printf(" a%d", agmA[i]);
    }
    printf("\n");

    free(agmA);

out:
    free(inAgm);
    free(melhorVert);
    free(melhorA);
    free(melhorPeso);
}
