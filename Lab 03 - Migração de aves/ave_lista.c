#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF INT_MAX

typedef struct Tvertice{
    int destino;
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
    aux->destino = v;
    aux->peso = w;
    aux->proximo = lista->adjacente[u];
    lista->adjacente[u] = aux;
 
    Tvertice *aux1 = malloc(sizeof(Tvertice));
    aux1->destino = u;
    aux1->peso = w;
    aux1->proximo = lista->adjacente[v];
    lista->adjacente[v] = aux1;

}

void Imprime(TlistaAdj *lista, int N){
    int i;
    for(i=0; i<N; i++){
        printf("\n%d:", i);
        Tvertice *percorre = lista->adjacente[i];
        while(percorre != NULL){
            printf(" %d", percorre->destino);
            percorre = percorre->proximo;
        }
    }
}

void Djikstra(TlistaAdj *lista, int origem, int *antecessor, int *dist){
   int *aux = malloc(lista->tamanho*sizeof(int));

    int i;
   for(i=0; i < lista->tamanho ; i++){
      antecessor[i] = -1;
      dist[i] = INF;
   }
   antecessor[origem] = origem;
   dist[origem] = 0;

   Tvertice *percorre;
   for(percorre = lista->adjacente[origem]; percorre != NULL; percorre = percorre->proximo) {
      dist[percorre->destino] = percorre->peso;
      aux[percorre->destino] = origem;
   }

   while (1) {
      int indMin;
      int mindist = INF;
      for(i=0; i< lista->tamanho; ++i){
         if(antecessor[i] == -1 && dist[i] < mindist){
            mindist = dist[i];
            indMin = i;
         }
      }
      if (mindist == INF) break;
      antecessor[indMin] = aux[indMin];
      for(percorre = lista->adjacente[indMin]; percorre != NULL; percorre = percorre->proximo) {
         int destino = percorre->destino;
         int peso = percorre->peso;
         if (dist[indMin] + peso < dist[destino]){
            dist[destino] = dist[indMin] + peso;
            aux[destino] = indMin;
         }
      }
   }
   free(aux);
}

int main(){

    int N, M;
    int tamanhog;
    scanf("%d %d", &N, &M);

    tamanhog = N*2;

    
    int antecessor[tamanhog];
    int dist[tamanhog];


    TlistaAdj lista;
    Inicializa(&lista, tamanhog);

    int u, v, w;
    int ui, up;
    int vi, vp;

    int i;
    for(i=0; i<M; i++){
        scanf("%d %d %d", &u, &v, &w);
        ui = tamanhog-u;
        up = u-1;

        vi = tamanhog-v;
        vp = v-1;


        Insere(&lista, ui, vp, w);
        Insere(&lista, up, vi, w);
     
    }

    Djikstra(&lista, 0, antecessor, dist);


   if(dist[N-1] != INF) printf("%d\n", dist[N-1]);
   else printf("%d\n", -1);

    return 0;
}