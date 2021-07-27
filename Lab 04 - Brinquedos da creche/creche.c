#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
 
#define INF INT_MAX

typedef struct Tvertice{
    int dado;
    int peso;
    struct Tvertice *proximo;
}Tvertice;
 
typedef struct Tgrafo{
    int tamanho;
    Tvertice **adjacente;
}Tgrafo;
 
void Inicializa(Tgrafo *grafo, int N){
    grafo->adjacente = malloc(N*sizeof(Tvertice*));
    grafo->tamanho = N;
 
    int i;
    for(i=0;i<N; i++){
        grafo->adjacente[i] = NULL;
    }
}
 
void Insere(Tgrafo *grafo, int u, int v, int w){
    Tvertice *aux = malloc(sizeof(Tvertice));
    aux->dado = v;
    aux->peso = w;
    aux->proximo = grafo->adjacente[u];
    grafo->adjacente[u] = aux;
 
//     Tvertice *aux1 = malloc(sizeof(Tvertice));
//     aux1->dado = u;
//     aux1->peso = w;
//     aux1->proximo = grafo->adjacente[v];
//     grafo->adjacente[v] = aux1;
}
 

 void Imprime(Tgrafo *grafo, int N){
    int i;
    for(i=0; i<N; i++){
        printf("\n%d:", i);
        Tvertice *percorre = grafo->adjacente[i];
        while(percorre != NULL){
            printf(" %d", percorre->dado);
            percorre = percorre->proximo;
        }
    }
}


int encontraCasamento(Tgrafo *grafo, int crianca, int *visitados, int *casamento) {

    Tvertice *percorre = grafo->adjacente[crianca];

    while(percorre != NULL){
        if(visitados[percorre->dado] != 1){
            visitados[percorre->dado] = 1;
            if(casamento[percorre->dado] < 0 || encontraCasamento(grafo, casamento[percorre->dado], visitados, casamento)){
                casamento[percorre->dado] = crianca;
                return 1;
            }
        }
        percorre = percorre->proximo;
    }

    return 0;
}


int casamentoPerfeito(Tgrafo *grafo, int N, int M) {

    int *casamento = malloc(M*sizeof(int));
    int i, j;
    for(i=0; i<M; i++) casamento[i] = -1;

    int brinquedos = 0;

    for (i=0; i<N; i++) {
        int *visitados = malloc(M*sizeof(int));
        for(j=0; j<M; j++) visitados[j] = 0;
  
        if (encontraCasamento(grafo, i, visitados, casamento)) brinquedos++;
    }

    return brinquedos;
}


int main(){
 
    int N, M, L;
    scanf("%d %d %d", &N, &M, &L);
 
    Tgrafo grafo;
    Inicializa(&grafo, N);
 
    int i; 
    int u, v;

    for(i=0; i<L; i++){
        scanf("%d %d", &u, &v);
        Insere(&grafo, u, v, 1);
    }

    // Imprime(&grafo, N);

    int max = casamentoPerfeito(&grafo, N, M);
    printf("%d", max);


 
    return 0;
}