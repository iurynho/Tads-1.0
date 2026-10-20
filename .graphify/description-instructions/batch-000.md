# Node Description Batch 1 of 2

Graphify is running in assistant/skill mode (no API key). You are the host
assistant (Claude Code / Codex / Gemini CLI). Read the prompt below and write
your JSON answer to the answer file.

## Prompt

You are documenting nodes in a knowledge graph.
For each entry below, write ONE concise factual plain-language sentence
describing what it is or does. Use only the provided context.
For a code symbol (kind=code-symbol — a function, class, or constant),
describe what the function/symbol does based on its name, source location
and neighbors — e.g. "Resolves the configured ontology profile from graphify.yaml.".
Write every description in English (en). Do not switch languages.
No marketing language.
Respond ONLY with a JSON object mapping each node id (as a string) to its
one-sentence description — no prose, no markdown fences.

- "grafo": "grafo.c" | kind=code-symbol | source=grafo.c:L1 | neighbors=[grafo.c, GAcriaAresta(), GApegaAresta(), GApegaArestaDir(), GAprimaAresta(), GAprimaEntrada()]
- "grafo_gbexisteidaresta": "GBexisteIdAresta()" | kind=code-symbol | source=grafo.c:L373 | neighbors=[grafo.c, GApegaAresta(), GApegaArestaDir(), GAprimeiraAresta(), GAproximaAresta(), GBarestaLaco()]
- "grafo_gbexisteidvertice": "GBexisteIdVertice()" | kind=code-symbol | source=grafo.c:L368 | neighbors=[grafo.c, GAcriaAresta(), GApegaAresta(), GApegaArestaDir(), GverticeNoIntervalo(), GbuscaNaEstrela()]
- "main_teste": "main_teste.c" | kind=code-symbol | source=main_teste.c:L1 | neighbors=[caminho.c, grafo.c, criaGrafoExemplo(), demonstraCaminho(), gravaArquivo(), main()]
- "grafo_gbuscanaestrela": "GbuscaNaEstrela()" | kind=code-symbol | source=grafo.c:L149 | neighbors=[grafo.c, GAprimaAresta(), GAprimaEntrada(), GAprimaSaida(), GAproxAresta(), GAproxEntrada()]
- "caminho": "caminho.c" | kind=code-symbol | source=caminho.c:L1 | neighbors=[caminho.c, Gcaminho(), GexecutaBellmanFord(), GexecutaDijkstra(), GimprimePartida(), GtemPesoNegativo()]
- "grafo_gacriaaresta": "GAcriaAresta()" | kind=code-symbol | source=grafo.c:L335 | neighbors=[grafo.c, GBexisteIdVertice(), GdevolveArestaLivre(), GinsereOrdenado(), GnumeroArestasInterno(), GremoveDaLista()]
- "main_teste_main": "main()" | kind=code-symbol | source=main_teste.c:L231 | neighbors=[main_teste.c, demonstraCaminho(), testaFila(), testaGrafo(), testaLimitesEArquivosInvalidos(), testaLista()]
- "grafo_gbsalvagrafo": "GBsalvaGrafo()" | kind=code-symbol | source=grafo.c:L582 | neighbors=[grafo.c, GAprimeiraAresta(), GAproximaAresta(), GnumeroArestasInterno(), GnumeroVerticesInterno(), GverticesContiguos()]
- "grafo_removearesta": "removeAresta()" | kind=code-symbol | source=grafo.c:L713 | neighbors=[grafo.c, GBexisteIdAresta(), GdevolveArestaLivre(), GremoveDaLista(), GverticeNoIntervalo(), removeVertice()]
- "grafo_removevertice": "removeVertice()" | kind=code-symbol | source=grafo.c:L738 | neighbors=[grafo.c, GBexisteIdAresta(), GBexisteIdVertice(), GinsereOrdenado(), GremoveDaLista(), removeAresta()]
- "caminho_gcaminho": "Gcaminho()" | kind=code-symbol | source=caminho.c:L126 | neighbors=[caminho.c, GexecutaBellmanFord(), GexecutaDijkstra(), GimprimePartida(), GtemPesoNegativo()]
- "grafo_ggcarregagrafo": "GGcarregaGrafo()" | kind=code-symbol | source=grafo.c:L525 | neighbors=[grafo.c, GAcriaAresta(), GcriaGrafoInterno(), GGdestroiGrafo(), GVcriaVertice()]
- "grafo_gnumeroverticesinterno": "GnumeroVerticesInterno()" | kind=code-symbol | source=grafo.c:L62 | neighbors=[grafo.c, GBsalvaGrafo(), GInumeroVertices(), GVcriaVertice(), GverticesContiguos()]
- "grafo_gvcriavertice": "GVcriaVertice()" | kind=code-symbol | source=grafo.c:L313 | neighbors=[grafo.c, GGcarregaGrafo(), GlimpaLista(), GnumeroVerticesInterno(), GverticeNoIntervalo()]
- "grafo_gapegaaresta": "GApegaAresta()" | kind=code-symbol | source=grafo.c:L407 | neighbors=[grafo.c, GBexisteIdAresta(), GBexisteIdVertice(), GBexisteAresta()]
- "grafo_gapegaarestadir": "GApegaArestaDir()" | kind=code-symbol | source=grafo.c:L388 | neighbors=[grafo.c, GBexisteIdAresta(), GBexisteIdVertice(), GBexisteArestaDir()]
- "grafo_gcriagrafointerno": "GcriaGrafoInterno()" | kind=code-symbol | source=grafo.c:L209 | neighbors=[grafo.c, GinsereOrdenado(), GGcarregaGrafo(), GGcriaGrafo()]
- "grafo_ginsereordenado": "GinsereOrdenado()" | kind=code-symbol | source=grafo.c:L80 | neighbors=[grafo.c, GAcriaAresta(), GcriaGrafoInterno(), removeVertice()]
- "grafo_gnumeroarestasinterno": "GnumeroArestasInterno()" | kind=code-symbol | source=grafo.c:L67 | neighbors=[grafo.c, GAcriaAresta(), GBsalvaGrafo(), GInumeroArestas()]
- "grafo_gremovedalista": "GremoveDaLista()" | kind=code-symbol | source=grafo.c:L104 | neighbors=[grafo.c, GAcriaAresta(), removeAresta(), removeVertice()]
- "grafo_gverticenointervalo": "GverticeNoIntervalo()" | kind=code-symbol | source=grafo.c:L52 | neighbors=[grafo.c, GBexisteIdVertice(), GVcriaVertice(), removeAresta()]
- "grafo_gverticescontiguos": "GverticesContiguos()" | kind=code-symbol | source=grafo.c:L180 | neighbors=[grafo.c, GBsalvaGrafo(), GBexisteIdVertice(), GnumeroVerticesInterno()]
- "grafo_gaprimeiraaresta": "GAprimeiraAresta()" | kind=code-symbol | source=grafo.c:L467 | neighbors=[grafo.c, GBexisteIdAresta(), GBsalvaGrafo()]
- "grafo_gaproximaaresta": "GAproximaAresta()" | kind=code-symbol | source=grafo.c:L484 | neighbors=[grafo.c, GBexisteIdAresta(), GBsalvaGrafo()]
- "grafo_gdevolvearestalivre": "GdevolveArestaLivre()" | kind=code-symbol | source=grafo.c:L125 | neighbors=[grafo.c, GAcriaAresta(), removeAresta()]
- "grafo_gipegagrau": "GIpegaGrau()" | kind=code-symbol | source=grafo.c:L617 | neighbors=[grafo.c, GBexisteIdAresta(), GBexisteIdVertice()]
- "grafo_gvvizinho": "GVvizinho()" | kind=code-symbol | source=grafo.c:L696 | neighbors=[grafo.c, GBexisteIdAresta(), GBexisteIdVertice()]
- "main_teste_criagrafoexemplo": "criaGrafoExemplo()" | kind=code-symbol | source=main_teste.c:L123 | neighbors=[main_teste.c, demonstraCaminho(), testaGrafo()]
- "main_teste_demonstracaminho": "demonstraCaminho()" | kind=code-symbol | source=main_teste.c:L214 | neighbors=[main_teste.c, criaGrafoExemplo(), main()]
- "main_teste_testagrafo": "testaGrafo()" | kind=code-symbol | source=main_teste.c:L145 | neighbors=[main_teste.c, main(), criaGrafoExemplo()]
- "main_teste_testalimitesearquivosinvalidos": "testaLimitesEArquivosInvalidos()" | kind=code-symbol | source=main_teste.c:L25 | neighbors=[main_teste.c, main(), gravaArquivo()]
- "caminho_gexecutabellmanford": "GexecutaBellmanFord()" | kind=code-symbol | source=caminho.c:L92 | neighbors=[caminho.c, Gcaminho()]
- "caminho_gexecutadijkstra": "GexecutaDijkstra()" | kind=code-symbol | source=caminho.c:L40 | neighbors=[caminho.c, Gcaminho()]
- "caminho_gimprimepartida": "GimprimePartida()" | kind=code-symbol | source=caminho.c:L19 | neighbors=[caminho.c, Gcaminho()]
- "caminho_gtempesonegativo": "GtemPesoNegativo()" | kind=code-symbol | source=caminho.c:L24 | neighbors=[caminho.c, Gcaminho()]
- "grafo_gaprimaaresta": "GAprimaAresta()" | kind=code-symbol | source=grafo.c:L650 | neighbors=[grafo.c, GbuscaNaEstrela()]
- "grafo_gaprimaentrada": "GAprimaEntrada()" | kind=code-symbol | source=grafo.c:L660 | neighbors=[grafo.c, GbuscaNaEstrela()]
- "grafo_gaprimasaida": "GAprimaSaida()" | kind=code-symbol | source=grafo.c:L670 | neighbors=[grafo.c, GbuscaNaEstrela()]
- "grafo_gaproxaresta": "GAproxAresta()" | kind=code-symbol | source=grafo.c:L655 | neighbors=[grafo.c, GbuscaNaEstrela()]

## Instructions

Write a single JSON object mapping each node id to a one-sentence description
to: e:\Faculdade\Tads-1.0\.graphify\description-instructions\batch-000.json

Keep each description factual and concise (one sentence). No markdown, no prose
outside the JSON object. It is acceptable to omit a node if context is
insufficient — but include every node you can ground confidently.

Example answer format:
```json
{
  "node_id_1": "Resolves the configured ontology profile from graphify.yaml.",
  "node_id_2": "Colonel James Barclay, an antagonist in The Crooked Man."
}
```
