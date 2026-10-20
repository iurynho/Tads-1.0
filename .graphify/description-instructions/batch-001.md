# Node Description Batch 2 of 2

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

- "grafo_gaproxentrada": "GAproxEntrada()" | kind=code-symbol | source=grafo.c:L665 | neighbors=[grafo.c, GbuscaNaEstrela()]
- "grafo_gaproxsaida": "GAproxSaida()" | kind=code-symbol | source=grafo.c:L675 | neighbors=[grafo.c, GbuscaNaEstrela()]
- "grafo_garestanointervalo": "GarestaNoIntervalo()" | kind=code-symbol | source=grafo.c:L57 | neighbors=[grafo.c, GBexisteIdAresta()]
- "grafo_gbarestalaco": "GBarestaLaco()" | kind=code-symbol | source=grafo.c:L680 | neighbors=[grafo.c, GBexisteIdAresta()]
- "grafo_gbexistearesta": "GBexisteAresta()" | kind=code-symbol | source=grafo.c:L383 | neighbors=[grafo.c, GApegaAresta()]
- "grafo_gbexistearestadir": "GBexisteArestaDir()" | kind=code-symbol | source=grafo.c:L378 | neighbors=[grafo.c, GApegaArestaDir()]
- "grafo_ggcriagrafo": "GGcriaGrafo()" | kind=code-symbol | source=grafo.c:L286 | neighbors=[grafo.c, GcriaGrafoInterno()]
- "grafo_ggdestroigrafo": "GGdestroiGrafo()" | kind=code-symbol | source=grafo.c:L295 | neighbors=[grafo.c, GGcarregaGrafo()]
- "grafo_ginumeroarestas": "GInumeroArestas()" | kind=code-symbol | source=grafo.c:L515 | neighbors=[grafo.c, GnumeroArestasInterno()]
- "grafo_ginumerovertices": "GInumeroVertices()" | kind=code-symbol | source=grafo.c:L505 | neighbors=[grafo.c, GnumeroVerticesInterno()]
- "grafo_glimpalista": "GlimpaLista()" | kind=code-symbol | source=grafo.c:L72 | neighbors=[grafo.c, GVcriaVertice()]
- "grafo_gvalfa": "GValfa()" | kind=code-symbol | source=grafo.c:L686 | neighbors=[grafo.c, GBexisteIdAresta()]
- "grafo_gvomega": "GVomega()" | kind=code-symbol | source=grafo.c:L691 | neighbors=[grafo.c, GBexisteIdAresta()]
- "grafo_gvprimeirovertice": "GVprimeiroVertice()" | kind=code-symbol | source=grafo.c:L429 | neighbors=[grafo.c, GBexisteIdVertice()]
- "grafo_gvproximovertice": "GVproximoVertice()" | kind=code-symbol | source=grafo.c:L446 | neighbors=[grafo.c, GBexisteIdVertice()]
- "main_teste_gravaarquivo": "gravaArquivo()" | kind=code-symbol | source=main_teste.c:L16 | neighbors=[main_teste.c, testaLimitesEArquivosInvalidos()]
- "main_teste_testafila": "testaFila()" | kind=code-symbol | source=main_teste.c:L86 | neighbors=[main_teste.c, main()]
- "main_teste_testalista": "testaLista()" | kind=code-symbol | source=main_teste.c:L104 | neighbors=[main_teste.c, main()]
- "main_teste_testapilha": "testaPilha()" | kind=code-symbol | source=main_teste.c:L68 | neighbors=[main_teste.c, main()]
- "grafo_ginumeroarestasmax": "GInumeroArestasMax()" | kind=code-symbol | source=grafo.c:L520 | neighbors=[grafo.c]
- "grafo_ginumeroverticesmax": "GInumeroVerticesMax()" | kind=code-symbol | source=grafo.c:L510 | neighbors=[grafo.c]

## Instructions

Write a single JSON object mapping each node id to a one-sentence description
to: e:\Faculdade\Tads-1.0\.graphify\description-instructions\batch-001.json

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
