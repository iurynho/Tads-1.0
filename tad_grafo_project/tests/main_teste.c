/*
 * Arquivo: main_teste.c
 * Programa de demonstracao e testes das TADs.
 */

#include "caminho.h"
#include "fila.h"
#include "grafo.h"
#include "lista.h"
#include "pilha.h"

#include <assert.h>
#include <stdio.h>


static void gravaArquivo(const char *nome, const char *conteudo)
{
    FILE *arquivo = fopen(nome, "w");

    assert(arquivo != NULL);
    assert(fputs(conteudo, arquivo) >= 0);
    assert(fclose(arquivo) == 0);
}

static void testaLimitesEArquivosInvalidos(void)
{
    Grafo g;

    assert(GGcriaGrafo(0, 1) == NULL);
    assert(GGcriaGrafo(1, 0) == NULL);
    assert(GGcarregaGrafo("arquivo_que_nao_existe.txt") == NULL);

    g = GGcriaGrafo(2, 1);
    assert(g != NULL);
    assert(GVcriaVertice(g) == 1);
    assert(GVcriaVertice(g) == 2);
    assert(GVcriaVertice(g) == 0);
    assert(GAcriaAresta(g, 1, 2) == 1);
    assert(GAcriaAresta(g, 1, 2) == 0);
    assert(GAcriaAresta(g, 1, 3) == 0);
    assert(removeAresta(g, 2) == 0);
    assert(removeVertice(g, 3) == 0);
    g = GGdestroiGrafo(g);

    gravaArquivo("arquivo_invalido_1.txt", "texto invalido\n");
    assert(GGcarregaGrafo("arquivo_invalido_1.txt") == NULL);

    gravaArquivo("arquivo_invalido_2.txt", "3 2\n1 2\n");
    assert(GGcarregaGrafo("arquivo_invalido_2.txt") == NULL);

    gravaArquivo("arquivo_invalido_3.txt", "3 1\n1 4\n");
    assert(GGcarregaGrafo("arquivo_invalido_3.txt") == NULL);

    gravaArquivo("grafo_sem_arestas.txt", "3 0\n");
    g = GGcarregaGrafo("grafo_sem_arestas.txt");
    assert(g != NULL);
    assert(GInumeroVertices(g) == 3);
    assert(GInumeroArestas(g) == 0);
    assert(GInumeroArestasMax(g) == 0);
    g = GGdestroiGrafo(g);

    (void)remove("arquivo_invalido_1.txt");
    (void)remove("arquivo_invalido_2.txt");
    (void)remove("arquivo_invalido_3.txt");
    (void)remove("grafo_sem_arestas.txt");
}

static void testaPilha(void)
{
    Pilha p = Pcria();

    assert(p != NULL);
    assert(Pvazia(p));
    Pinsere(p, 6);
    Pinsere(p, 5);
    Pinsere(p, 7);
    assert(Ptamanho(p) == 3);
    assert(Pexamina(p) == 7);
    assert(Premove(p) == 7);
    assert(Premove(p) == 5);
    assert(Premove(p) == 6);
    assert(Premove(p) == 0);
    Pdestroi(p);
}

static void testaFila(void)
{
    Fila f = Fcria();

    assert(f != NULL);
    assert(Fvazia(f));
    Finsere(f, 6);
    Finsere(f, 5);
    Finsere(f, 7);
    assert(Ftamanho(f) == 3);
    assert(Fexamina(f) == 6);
    assert(Fremove(f) == 6);
    assert(Fremove(f) == 5);
    assert(Fremove(f) == 7);
    assert(Fremove(f) == 0);
    Fdestroi(f);
}

static void testaLista(void)
{
    Lista l = Lcria();

    assert(l != NULL);
    assert(Lvazia(l));
    Linsere(l, 10, 1);
    Linsere(l, 30, 2);
    Linsere(l, 20, 2);
    assert(Ltamanho(l) == 3);
    assert(Lexamina(l, 1) == 10);
    assert(Lexamina(l, 2) == 20);
    assert(Lexamina(l, 3) == 30);
    assert(Llocaliza(l, 20) == 2);
    assert(Lremove(l, 2) == 20);
    assert(Lexamina(l, 2) == 30);
    Ldestroi(l);
}

