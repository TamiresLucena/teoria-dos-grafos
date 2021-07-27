#include <stdio.h> 
#include <stdlib.h>
#include <limits.h> 


#define INF INT_MAX

int minDistance(int dist[], int visitados[], int tamanhog){ 
    int min = INF, min_index; 
  
    int v;
    for (v = 0; v < tamanhog; v++){
        if (visitados[v] == 0 && dist[v] <= min){
            min = dist[v], min_index = v; 
        }
    }
  
    return min_index; 
} 
  
void dijkstra(int **grafo, int src, int tamanhog) { 
    int dist[tamanhog];
  
    int visitados[tamanhog];
    int i;
    for (i = 0; i < tamanhog; i++){
        dist[i] = INF, visitados[i] = 0;
    }
    dist[src] = 0;
    int count;
    for (count = 0; count < tamanhog - 1; count++) {
        int u = minDistance(dist, visitados, tamanhog); 
        visitados[u] = 1;
        int v;
        for (v = 0; v < tamanhog; v++){
            if (!visitados[v] && grafo[u][v] && dist[u] != INF && dist[u] + grafo[u][v] < dist[v]){
                dist[v] = dist[u] + grafo[u][v]; 
            }
        }
    } 
  
    if(dist[(tamanhog/2)-1] != INF) printf("%d\n", dist[(tamanhog/2)-1]);
    else printf("%d\n", -1);
} 

int main(){


    int N, M;   
    scanf("%d %d", &N, &M);

    int tamanhog = N*2;
    int **grafo = malloc(tamanhog * sizeof(int*));
    int i;
    for(i=0; i<tamanhog; i++) grafo[i] = malloc(tamanhog * sizeof(int));

    int u, v, w;
    int ui, up;
    int vi, vp;

    for(i=0; i<M; i++){
        scanf("%d %d %d", &u, &v, &w);
        ui = tamanhog-u;
        up = u-1;

        vi = tamanhog-v;
        vp = v-1;

        grafo[ui][vp] = w;
        grafo[vp][ui] = w;
        grafo[up][vi] = w;
        grafo[vi][up] = w;     
    }

    dijkstra(grafo, 0, tamanhog);    

    return 0;
}