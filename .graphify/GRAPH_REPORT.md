# Graph Report - .  (2026-10-20)

## Corpus Check
- Corpus is ~3.189 words - fits in a single context window. You may not need a graph.

## Summary
- 61 nodes · 134 edges · 9 communities detected
- Extraction: 100% EXTRACTED · 0% INFERRED · 0% AMBIGUOUS
- Token cost: 0 input · 0 output
- Edge kinds: calls: 72 · contains: 58 · imports: 4


## Input Scope
- Requested: all
- Resolved: all (source: configured-default)
- Included files: 3 · Candidates: recursive
- Excluded: 0 untracked · 0 ignored · 0 sensitive · 0 missing committed
## God Nodes (most connected - your core abstractions)
1. `GBexisteIdAresta()` - 14 edges
2. `GBexisteIdVertice()` - 12 edges
3. `GbuscaNaEstrela()` - 9 edges
4. `GAcriaAresta()` - 7 edges
5. `main()` - 7 edges
6. `GBsalvaGrafo()` - 6 edges
7. `removeAresta()` - 6 edges
8. `removeVertice()` - 6 edges
9. `Gcaminho()` - 5 edges
10. `GnumeroVerticesInterno()` - 5 edges

## Surprising Connections (you probably didn't know these)
- `GAcriaAresta()` --calls--> `GBexisteIdVertice()`  [EXTRACTED]
  grafo.c → grafo.c  _Bridges community 0 → community 6_
- `GAcriaAresta()` --calls--> `GnumeroArestasInterno()`  [EXTRACTED]
  grafo.c → grafo.c  _Bridges community 0 → community 3_
- `GApegaAresta()` --calls--> `GBexisteIdAresta()`  [EXTRACTED]
  grafo.c → grafo.c  _Bridges community 8 → community 5_
- `GApegaAresta()` --calls--> `GBexisteIdVertice()`  [EXTRACTED]
  grafo.c → grafo.c  _Bridges community 8 → community 6_
- `GApegaArestaDir()` --calls--> `GBexisteIdAresta()`  [EXTRACTED]
  grafo.c → grafo.c  _Bridges community 7 → community 5_

## Communities

### Community 0 - "Community 0"
Cohesion: 0.22
Nodes (13): GAcriaAresta(), GcriaGrafoInterno(), GdevolveArestaLivre(), GGcarregaGrafo(), GGcriaGrafo(), GGdestroiGrafo(), GinsereOrdenado(), GlimpaLista() (+5 more)

### Community 1 - "Community 1"
Cohesion: 0.36
Nodes (7): GAprimaAresta(), GAprimaEntrada(), GAprimaSaida(), GAproxAresta(), GAproxEntrada(), GAproxSaida(), GbuscaNaEstrela()

### Community 2 - "Community 2"
Cohesion: 0.40
Nodes (9): criaGrafoExemplo(), demonstraCaminho(), gravaArquivo(), main(), testaFila(), testaGrafo(), testaLimitesEArquivosInvalidos(), testaLista() (+1 more)

### Community 3 - "Community 3"
Cohesion: 0.29
Nodes (8): GAprimeiraAresta(), GAproximaAresta(), GBsalvaGrafo(), GInumeroArestas(), GInumeroVertices(), GnumeroArestasInterno(), GnumeroVerticesInterno(), GverticesContiguos()

### Community 4 - "Community 4"
Cohesion: 0.67
Nodes (5): Gcaminho(), GexecutaBellmanFord(), GexecutaDijkstra(), GimprimePartida(), GtemPesoNegativo()

### Community 5 - "Community 5"
Cohesion: 0.40
Nodes (5): GarestaNoIntervalo(), GBarestaLaco(), GBexisteIdAresta(), GValfa(), GVomega()

### Community 6 - "Community 6"
Cohesion: 0.40
Nodes (5): GBexisteIdVertice(), GIpegaGrau(), GVprimeiroVertice(), GVproximoVertice(), GVvizinho()

### Community 7 - "Community 7"
Cohesion: 1.00
Nodes (2): GApegaArestaDir(), GBexisteArestaDir()

### Community 8 - "Community 8"
Cohesion: 1.00
Nodes (2): GApegaAresta(), GBexisteAresta()

## Knowledge Gaps
- **Thin community `Community 7`** (2 nodes): `GApegaArestaDir()`, `GBexisteArestaDir()`
  Too small to be a meaningful cluster - may be noise or needs more connections extracted.
- **Thin community `Community 8`** (2 nodes): `GApegaAresta()`, `GBexisteAresta()`
  Too small to be a meaningful cluster - may be noise or needs more connections extracted.

## Suggested Questions
_Questions this graph is uniquely positioned to answer:_

- **Why does `GBexisteIdAresta()` connect `Community 5` to `Community 1`, `Community 8`, `Community 7`, `Community 3`, `Community 6`, `Community 0`?**
  _High betweenness centrality (0.020) - this node is a cross-community bridge._
- **Why does `GBexisteIdVertice()` connect `Community 6` to `Community 1`, `Community 0`, `Community 8`, `Community 7`, `Community 3`?**
  _High betweenness centrality (0.014) - this node is a cross-community bridge._