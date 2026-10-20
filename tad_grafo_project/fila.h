/*
 * Arquivo: fila.h
 * Autor(es): PREENCHER
 * Matricula(s): PREENCHER
 * Data: 19/10/2026
 *
 * Interface da TAD Fila dinamica de inteiros.
 */

#ifndef FILA_H
#define FILA_H

typedef struct fila *Fila;

Fila Fcria(void);
void Fdestroi(Fila fila);
int Fvazia(Fila fila);
int Fcheia(Fila fila);
int Ftamanho(Fila fila);
int Fexamina(Fila fila);
void Finsere(Fila fila, int elemento);
int Fremove(Fila fila);

#endif
