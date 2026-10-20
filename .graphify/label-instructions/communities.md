# Community Labeling

Graphify is running in assistant/skill mode (no API key). You are the host
assistant (Claude Code / Codex / Gemini CLI). Read the community listing below
and write 2-5 word plain-language names for each.

## Language

Write every name in English (en). Do not switch languages.

## Communities

Community 0: GAcriaAresta(, removeAresta(, removeVertice(, GcriaGrafoInterno(, GdevolveArestaLivre(, GGcarregaGrafo(, GGcriaGrafo(, GGdestroiGrafo(, GinsereOrdenado(, GlimpaLista(, GremoveDaLista(, GVcriaVertice(
Community 1: GbuscaNaEstrela(, grafo.c, GAprimaAresta(, GAprimaEntrada(, GAprimaSaida(, GAproxAresta(, GAproxEntrada(, GAproxSaida(, GInumeroArestasMax(, GInumeroVerticesMax(
Community 2: main(, main_teste.c, criaGrafoExemplo(, demonstraCaminho(, gravaArquivo(, testaFila(, testaGrafo(, testaLimitesEArquivosInvalidos(, testaLista(, testaPilha(
Community 3: GBsalvaGrafo(, GnumeroVerticesInterno(, GAprimeiraAresta(, GAproximaAresta(, GInumeroArestas(, GInumeroVertices(, GnumeroArestasInterno(, GverticesContiguos(
Community 4: Gcaminho(, caminho.c, GexecutaBellmanFord(, GexecutaDijkstra(, GimprimePartida(, GtemPesoNegativo(
Community 5: GBexisteIdAresta(, GarestaNoIntervalo(, GBarestaLaco(, GValfa(, GVomega(
Community 6: GBexisteIdVertice(, GIpegaGrau(, GVprimeiroVertice(, GVproximoVertice(, GVvizinho(
Community 7: GApegaArestaDir(, GBexisteArestaDir(
Community 8: GApegaAresta(, GBexisteAresta(

## Instructions

Write a single JSON object mapping each community id (as a string) to its
2-5 word name to: e:\Faculdade\Tads-1.0\.graphify\label-instructions\communities.json

Example:
```json
{
  "0": "Authentication Flow",
  "1": "Authentication Flow",
  "2": "Authentication Flow"
}
```

Then re-run `graphify update` (or `graphify label`) to ingest the names.
