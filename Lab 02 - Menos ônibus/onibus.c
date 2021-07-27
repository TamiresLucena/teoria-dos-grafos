#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF INT_MAX

typedef struct Tvertice{
    int dado;
    int peso;
    struct Tvertice *proximo;
}Tvertice;

typedef struct TlistaAdj{
    int tamanho;
    Tvertice **adjacente;
}TlistaAdj;

void Inicializa(TlistaAdj *lista, int N){
    lista->adjacente = malloc(N*sizeof(Tvertice*));
    lista->tamanho = N;

    int i;
    for(i=0;i<N; i++){
        lista->adjacente[i] = NULL;
    }
}

void Insere(TlistaAdj *lista, int u, int v, int w){
    Tvertice *aux = malloc(sizeof(Tvertice));
    aux->dado = v;
    aux->peso = w;
    aux->proximo = lista->adjacente[u];
    lista->adjacente[u] = aux;

    Tvertice *aux1 = malloc(sizeof(Tvertice));
    aux1->dado = u;
    aux1->peso = w;
    aux1->proximo = lista->adjacente[v];
    lista->adjacente[v] = aux1;
}

int main(){

    int N, M;
    scanf("%d %d", &N, &M);

    
    int visitados[N];
    int custo[N];

    TlistaAdj lista;
    Inicializa(&lista, N);

    int pesototal = 0;
    int u, v, w;
    int i;
    for(i=0; i<M; i++){
        scanf("%d %d %d", &u, &v, &w);
        Insere(&lista, u, v, w);
        pesototal += w;
    }

    int total = 0;
    for(i=0; i<N; i++) {
        visitados[i] = 0;
        custo[i] = INF;
    }

    custo[0] = 0;

    int qtd;
    for(qtd = N; qtd>0; qtd--) {
        int no = -1;
        for(i=0; i<N; i++){
            if(!visitados[i] && (no==-1 || custo[i] < custo[no]))
            no = i;
        }
        visitados[no] = 1;

        // if(custo[no] == INF) {
        //     total = INF;
        //     break;
        // }

        total += custo[no];

        Tvertice *percorre;
        for(percorre=lista.adjacente[no]; percorre != NULL; percorre = percorre->proximo){
            if(custo[percorre->dado] > percorre->peso) custo[percorre->dado] = percorre->peso;
        }

    }
    int saida = pesototal - total;
    printf("%d\n", saida);

    return 0;
}