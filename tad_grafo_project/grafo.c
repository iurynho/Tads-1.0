/*
 * Arquivo: grafo.c
 * Autor(es): Iury Dias Ribeiro
 * Matricula(s): 0071470
 * Data: 19/10/2026
 *
 * Implementacao de um grafo com capacidades fixas para vertices e arestas.
 * Os dois vetores sao alocados uma unica vez e nunca sao redimensionados.
 */

#include "grafo.h"
#include "lista.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    /* Na posicao 0, estado guarda o numero de vertices ativos. */
    int estado;

    /*
     * Na posicao 0, a lista guarda os identificadores livres.
     * Nas demais posicoes, guarda as arestas incidentes no vertice.
     */
    Lista incidencias;
} VerticeInterno;

typedef struct {
    /*
     * Em uma aresta ativa, alfa e omega sao seus extremos.
     * Na posicao 0, alfa guarda o numero de arestas ativas e omega
     * guarda o primeiro identificador livre.
     * Em uma posicao livre, alfa vale 0 e omega aponta a proxima livre.
     */
    int alfa;
    int omega;
} ArestaInterna;

struct grafo {
    int maxVertices;
    int maxArestas;
    VerticeInterno *vertices;
    ArestaInterna *arestas;
};

enum {
    ESTRELA_TODAS = 0,
    ESTRELA_ENTRADA = 1,
    ESTRELA_SAIDA = 2
};

static int GverticeNoIntervalo(Grafo p, int v)
{
    return p != NULL && v >= 1 && v <= p->maxVertices;
}

static int GarestaNoIntervalo(Grafo p, int a)
{
    return p != NULL && a >= 1 && a <= p->maxArestas;
}

static int GnumeroVerticesInterno(Grafo p)
{
    return p->vertices[0].estado;
}

static int GnumeroArestasInterno(Grafo p)
{
    return p->arestas[0].alfa;
}

static void GlimpaLista(Lista lista)
{
    while (!Lvazia(lista)) {
        (void)Lremove(lista, 1);
    }
}

/* Insere um inteiro em ordem crescente e informa se conseguiu. */
static int GinsereOrdenado(Lista lista, int valor)
{
    int tamanho;
    int posicao;

    if (lista == NULL || valor <= 0) {
        return 0;
    }

    tamanho = Ltamanho(lista);
    posicao = 1;

    while (posicao <= tamanho && Lexamina(lista, posicao) < valor) {
        ++posicao;
    }

    if (posicao <= tamanho && Lexamina(lista, posicao) == valor) {
        return 1;
    }

    Linsere(lista, valor, posicao);
    return Ltamanho(lista) == tamanho + 1;
}

static int GremoveDaLista(Lista lista, int valor)
{
    int posicao;

    if (lista == NULL) {
        return 0;
    }

    posicao = Llocaliza(lista, valor);
    if (posicao == 0) {
        return 0;
    }

    (void)Lremove(lista, posicao);
    return 1;
}

/*
 * Recoloca uma aresta na cadeia de identificadores livres, em ordem
 * crescente. A propria posicao livre usa omega como elo da cadeia.
 */
static void GdevolveArestaLivre(Grafo p, int a)
{
    int anterior = 0;
    int atual = p->arestas[0].omega;

    while (atual != 0 && atual < a) {
        anterior = atual;
        atual = p->arestas[atual].omega;
    }

    p->arestas[a].alfa = 0;
    p->arestas[a].omega = atual;

    if (anterior == 0) {
        p->arestas[0].omega = a;
    } else {
        p->arestas[anterior].omega = a;
    }
}

/*
 * Busca o menor identificador maior que "depoisDe" na estrela solicitada.
 * As listas de incidencia permanecem ordenadas por identificador de aresta.
 */
static int GbuscaNaEstrela(Grafo p, int v, int depoisDe, int tipo)
{
    Lista incidencias;
    int tamanho;
    int posicao;

    if (!GBexisteIdVertice(p, v)) {
        return 0;
    }

    incidencias = p->vertices[v].incidencias;
    tamanho = Ltamanho(incidencias);

    for (posicao = 1; posicao <= tamanho; ++posicao) {
        int a = Lexamina(incidencias, posicao);

        if (a <= depoisDe || !GBexisteIdAresta(p, a)) {
            continue;
        }

        if (tipo == ESTRELA_TODAS
            || (tipo == ESTRELA_ENTRADA && p->arestas[a].omega == v)
            || (tipo == ESTRELA_SAIDA && p->arestas[a].alfa == v)) {
            return a;
        }
    }

    return 0;
}

