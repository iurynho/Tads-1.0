/*
 * Arquivo: pilha.h
 * Autor(es): PREENCHER
 * Matricula(s): PREENCHER
 * Data: 19/10/2026
 *
 * Interface da TAD Pilha dinamica de inteiros.
 */

#ifndef PILHA_H
#define PILHA_H

typedef struct pilha *Pilha;

Pilha Pcria(void);
void Pdestroi(Pilha pilha);
int Pvazia(Pilha pilha);
int Pcheia(Pilha pilha);
int Ptamanho(Pilha pilha);
int Pexamina(Pilha pilha);
void Pinsere(Pilha pilha, int elemento);
int Premove(Pilha pilha);

#endif