static Grafo criaGrafoExemplo(void)
{
    Grafo g = GGcriaGrafo(6, 8);
    int i;

    assert(g != NULL);

    for (i = 1; i <= 6; ++i) {
        assert(GVcriaVertice(g) == i);
    }

    assert(GAcriaAresta(g, 6, 1) == 1);
    assert(GAcriaAresta(g, 6, 3) == 2);
    assert(GAcriaAresta(g, 3, 6) == 3);
    assert(GAcriaAresta(g, 1, 3) == 4);
    assert(GAcriaAresta(g, 1, 2) == 5);
    assert(GAcriaAresta(g, 2, 3) == 6);
    assert(GAcriaAresta(g, 2, 2) == 7);
    assert(GAcriaAresta(g, 5, 4) == 8);
    return g;
}

static void testaGrafo(void)
{
    Grafo g = criaGrafoExemplo();
    Grafo carregado;
    int a;

    assert(GInumeroVertices(g) == 6);
    assert(GInumeroArestas(g) == 8);
    assert(GInumeroVerticesMax(g) == 6);
    assert(GInumeroArestasMax(g) == 8);

    assert(GBexisteArestaDir(g, 6, 3));
    assert(GBexisteArestaDir(g, 3, 6));
    assert(!GBexisteArestaDir(g, 3, 1));
    assert(GBexisteAresta(g, 3, 1));
    assert(GApegaArestaDir(g, 1, 2) == 5);
    assert(GApegaAresta(g, 2, 1) == 5);

    assert(GIpegaGrau(g, 2) == 4);
    assert(GBarestaLaco(g, 7));
    assert(GValfa(g, 1) == 6);
    assert(GVomega(g, 1) == 1);
    assert(GVvizinho(g, 1, 6) == 1);
    assert(GVvizinho(g, 1, 1) == 6);
    assert(GVvizinho(g, 1, 3) == 0);

    assert(GAprimaEntrada(g, 2) == 5);
    assert(GAproxEntrada(g, 2, 5) == 7);
    assert(GAprimaSaida(g, 2) == 6);
    assert(GAproxSaida(g, 2, 6) == 7);

    assert(GBsalvaGrafo(g, "grafo_teste.txt"));
    carregado = GGcarregaGrafo("grafo_teste.txt");
    assert(carregado != NULL);
    assert(GInumeroVertices(carregado) == 6);
    assert(GInumeroArestas(carregado) == 8);
    assert(GApegaArestaDir(carregado, 3, 6) == 3);
    carregado = GGdestroiGrafo(carregado);
    assert(carregado == NULL);

    assert(removeAresta(g, 4));
    assert(!GBexisteIdAresta(g, 4));
    assert(GInumeroArestas(g) == 7);
    assert(GAcriaAresta(g, 4, 1) == 4);

    assert(removeVertice(g, 2));
    assert(!GBexisteIdVertice(g, 2));
    assert(!GBexisteIdAresta(g, 5));
    assert(!GBexisteIdAresta(g, 6));
    assert(!GBexisteIdAresta(g, 7));
    assert(GInumeroVertices(g) == 5);
    assert(GInumeroArestas(g) == 5);

    /* O formato original nao representa a lacuna no id 2. */
    assert(!GBsalvaGrafo(g, "grafo_com_lacuna.txt"));

    assert(GVcriaVertice(g) == 2);
    assert(GAcriaAresta(g, 1, 2) == 5);

    a = GAprimeiraAresta(g);
    while (a != 0) {
        assert(GBexisteIdAresta(g, a));
        a = GAproximaAresta(g, a);
    }

    g = GGdestroiGrafo(g);
    assert(g == NULL);
}

static void demonstraCaminho(void)
{
    Grafo g = criaGrafoExemplo();
    float pesos[9] = {0.0F, 1.0F, 1.0F, 1.0F, 1.0F,
                      1.0F, 1.0F, 1.0F, 1.0F};

    printf("Caminho esperado: 3 -> 6 -> 1 -> 2\n");
    printf("Caminho obtido:   ");
    Gcaminho(g, pesos, 3, 2);

    printf("Sem caminho esperado: 1\n");
    printf("Caminho obtido:       ");
    Gcaminho(g, pesos, 1, 4);

    g = GGdestroiGrafo(g);
}

int main(void)
{
    testaLimitesEArquivosInvalidos();
    testaPilha();
    testaFila();
    testaLista();
    testaGrafo();
    demonstraCaminho();

    (void)remove("grafo_teste.txt");
    (void)remove("grafo_com_lacuna.txt");

    puts("Todos os testes com assert foram concluidos com sucesso.");
    return 0;
}
