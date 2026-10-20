# TAD Grafo estático e TADs básicas

Implementação em C puro das seguintes estruturas:

- TAD Grafo estático;
- módulo de caminho mínimo;
- TAD Pilha;
- TAD Fila;
- TAD Lista dinâmica duplamente encadeada;
- `removeVertice()` e `removeAresta()`.

Antes da entrega, preencha o nome e a matrícula nos cabeçalhos dos arquivos-fonte.

## Estrutura do projeto

```text
grafo.h / grafo.c       TAD Grafo
caminho.h / caminho.c   caminho de menor peso
pilha.h / pilha.c       TAD Pilha
fila.h / fila.c         TAD Fila
lista.h / lista.c       TAD Lista duplamente encadeada
tests/main_teste.c      testes funcionais e demonstração
tests/stress_grafo.c    teste aleatório do grafo
exemplos/               arquivo de grafo no formato do enunciado
```

## O que significa “grafo estático” nesta implementação

Os limites máximos de vértices e arestas são recebidos por `GGcriaGrafo(v, a)`.
Os dois vetores são alocados uma única vez e nunca são ampliados com `realloc`.
Portanto, a capacidade do grafo permanece fixa durante toda a sua vida.

A posição zero dos vetores funciona como sentinela/metadado:

- `vertices[0]` registra a quantidade de vértices ativos e mantém a lista de identificadores livres;
- `arestas[0].alfa` registra a quantidade de arestas ativas;
- `arestas[0].omega` aponta para a primeira posição livre do vetor de arestas;
- em uma posição livre de aresta, `omega` aponta para a próxima posição livre.

Cada vértice possui uma lista ordenada com os identificadores das arestas incidentes.

## Decisões de implementação

- O identificador zero significa elemento inexistente.
- Os identificadores válidos começam em 1 e podem ser usados diretamente como índices.
- Arestas múltiplas e arestas de laço são permitidas.
- Uma aresta só é criada quando os dois vértices existem.
- `removeAresta()` retorna 1 ao remover e 0 se a aresta não existir.
- `removeVertice()` também remove todas as arestas incidentes e retorna 1 ou 0.
- Identificadores liberados são reaproveitados em ordem crescente.
- Um laço contribui com 2 para o grau do vértice: uma entrada e uma saída.

## Caminho mínimo

`Gcaminho()` usa Dijkstra quando todos os pesos são não negativos. Caso exista
peso negativo, usa Bellman-Ford, evitando aplicar Dijkstra fora de sua condição
de correção. A função imprime o caminho no formato:

```text
3 -> 6 -> 1 -> 2
```

Quando não existe caminho, imprime somente o vértice de partida.
O vetor de pesos é indexado pelo identificador da aresta. Nos grafos originais,
sem remoções, o tamanho indicado pelo enunciado é `|A| + 1`. Depois de remoções,
o vetor deve possuir `GInumeroArestasMax(g) + 1` posições, pois podem existir
identificadores ativos maiores que a quantidade atual de arestas.

A alternativa de Bellman-Ford aceita pesos negativos, mas o problema de menor
caminho não fica bem definido quando existe um ciclo negativo relevante para o
destino.

## Pilha, fila e lista

As três TADs armazenam valores inteiros. A lista é dinâmica e duplamente
encadeada, conforme o modelo do enunciado. Pilha e fila também são dinâmicas,
pois as interfaces `Pcria()` e `Fcria()` não recebem uma capacidade máxima.
Consequentemente, `Pcheia()`, `Fcheia()` e `Lcheia()` retornam falso para uma
estrutura válida; uma eventual falta de memória só pode ocorrer na inserção.

As posições da lista começam em 1. Operações inválidas que deveriam retornar
um elemento retornam zero.

## Arquivos de grafo e remoção de vértices

O formato do enunciado informa somente a quantidade de vértices e depois as
arestas. Ele não possui uma lista explícita dos identificadores de vértices.
Por isso, não consegue representar um grafo com uma lacuna como `{1, 3, 4}`.

Para não salvar um arquivo que recriaria incorretamente o vértice 2,
`GBsalvaGrafo()` retorna 0 quando os vértices ativos não são exatamente
`1, 2, ..., |V|`. Depois que o identificador removido for reutilizado, o grafo
volta a poder ser salvo normalmente.

## Compilação

Com Make:

```bash
make test
make stress
make sanitize
```

Compilação manual:

```bash
gcc -std=c11 -Wall -Wextra -Wpedantic \
    lista.c pilha.c fila.c grafo.c caminho.c tests/main_teste.c \
    -I. -o teste_tads

./teste_tads
```

A TAD Grafo utiliza a TAD Lista, portanto `lista.c` deve ser incluído ao ligar
um programa que use `grafo.c`.
