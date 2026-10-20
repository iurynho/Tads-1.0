#include "grafo.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define MV 12
#define MA 30

typedef struct { int active, u, v; } ME;

static int min_free_v(int av[]) { int i; for(i=1;i<=MV;i++) if(!av[i]) return i; return 0; }
static int min_free_e(ME e[]) { int i; for(i=1;i<=MA;i++) if(!e[i].active) return i; return 0; }
static int countv(int av[]) { int i,c=0; for(i=1;i<=MV;i++) c+=av[i]; return c; }
static int counte(ME e[]) { int i,c=0; for(i=1;i<=MA;i++) c+=e[i].active; return c; }

static void verify(Grafo g, int av[], ME e[]) {
    int i, prev, got, c;
    assert(GInumeroVertices(g)==countv(av));
    assert(GInumeroArestas(g)==counte(e));
    for(i=1;i<=MV;i++) {
        int deg=0, j;
        assert(GBexisteIdVertice(g,i)==av[i]);
        for(j=1;j<=MA;j++) if(e[j].active) {
            if(e[j].u==i) deg++;
            if(e[j].v==i) deg++;
        }
        assert(GIpegaGrau(g,i)==(av[i]?deg:0));

        prev=0; c=0;
        for(got=GAprimaAresta(g,i); got; got=GAproxAresta(g,i,got)) {
            assert(got>prev && e[got].active && (e[got].u==i||e[got].v==i));
            prev=got; c++;
        }
        { int exp=0; for(j=1;j<=MA;j++) if(e[j].active&&(e[j].u==i||e[j].v==i)) exp++; assert(c==(av[i]?exp:0)); }

        prev=0; c=0;
        for(got=GAprimaEntrada(g,i); got; got=GAproxEntrada(g,i,got)) {
            assert(got>prev && e[got].active && e[got].v==i); prev=got; c++;
        }
        { int exp=0; for(j=1;j<=MA;j++) if(e[j].active&&e[j].v==i) exp++; assert(c==(av[i]?exp:0)); }

        prev=0; c=0;
        for(got=GAprimaSaida(g,i); got; got=GAproxSaida(g,i,got)) {
            assert(got>prev && e[got].active && e[got].u==i); prev=got; c++;
        }
        { int exp=0; for(j=1;j<=MA;j++) if(e[j].active&&e[j].u==i) exp++; assert(c==(av[i]?exp:0)); }
    }
    for(i=1;i<=MA;i++) {
        assert(GBexisteIdAresta(g,i)==e[i].active);
        assert(GValfa(g,i)==(e[i].active?e[i].u:0));
        assert(GVomega(g,i)==(e[i].active?e[i].v:0));
        assert(GBarestaLaco(g,i)==(e[i].active&&e[i].u==e[i].v));
    }
    prev=0; c=0;
    for(got=GVprimeiroVertice(g);got;got=GVproximoVertice(g,got)){ assert(got>prev&&av[got]); prev=got;c++; }
    assert(c==countv(av));
    prev=0; c=0;
    for(got=GAprimeiraAresta(g);got;got=GAproximaAresta(g,got)){ assert(got>prev&&e[got].active); prev=got;c++; }
    assert(c==counte(e));
    for(i=1;i<=MV;i++) { int j; for(j=1;j<=MV;j++) {
        int k, d=0, nd=0;
        for(k=1;k<=MA;k++) if(e[k].active) {
            if(!d && e[k].u==i&&e[k].v==j) d=k;
            if(!nd && ((e[k].u==i&&e[k].v==j)||(e[k].u==j&&e[k].v==i))) nd=k;
        }
        if(!av[i]||!av[j]) d=nd=0;
        assert(GApegaArestaDir(g,i,j)==d);
        assert(GApegaAresta(g,i,j)==nd);
        assert(GBexisteArestaDir(g,i,j)==(d!=0));
        assert(GBexisteAresta(g,i,j)==(nd!=0));
    }}
}

int main(void) {
    unsigned seed=1234567U;
    int round;
    srand(seed);
    for(round=0;round<10;round++) {
        Grafo g=GGcriaGrafo(MV,MA);
        int av[MV+1]={0}; ME e[MA+1]={{0}};
        int step;
        assert(g);
        for(step=0;step<1000;step++) {
            int op=rand()%4;
            if(op==0) {
                int expected=min_free_v(av); int got=GVcriaVertice(g);
                assert(got==expected); if(got) av[got]=1;
            } else if(op==1) {
                int ids[MV], n=0, i, u,v, expected,got;
                for(i=1;i<=MV;i++) if(av[i]) ids[n++]=i;
                if(n) { u=ids[rand()%n]; v=ids[rand()%n]; expected=min_free_e(e); got=GAcriaAresta(g,u,v); assert(got==expected); if(got){e[got].active=1;e[got].u=u;e[got].v=v;} }
                else assert(GAcriaAresta(g,1,1)==0);
            } else if(op==2) {
                int id=1+rand()%MA; int expected=e[id].active; int got=removeAresta(g,id); assert(got==expected); if(got)e[id].active=0;
            } else {
                int id=1+rand()%MV; int expected=av[id]; int got=removeVertice(g,id); int k; assert(got==expected); if(got){ av[id]=0; for(k=1;k<=MA;k++) if(e[k].active&&(e[k].u==id||e[k].v==id))e[k].active=0; }
            }
            verify(g,av,e);
        }
        g=GGdestroiGrafo(g); assert(!g);
    }
    puts("stress ok");
    return 0;
}
