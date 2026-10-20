/*
 * Arquivo: pilha.c
 * Autor(es): Iury Dias Ribeiro
 * Matricula(s): 0071470
 * Data: 19/10/2026
 */

#include "pilha.h"

#include <stdlib.h>

typedef struct noPilha {
    int valor;
    struct noPilha *proximo;
} NoPilha;

struct pilha {
    int tamanho;
    NoPilha *topo;
};

Pilha Pcria(void)
{
    Pilha pilha = (Pilha)malloc(sizeof(*pilha));

    if (pilha == NULL) {
        return NULL;
    }

    pilha->tamanho = 0;
    pilha->topo = NULL;
    return pilha;
}

void Pdestroi(Pilha pilha)
{
    NoPilha *atual;
    NoPilha *proximo;

    if (pilha == NULL) {
        return;
    }

    atual = pilha->topo;
    while (atual != NULL) {
        proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }

    free(pilha);
}

int Pvazia(Pilha pilha)
{
    return pilha == NULL || pilha->tamanho == 0;
}

int Pcheia(Pilha pilha)
{
    (void)pilha;
    return 0;
}

int Ptamanho(Pilha pilha)
{
    if (pilha == NULL) {
        return 0;
    }

    return pilha->tamanho;
}

int Pexamina(Pilha pilha)
{
    if (pilha == NULL || pilha->topo == NULL) {
        return 0;
    }

    return pilha->topo->valor;
}

void Pinsere(Pilha pilha, int elemento)
{
    NoPilha *novo;

    if (pilha == NULL) {
        return;
    }

    novo = (NoPilha *)malloc(sizeof(*novo));
    if (novo == NULL) {
        return;
    }

    novo->valor = elemento;
    novo->proximo = pilha->topo;
    pilha->topo = novo;
    ++pilha->tamanho;
}

int Premove(Pilha pilha)
{
    NoPilha *removido;
    int valor;

    if (pilha == NULL || pilha->topo == NULL) {
        return 0;
    }

    removido = pilha->topo;
    valor = removido->valor;
    pilha->topo = removido->proximo;
    free(removido);
    --pilha->tamanho;
    return valor;
}