/* O formato de arquivo original representa vertices 1, 2, ..., |V|. */
static int GverticesContiguos(Grafo p)
{
    int v;
    int numeroVertices;

    if (p == NULL) {
        return 0;
    }

    numeroVertices = GnumeroVerticesInterno(p);
    if (numeroVertices <= 0) {
        return 0;
    }

    for (v = 1; v <= numeroVertices; ++v) {
        if (!GBexisteIdVertice(p, v)) {
            return 0;
        }
    }

    for (v = numeroVertices + 1; v <= p->maxVertices; ++v) {
        if (GBexisteIdVertice(p, v)) {
            return 0;
        }
    }

    return 1;
}

static Grafo GcriaGrafoInterno(int v, int a)
{
    Grafo p;
    int i;

    if (v <= 0 || a < 0) {
        return NULL;
    }

    p = (Grafo)calloc(1U, sizeof(*p));
    if (p == NULL) {
        return NULL;
    }

    p->vertices = (VerticeInterno *)calloc((size_t)v + 1U,
                                           sizeof(*p->vertices));
    p->arestas = (ArestaInterna *)calloc((size_t)a + 1U,
                                         sizeof(*p->arestas));

    if (p->vertices == NULL || p->arestas == NULL) {
        free(p->arestas);
        free(p->vertices);
        free(p);
        return NULL;
    }

    p->maxVertices = v;
    p->maxArestas = a;

    /* Cria a lista de livres da posicao 0 e uma estrela para cada vertice. */
    for (i = 0; i <= v; ++i) {
        p->vertices[i].estado = 0;
        p->vertices[i].incidencias = Lcria();

        if (p->vertices[i].incidencias == NULL) {
            int j;

            for (j = 0; j < i; ++j) {
                Ldestroi(p->vertices[j].incidencias);
            }

            free(p->arestas);
            free(p->vertices);
            free(p);
            return NULL;
        }
    }

    /* Inicialmente todos os identificadores de vertice estao livres. */
    for (i = 1; i <= v; ++i) {
        if (!GinsereOrdenado(p->vertices[0].incidencias, i)) {
            int j;

            for (j = 0; j <= v; ++j) {
                Ldestroi(p->vertices[j].incidencias);
            }

            free(p->arestas);
            free(p->vertices);
            free(p);
            return NULL;
        }
    }

    /* A posicao 0 e a sentinela do vetor de arestas. */
    p->arestas[0].alfa = 0;
    p->arestas[0].omega = (a > 0) ? 1 : 0;

    /* Encadeia todas as posicoes livres usando o campo omega. */
    for (i = 1; i <= a; ++i) {
        p->arestas[i].alfa = 0;
        p->arestas[i].omega = (i < a) ? i + 1 : 0;
    }

    return p;
}

Grafo GGcriaGrafo(int v, int a)
{
    if (v <= 0 || a <= 0) {
        return NULL;
    }

    return GcriaGrafoInterno(v, a);
}

Grafo GGdestroiGrafo(Grafo p)
{
    int v;

    if (p == NULL) {
        return NULL;
    }

    for (v = 0; v <= p->maxVertices; ++v) {
        Ldestroi(p->vertices[v].incidencias);
    }

    free(p->arestas);
    free(p->vertices);
    free(p);
    return NULL;
}

int GVcriaVertice(Grafo p)
{
    int v;

    if (p == NULL
        || GnumeroVerticesInterno(p) >= p->maxVertices
        || Lvazia(p->vertices[0].incidencias)) {
        return 0;
    }

    /* A lista e ordenada, portanto o primeiro e o menor id livre. */
    v = Lremove(p->vertices[0].incidencias, 1);
    if (!GverticeNoIntervalo(p, v)) {
        return 0;
    }

    p->vertices[v].estado = 1;
    GlimpaLista(p->vertices[v].incidencias);
    ++p->vertices[0].estado;
    return v;
}

int GAcriaAresta(Grafo p, int v1, int v2)
{
    int a;

    if (p == NULL
        || GnumeroArestasInterno(p) >= p->maxArestas
        || p->arestas[0].omega == 0
        || !GBexisteIdVertice(p, v1)
        || !GBexisteIdVertice(p, v2)) {
        return 0;
    }

    a = p->arestas[0].omega;
    p->arestas[0].omega = p->arestas[a].omega;

    p->arestas[a].alfa = v1;
    p->arestas[a].omega = v2;

    if (!GinsereOrdenado(p->vertices[v1].incidencias, a)) {
        GdevolveArestaLivre(p, a);
        return 0;
    }

    if (v2 != v1 && !GinsereOrdenado(p->vertices[v2].incidencias, a)) {
        (void)GremoveDaLista(p->vertices[v1].incidencias, a);
        GdevolveArestaLivre(p, a);
        return 0;
    }

    ++p->arestas[0].alfa;
    return a;
}

