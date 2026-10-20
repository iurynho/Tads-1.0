# Testes executados

A implementação foi verificada com:

1. compilação GCC em C11 com `-Wall -Wextra -Wpedantic`;
2. compilação Clang em C11 com `-Wall -Wextra -Wpedantic -Werror`;
3. GCC Static Analyzer (`-fanalyzer`);
4. Clang Static Analyzer (`clang --analyze`);
5. AddressSanitizer e UndefinedBehaviorSanitizer;
6. testes funcionais das TADs Pilha, Fila e Lista;
7. criação, consulta, percurso, laço, arestas múltiplas, remoção e reutilização de identificadores no grafo;
8. salvamento, carregamento, arquivo sem arestas e rejeição de arquivos inválidos;
9. caminho do exemplo do enunciado e caso sem caminho;
10. teste aleatório determinístico com 10.000 operações de criação e remoção, comparando a TAD com um modelo auxiliar.

Resultado obtido nos testes principais:

```text
Caminho esperado: 3 -> 6 -> 1 -> 2
Caminho obtido:   3 -> 6 -> 1 -> 2
Sem caminho esperado: 1
Caminho obtido:       1
Todos os testes com assert foram concluidos com sucesso.
```

O teste aleatório terminou com:

```text
stress ok
```
