# TAD Grafo estático e TADs básicas

Implementação em C puro das seguintes estruturas:

- TAD Grafo estático
- Módulo de caminho de menor peso
- TAD Pilha
- TAD Fila
- TAD Lista dinâmica duplamente encadeada
- `removeVertice()` e `removeAresta()`

## Estrutura do projeto

```text
grafo.h / grafo.c       TAD Grafo
caminho.h / caminho.c   caminho de menor peso (grafo dirigido ponderado)
pilha.h / pilha.c       TAD Pilha
fila.h / fila.c         TAD Fila
lista.h / lista.c       TAD Lista duplamente encadeada
tests/main_teste.c      testes funcionais e demonstração
tests/stress_grafo.c   teste aleatório do grafo
exemplos/               arquivos de grafo no formato do enunciado
```

## Como testar

- `make`
- `make test`
- `make stress` (se disponível no Makefile)

## Relatório de execução

Os testes com `assert` devem terminar com sucesso e o stress deve imprimir `stress ok`.