int GBexisteIdVertice(Grafo p, int v)
{
    return GverticeNoIntervalo(p, v) && p->vertices[v].estado == 1;
}

int GBexisteIdAresta(Grafo p, int a)
{
    return GarestaNoIntervalo(p, a) && p->arestas[a].alfa != 0;
}

int GBexisteArestaDir(Grafo p, int v1, int v2)
{
    return GApegaArestaDir(p, v1, v2) != 0;
}

int GBexisteAresta(Grafo p, int v1, int v2)
{
    return GApegaAresta(p, v1, v2) != 0;
}

int GApegaArestaDir(Grafo p, int v1, int v2)
{
    int a;

    if (!GBexisteIdVertice(p, v1) || !GBexisteIdVertice(p, v2)) {
        return 0;
    }

    for (a = 1; a <= p->maxArestas; ++a) {
        if (GBexisteIdAresta(p, a)
            && p->arestas[a].alfa == v1
            && p->arestas[a].omega == v2) {
            return a;
        }
    }

    return 0;
}

int GApegaAresta(Grafo p, int v1, int v2)
{
    int a;

    if (!GBexisteIdVertice(p, v1) || !GBexisteIdVertice(p, v2)) {
        return 0;
    }

    for (a = 1; a <= p->maxArestas; ++a) {
        if (!GBexisteIdAresta(p, a)) {
            continue;
        }

        if ((p->arestas[a].alfa == v1 && p->arestas[a].omega == v2)
            || (p->arestas[a].alfa == v2 && p->arestas[a].omega == v1)) {
            return a;
        }
    }

    return 0;
}

int GVprimeiroVertice(Grafo p)
{
    int v;

    if (p == NULL) {
        return 0;
    }

    for (v = 1; v <= p->maxVertices; ++v) {
        if (GBexisteIdVertice(p, v)) {
            return v;
        }
    }

    return 0;
}

int GVproximoVertice(Grafo p, int v1)
{
    int v;

    if (p == NULL) {
        return 0;
    }

    if (v1 < 0) {
        v1 = 0;
    }

    for (v = v1 + 1; v <= p->maxVertices; ++v) {
        if (GBexisteIdVertice(p, v)) {
            return v;
        }
    }

    return 0;
}

int GAprimeiraAresta(Grafo p)
{
    int a;

    if (p == NULL) {
        return 0;
    }

    for (a = 1; a <= p->maxArestas; ++a) {
        if (GBexisteIdAresta(p, a)) {
            return a;
        }
    }

    return 0;
}

int GAproximaAresta(Grafo p, int a1)
{
    int a;

    if (p == NULL) {
        return 0;
    }

    if (a1 < 0) {
        a1 = 0;
    }

    for (a = a1 + 1; a <= p->maxArestas; ++a) {
        if (GBexisteIdAresta(p, a)) {
            return a;
        }
    }

    return 0;
}

int GInumeroVertices(Grafo p)
{
    return p == NULL ? 0 : GnumeroVerticesInterno(p);
}

int GInumeroVerticesMax(Grafo p)
{
    return p == NULL ? 0 : p->maxVertices;
}

int GInumeroArestas(Grafo p)
{
    return p == NULL ? 0 : GnumeroArestasInterno(p);
}

int GInumeroArestasMax(Grafo p)
{
    return p == NULL ? 0 : p->maxArestas;
}

Grafo GGcarregaGrafo(const char *nomeArquivo)
{
    FILE *arquivo;
    Grafo p;
    int numeroVertices;
    int numeroArestas;
    int i;

    if (nomeArquivo == NULL) {
        return NULL;
    }

    arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        return NULL;
    }

    if (fscanf(arquivo, "%d %d", &numeroVertices, &numeroArestas) != 2
        || numeroVertices <= 0 || numeroArestas < 0) {
        fclose(arquivo);
        return NULL;
    }

    p = GcriaGrafoInterno(numeroVertices, numeroArestas);
    if (p == NULL) {
        fclose(arquivo);
        return NULL;
    }

    for (i = 0; i < numeroVertices; ++i) {
        if (GVcriaVertice(p) == 0) {
            (void)GGdestroiGrafo(p);
            fclose(arquivo);
            return NULL;
        }
    }

    for (i = 0; i < numeroArestas; ++i) {
        int alfa;
        int omega;

        if (fscanf(arquivo, "%d %d", &alfa, &omega) != 2
            || GAcriaAresta(p, alfa, omega) == 0) {
            (void)GGdestroiGrafo(p);
            fclose(arquivo);
            return NULL;
        }
    }

    if (fclose(arquivo) != 0) {
        (void)GGdestroiGrafo(p);
        return NULL;
    }

    return p;
}

