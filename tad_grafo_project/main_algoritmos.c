#include "algoritmos.h"

#include <stdio.h>
#include <stdlib.h>

static void lePesosPorStdin(int aMax, float *pesos)
{
    for (int i = 1; i <= aMax; ++i) {
        for (;;) {
            printf("Peso da aresta a%d: ", i);
            if (scanf("%f", &pesos[i]) == 1) {
                break;
            }
            /* limpa entrada inválida */
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {
                /* descarta */
            }
            printf("Valor invalido. Tente novamente.\n");
            pesos[i] = 0.0f;
        }
    }
}


int main(void)
{
    int opcao;
    int v, a;
    char nomeArquivo[256];

    Grafo g = NULL;
    float *pesos = NULL;

    printf("Algoritmos em Grafo (TAD Grafo)\n");
    printf("Escolha modo de entrada:\n");
    printf("1) Ler grafo via stdin\n");
    printf("2) Ler grafo via arquivo (exige caminho + pesos via stdin)\n");
    printf("Opcao: ");
    if (scanf("%d", &opcao) != 1) {
        return 0;
    }

    if (opcao == 1) {
        if (scanf("%d %d", &v, &a) != 2) {
            return 0;
        }

        printf("Grafo criado com V=%d (vertices) e A=%d (arestas max).\n", v, a);

        g = GGcriaGrafo(v, a);
        if (g == NULL) {
            printf("Falha ao criar grafo.\n");
            return 0;
        }

        for (int i = 1; i <= v; ++i) {
            if (GVcriaVertice(g) == 0) {
                printf("Falha ao criar vertice.\n");
                return 0;
            }
        }

        printf("Agora informe as A=%d arestas no formato alfa omega.\n", a);

        for (int i = 1; i <= a; ++i) {
            int alfa, omega;
            printf("Aresta %d/%d (alfa omega): ", i, a);
            if (scanf("%d %d", &alfa, &omega) != 2) {
                return 0;
            }
            if (GAcriaAresta(g, alfa, omega) == 0) {
                printf("Aviso: nao foi possivel criar a aresta (alfa=%d, omega=%d).\n", alfa, omega);
            }
        }

        pesos = (float *)calloc((size_t)a + 1U, sizeof(*pesos));
        if (pesos == NULL) {
            return 0;
        }

        printf("Agora forneca os pesos das arestas: total %d (id a1..a%d).\n", a, a);
        lePesosPorStdin(a, pesos);
    } else if (opcao == 2) {
        printf("Informe o nome do arquivo: ");
        if (scanf("%255s", nomeArquivo) != 1) {
            return 0;
        }

        g = GGcarregaGrafo(nomeArquivo);
        if (g == NULL) {
            printf("Falha ao carregar grafo.\n");
            return 0;
        }

        int vMax = GInumeroVerticesMax(g);
        int aMax = GInumeroArestasMax(g);

        printf("Grafo carregado do arquivo. Vmax=%d, Amax=%d.\n", vMax, aMax);

        pesos = (float *)calloc((size_t)aMax + 1U, sizeof(*pesos));
        if (pesos == NULL) {
            return 0;
        }

        printf("Agora forneca os pesos das arestas: total %d (id a1..a%d).\n", aMax, aMax);
        printf("Observacao: o id da aresta corresponde a ordem em que as arestas estao no arquivo.\n");
        lePesosPorStdin(aMax, pesos);
    } else {
        printf("Opcao invalida.\n");
        return 0;
    }

    for (;;) {
        printf("\nEscolha o algoritmo (ou 0 para voltar):\n");
        printf("1) AGM\n");
        printf("2) BEL (Busca em Largura)\n");
        printf("3) BEP (Busca em Profundidade)\n");
        printf("4) CMC (Caminho mais curto)\n");
        printf("5) CC (Componentes conexos)\n");
        printf("0) Voltar / Repetir menu de entrada\n");
        printf("Opcao: ");

        int alg;
        if (scanf("%d", &alg) != 1) {
            break;
        }

        if (alg == 0) {
            /* Volta ao menu de entrada: libera e reinicia tudo. */
            break;
        }

        if (alg == 1) {
            AGM(g, pesos);
        } else if (alg == 2) {
            int partida;
            printf("Partida: ");
            scanf("%d", &partida);
            BEL(g, partida);
        } else if (alg == 3) {
            int partida;
            printf("Partida: ");
            scanf("%d", &partida);
            BEP(g, partida);
        } else if (alg == 4) {
            int partida, chegada;
            printf("Partida: ");
            scanf("%d", &partida);
            printf("Chegada: ");
            scanf("%d", &chegada);
            CMC(g, pesos, partida, chegada);
        } else if (alg == 5) {
            CC(g);
        } else {
            printf("Opcao invalida.\n");
        }
    }

    if (pesos != NULL) {
        free(pesos);
    }
    (void)GGdestroiGrafo(g);
    return 0;
}
