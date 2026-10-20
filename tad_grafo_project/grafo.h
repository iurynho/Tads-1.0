/*
 * Arquivo: grafo.h
 * Autor(es): Iury Dias Ribeiro
 * Matricula(s): 0071470
 * Data: 19/10/2026
 *
 * Interface da TAD Grafo estatico.
 */

#ifndef GRAFO_H
#define GRAFO_H

/* Estrutura opaca: os campos internos ficam definidos em grafo.c. */
typedef struct grafo *Grafo;

/* Cria um grafo vazio com capacidade maxima para v vertices e a arestas. */
Grafo GGcriaGrafo(int v, int a);

/* Libera o grafo e retorna NULL. */
Grafo GGdestroiGrafo(Grafo p);

/* Cria um vertice e retorna seu identificador; retorna 0 em caso de falha. */
int GVcriaVertice(Grafo p);

/*
 * Cria a aresta (v1,v2), permitindo lacos e arestas multiplas.
 * Retorna o identificador criado ou 0 em caso de falha.
 */
int GAcriaAresta(Grafo p, int v1, int v2);

/* Consultas de existencia. */
int GBexisteIdVertice(Grafo p, int v);
int GBexisteIdAresta(Grafo p, int a);
int GBexisteArestaDir(Grafo p, int v1, int v2);
int GBexisteAresta(Grafo p, int v1, int v2);

/*
 * Retornam o menor identificador que representa a relacao informada,
 * ou 0 quando a aresta nao existe.
 */
int GApegaArestaDir(Grafo p, int v1, int v2);
int GApegaAresta(Grafo p, int v1, int v2);

/* Percurso dos vertices ativos em ordem crescente de identificador. */
int GVprimeiroVertice(Grafo p);
int GVproximoVertice(Grafo p, int v1);

/* Percurso das arestas ativas em ordem crescente de identificador. */
int GAprimeiraAresta(Grafo p);
int GAproximaAresta(Grafo p, int a1);

/* Quantidades atuais e capacidades maximas. */
int GInumeroVertices(Grafo p);
int GInumeroVerticesMax(Grafo p);
int GInumeroArestas(Grafo p);
int GInumeroArestasMax(Grafo p);

/* Persistencia no formato textual especificado no enunciado. */
Grafo GGcarregaGrafo(const char *nomeArquivo);
int GBsalvaGrafo(Grafo p, const char *nomeArquivo);

/* Grau e percursos das estrelas de um vertice. */
int GIpegaGrau(Grafo p, int v);
int GAprimaAresta(Grafo p, int v);
int GAproxAresta(Grafo p, int v, int a1);
int GAprimaEntrada(Grafo p, int v);
int GAproxEntrada(Grafo p, int v, int a1);
int GAprimaSaida(Grafo p, int v);
int GAproxSaida(Grafo p, int v, int a1);

/* Consultas relacionadas a uma aresta. */
int GBarestaLaco(Grafo p, int a);
int GValfa(Grafo p, int a);
int GVomega(Grafo p, int a);
int GVvizinho(Grafo p, int a, int v1);

/*
 * Operacoes adicionais solicitadas.
 * Retornam 1 quando removem e 0 quando o identificador nao existe.
 * A remocao de um vertice tambem remove todas as arestas incidentes.
 */
int removeVertice(Grafo p, int v);
int removeAresta(Grafo p, int a);

#endif