int GBsalvaGrafo(Grafo p, const char *nomeArquivo)
{
    FILE *arquivo;
    int a;
    int sucesso = 1;

    if (p == NULL || nomeArquivo == NULL || !GverticesContiguos(p)) {
        return 0;
    }

    arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL) {
        return 0;
    }

    if (fprintf(arquivo, "%d %d\n", GnumeroVerticesInterno(p),
                GnumeroArestasInterno(p)) < 0) {
        sucesso = 0;
    }

    for (a = GAprimeiraAresta(p); sucesso && a != 0;
         a = GAproximaAresta(p, a)) {
        if (fprintf(arquivo, "%d %d\n", p->arestas[a].alfa,
                    p->arestas[a].omega) < 0) {
            sucesso = 0;
        }
    }

    if (fclose(arquivo) != 0) {
        sucesso = 0;
    }

    return sucesso;
}

int GIpegaGrau(Grafo p, int v)
{
    Lista incidencias;
    int tamanho;
    int posicao;
    int grau = 0;

    if (!GBexisteIdVertice(p, v)) {
        return 0;
    }

    incidencias = p->vertices[v].incidencias;
    tamanho = Ltamanho(incidencias);

    for (posicao = 1; posicao <= tamanho; ++posicao) {
        int a = Lexamina(incidencias, posicao);

        if (!GBexisteIdAresta(p, a)) {
            continue;
        }

        if (p->arestas[a].alfa == v) {
            ++grau;
        }

        if (p->arestas[a].omega == v) {
            ++grau;
        }
    }

    return grau;
}

int GAprimaAresta(Grafo p, int v)
{
    return GbuscaNaEstrela(p, v, 0, ESTRELA_TODAS);
}

int GAproxAresta(Grafo p, int v, int a1)
{
    return GbuscaNaEstrela(p, v, a1, ESTRELA_TODAS);
}

int GAprimaEntrada(Grafo p, int v)
{
    return GbuscaNaEstrela(p, v, 0, ESTRELA_ENTRADA);
}

int GAproxEntrada(Grafo p, int v, int a1)
{
    return GbuscaNaEstrela(p, v, a1, ESTRELA_ENTRADA);
}

int GAprimaSaida(Grafo p, int v)
{
    return GbuscaNaEstrela(p, v, 0, ESTRELA_SAIDA);
}

int GAproxSaida(Grafo p, int v, int a1)
{
    return GbuscaNaEstrela(p, v, a1, ESTRELA_SAIDA);
}

int GBarestaLaco(Grafo p, int a)
{
    return GBexisteIdAresta(p, a)
        && p->arestas[a].alfa == p->arestas[a].omega;
}

int GValfa(Grafo p, int a)
{
    return GBexisteIdAresta(p, a) ? p->arestas[a].alfa : 0;
}

int GVomega(Grafo p, int a)
{
    return GBexisteIdAresta(p, a) ? p->arestas[a].omega : 0;
}

int GVvizinho(Grafo p, int a, int v1)
{
    if (!GBexisteIdAresta(p, a) || !GBexisteIdVertice(p, v1)) {
        return 0;
    }

    if (p->arestas[a].alfa == v1) {
        return p->arestas[a].omega;
    }

    if (p->arestas[a].omega == v1) {
        return p->arestas[a].alfa;
    }

    return 0;
}

int removeAresta(Grafo p, int a)
{
    int alfa;
    int omega;

    if (!GBexisteIdAresta(p, a)) {
        return 0;
    }

    alfa = p->arestas[a].alfa;
    omega = p->arestas[a].omega;

    if (GverticeNoIntervalo(p, alfa)) {
        (void)GremoveDaLista(p->vertices[alfa].incidencias, a);
    }

    if (omega != alfa && GverticeNoIntervalo(p, omega)) {
        (void)GremoveDaLista(p->vertices[omega].incidencias, a);
    }

    --p->arestas[0].alfa;
    GdevolveArestaLivre(p, a);
    return 1;
}

int removeVertice(Grafo p, int v)
{
    Lista incidencias;

    if (!GBexisteIdVertice(p, v)) {
        return 0;
    }

    /* Reserva primeiro a reinsercao do id na lista livre. */
    if (!GinsereOrdenado(p->vertices[0].incidencias, v)) {
        return 0;
    }

    incidencias = p->vertices[v].incidencias;

    while (!Lvazia(incidencias)) {
        int a = Lexamina(incidencias, 1);

        if (!GBexisteIdAresta(p, a)) {
            (void)Lremove(incidencias, 1);
        } else if (!removeAresta(p, a)) {
            (void)GremoveDaLista(p->vertices[0].incidencias, v);
            return 0;
        }
    }

    p->vertices[v].estado = 0;
    --p->vertices[0].estado;
    return 1;
}
