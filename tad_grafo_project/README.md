# TAD Grafo estático, módulo de caminho e algoritmos em grafos

Este projeto implementa, em C puro, uma TAD de Grafo estático (TPs anteriores) e um programa de **algoritmos em grafos** (TP atual).

## Estrutura do projeto

```text
grafo.h / grafo.c       TAD Grafo (estático)
caminho.h / caminho.c   Caminho de menor peso (grafo dirigido ponderado)
pilha.h / pilha.c       TAD Pilha
fila.h / fila.c         TAD Fila
lista.h / lista.c       TAD Lista duplamente encadeada
algoritmos.h / algoritmos.c  Algoritmos pedidos (AGM/BEL/BEP/CMC/CC)
main_algoritmos.c       Programa de menu e leitura (stdin/arquivo)
tests/                  testes funcionais e stress
exemplos/              arquivos de grafo no formato do enunciado
```

## Parte 2 — Objetivo

Desenvolver algoritmos em grafos representados com a TAD `Grafo`, com:
- **Entrada e saída em modo texto**
- **Opção para ler o grafo via arquivo**
- **Uso das operações da TAD**

## Algoritmos implementados

1. **Árvore Geradora Mínima (AGM)**  
2. **Busca em Largura (BEL)**  
3. **Busca em Profundidade (BEP)**  
4. **Caminho mais curto (CMC)**  
5. **Componentes conexos (CC)**  

> Nota: AGM/CC são tratados como **não-dirigidos** na forma como a vizinhança é considerada.

## Como testar (programa de algoritmos)

### Compilar
No Windows/MinGW/MSYS2, compile gerando `algoritmos.exe`:
```sh
gcc -std=c11 -Wall -Wextra -Wpedantic -O2 main_algoritmos.c algoritmos.c lista.c pilha.c fila.c grafo.c caminho.c -I. -o algoritmos.exe
```

### Executar
```sh
./algoritmos.exe
```

### Entrada via stdin
1) Opção `1`  
2) Informe `V A`  
3) Para cada aresta i=1..A informe: `alfa omega`  
4) Em seguida, informe os **pesos**:
   - o programa pede `Peso da aresta a1`, depois `a2`, ..., até `aA`
   - isto é: **`pesos[i]` é o peso da aresta de id `a<i>`** (IDs conforme a ordem de inserção/arquivo)

### Entrada via arquivo
1) Opção `2`  
2) Informe o caminho do arquivo (ex.: `exemplos/grafo_exemplo.txt`)  
3) Em seguida, o programa pede os pesos das arestas `a1..aA` na mesma ordem em que o arquivo lista as arestas.

### Menu de algoritmos
Escolha:
- `1) AGM`
- `2) BEL`
- `3) BEP`
- `4) CMC`
- `5) CC`
- `0) Voltar / Repetir menu de entrada`

## Testes automáticos das TADs
Consulte `TESTES.md`. O teste principal usa `assert` e o stress valida comportamento aleatório.
