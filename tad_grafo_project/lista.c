/*
 * Arquivo: lista.c
 * Autor(es): Iury Dias Ribeiro
 * Matricula(s): 0071470
 * Data: 19/10/2026
 */

#include "lista.h"

#include <stddef.h>
#include <stdlib.h>

typedef struct noLista {
    int valor;
    struct noLista *anterior;
    struct noLista *proximo;
} NoLista;

struct lista {
    int tamanho;
    NoLista *inicio;
    NoLista *fim;
};

/* Retorna o no da posicao, considerando que a posicao ja foi validada. */
static NoLista *LnoNaPosicao(Lista lista, int posicao)
{
    NoLista *atual;
    int indice;

    if (posicao <= lista->tamanho / 2) {
        atual = lista->inicio;
        for (indice = 1; indice < posicao; ++indice) {
            atual = atual->proximo;
        }
    } else {
        atual = lista->fim;
        for (indice = lista->tamanho; indice > posicao; --indice) {
            atual = atual->anterior;
        }
    }

    return atual;
}

Lista Lcria(void)
{
    Lista lista = (Lista)malloc(sizeof(*lista));

    if (lista == NULL) {
        return NULL;
    }

    lista->tamanho = 0;
    lista->inicio = NULL;
    lista->fim = NULL;
    return lista;
}

void Ldestroi(Lista lista)
{
    NoLista *atual;
    NoLista *proximo;

    if (lista == NULL) {
        return;
    }

    atual = lista->inicio;
    while (atual != NULL) {
        proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }

    free(lista);
}

int Lvazia(Lista lista)
{
    return lista == NULL || lista->tamanho == 0;
}

int Lcheia(Lista lista)
{
    (void)lista;
    return 0;
}

int Ltamanho(Lista lista)
{
    if (lista == NULL) {
        return 0;
    }

    return lista->tamanho;
}

int Lexamina(Lista lista, int posicao)
{
    NoLista *no;

    if (lista == NULL || posicao < 1 || posicao > lista->tamanho) {
        return 0;
    }

    no = LnoNaPosicao(lista, posicao);
    return no->valor;
}

int Llocaliza(Lista lista, int elemento)
{
    NoLista *atual;
    int posicao = 1;

    if (lista == NULL) {
        return 0;
    }

    atual = lista->inicio;
    while (atual != NULL) {
        if (atual->valor == elemento) {
            return posicao;
        }

        atual = atual->proximo;
        ++posicao;
    }

    return 0;
}

void Linsere(Lista lista, int elemento, int posicao)
{
    NoLista *novo;

    if (lista == NULL || posicao < 1 || posicao > lista->tamanho + 1) {
        return;
    }

    novo = (NoLista *)malloc(sizeof(*novo));
    if (novo == NULL) {
        return;
    }

    novo->valor = elemento;
    novo->anterior = NULL;
    novo->proximo = NULL;

    if (lista->tamanho == 0) {
        lista->inicio = novo;
        lista->fim = novo;
    } else if (posicao == 1) {
        novo->proximo = lista->inicio;
        lista->inicio->anterior = novo;
        lista->inicio = novo;
    } else if (posicao == lista->tamanho + 1) {
        novo->anterior = lista->fim;
        lista->fim->proximo = novo;
        lista->fim = novo;
    } else {
        NoLista *atual = LnoNaPosicao(lista, posicao);

        novo->anterior = atual->anterior;
        novo->proximo = atual;
        atual->anterior->proximo = novo;
        atual->anterior = novo;
    }

    ++lista->tamanho;
}

int Lremove(Lista lista, int posicao)
{
    NoLista *removido;
    int valor;

    if (lista == NULL || posicao < 1 || posicao > lista->tamanho) {
        return 0;
    }

    removido = LnoNaPosicao(lista, posicao);
    valor = removido->valor;

    if (removido->anterior != NULL) {
        removido->anterior->proximo = removido->proximo;
    } else {
        lista->inicio = removido->proximo;
    }

    if (removido->proximo != NULL) {
        removido->proximo->anterior = removido->anterior;
    } else {
        lista->fim = removido->anterior;
    }

    free(removido);
    --lista->tamanho;
    return valor;
}
