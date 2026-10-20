/*
 * Arquivo: fila.c
 * Autor(es): Iury Dias Ribeiro
 * Matricula(s): 0071470
 * Data: 19/10/2026
 */

#include "fila.h"

#include <stdlib.h>

typedef struct noFila {
    int valor;
    struct noFila *proximo;
} NoFila;

struct fila {
    int tamanho;
    NoFila *inicio;
    NoFila *fim;
};

Fila Fcria(void)
{
    Fila fila = (Fila)malloc(sizeof(*fila));

    if (fila == NULL) {
        return NULL;
    }

    fila->tamanho = 0;
    fila->inicio = NULL;
    fila->fim = NULL;
    return fila;
}

void Fdestroi(Fila fila)
{
    NoFila *atual;
    NoFila *proximo;

    if (fila == NULL) {
        return;
    }

    atual = fila->inicio;
    while (atual != NULL) {
        proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }

    free(fila);
}

int Fvazia(Fila fila)
{
    return fila == NULL || fila->tamanho == 0;
}

int Fcheia(Fila fila)
{
    (void)fila;
    return 0;
}

int Ftamanho(Fila fila)
{
    if (fila == NULL) {
        return 0;
    }

    return fila->tamanho;
}

int Fexamina(Fila fila)
{
    if (fila == NULL || fila->inicio == NULL) {
        return 0;
    }

    return fila->inicio->valor;
}

void Finsere(Fila fila, int elemento)
{
    NoFila *novo;

    if (fila == NULL) {
        return;
    }

    novo = (NoFila *)malloc(sizeof(*novo));
    if (novo == NULL) {
        return;
    }

    novo->valor = elemento;
    novo->proximo = NULL;

    if (fila->fim == NULL) {
        fila->inicio = novo;
        fila->fim = novo;
    } else {
        fila->fim->proximo = novo;
        fila->fim = novo;
    }

    ++fila->tamanho;
}

int Fremove(Fila fila)
{
    NoFila *removido;
    int valor;

    if (fila == NULL || fila->inicio == NULL) {
        return 0;
    }

    removido = fila->inicio;
    valor = removido->valor;
    fila->inicio = removido->proximo;

    if (fila->inicio == NULL) {
        fila->fim = NULL;
    }

    free(removido);
    --fila->tamanho;
    return valor;
}
