/*
 * Arquivo: lista.h
 * Autor(es): PREENCHER
 * Matricula(s): PREENCHER
 * Data: 19/10/2026
 *
 * Interface da TAD Lista dinamica duplamente encadeada.
 */

#ifndef LISTA_H
#define LISTA_H

/*
 * Os elementos armazenados nesta implementacao sao inteiros.
 * As posicoes da lista comecam em 1.
 */
typedef struct lista *Lista;

/* Cria uma lista vazia. Retorna NULL em caso de falha. */
Lista Lcria(void);

/* Destroi a lista e libera todos os seus elementos. */
void Ldestroi(Lista lista);

/* Retorna 1 se a lista estiver vazia; caso contrario, retorna 0. */
int Lvazia(Lista lista);

/*
 * Como a lista e dinamica, retorna 0 para uma lista valida.
 * A falta de memoria somente pode ser detectada durante uma insercao.
 */
int Lcheia(Lista lista);

/* Retorna a quantidade de elementos armazenados. */
int Ltamanho(Lista lista);

/*
 * Retorna o elemento da posicao informada.
 * Retorna 0 se a lista ou a posicao forem invalidas.
 */
int Lexamina(Lista lista, int posicao);

/*
 * Retorna a primeira posicao em que o elemento aparece.
 * Retorna 0 se o elemento nao estiver na lista.
 */
int Llocaliza(Lista lista, int elemento);

/*
 * Insere o elemento na posicao informada.
 * Posicoes validas: 1 ate tamanho + 1.
 * Nao altera a lista se os parametros forem invalidos ou se faltar memoria.
 */
void Linsere(Lista lista, int elemento, int posicao);

/*
 * Remove e retorna o elemento da posicao informada.
 * Retorna 0 se a lista ou a posicao forem invalidas.
 */
int Lremove(Lista lista, int posicao);

#endif
