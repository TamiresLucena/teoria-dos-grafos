#include <stdio.h> 
#include <stdlib.h> 
#include <limits.h>

#define INF INT_MAX
  
typedef struct Tvertice { 
    int dest; 
    int peso; 
    struct Tvertice* prox; 
}Tvertice; 
  
typedef struct TlistaAdj { 
    struct Tvertice *inicio; 
}TlistaAdj; 

typedef struct Tgrafo { 
    int V; 
    struct TlistaAdj* vetor; 
}Tgrafo; 
  
typedef struct MinHeapNo { 
    int  v; 
    int dist; 
}MinHeapNo;

typedef struct MinHeap { 
    int tamanho;      
    int capacidade;  
    int *pos;     
    MinHeapNo **vetor; 
}MinHeap; 

Tvertice* novoNoListaAdj(int dest, int peso) { 
    struct Tvertice* novono =  malloc(sizeof(struct Tvertice)); 
    novono->dest = dest; 
    novono->peso = peso; 
    novono->prox = NULL; 
    return novono; 
} 
  
Tgrafo* criaGrafo(int V){ 

    Tgrafo* grafo = malloc(sizeof(Tgrafo)); 
    grafo->V = V; 
  
    grafo->vetor =  malloc(V * sizeof(TlistaAdj)); 

    int i;
    for (i = 0; i < V; ++i) 
        grafo->vetor[i].inicio = NULL; 
  
    return grafo; 
} 

MinHeapNo* novoMinHeapNo(int v, int dist) { 
    MinHeapNo* MinHeapNo =  malloc(sizeof(MinHeapNo)); 
    MinHeapNo->v = v; 
    MinHeapNo->dist = dist; 
    return MinHeapNo; 
} 
  
MinHeap* criaMinHeap(int capacidade) { 
    MinHeap* minHeap = malloc(sizeof(MinHeap)); 
    minHeap->pos = malloc(capacidade * sizeof(int)); 
    minHeap->tamanho = 0; 
    minHeap->capacidade = capacidade; 
    minHeap->vetor =  malloc(capacidade * sizeof(MinHeapNo*)); 
    return minHeap; 
}

void insereAresta(struct Tgrafo* Tgrafo, int origem, int dest, int peso) { 
     
    struct Tvertice* novono = novoNoListaAdj(dest, peso); 
    novono->prox = Tgrafo->vetor[origem].inicio; 
    Tgrafo->vetor[origem].inicio = novono; 
  
    novono = novoNoListaAdj(origem, peso); 
    novono->prox = Tgrafo->vetor[dest].inicio; 
    Tgrafo->vetor[dest].inicio = novono; 
} 
  
void trocaMinHeapNo(MinHeapNo** a,MinHeapNo** b){ 
    struct MinHeapNo* t = *a; 
    *a = *b; 
    *b = t; 
} 

void minHeapify(MinHeap* minHeap, int indice) { 
    int menor, esquerdo, direito; 
    menor = indice; 
    esquerdo = 2 * indice + 1; 
    direito = 2 * indice + 2; 
  
    if (esquerdo < minHeap->tamanho && minHeap->vetor[esquerdo]->dist < minHeap->vetor[menor]->dist) menor = esquerdo; 
  
    if (direito < minHeap->tamanho && minHeap->vetor[direito]->dist < minHeap->vetor[menor]->dist) menor = direito; 
  
    if (menor != indice) { 
        struct MinHeapNo *menorNo = minHeap->vetor[menor]; 
        struct MinHeapNo *indiceNo = minHeap->vetor[indice]; 
  
        minHeap->pos[menorNo->v] = indice; 
        minHeap->pos[indiceNo->v] = menor; 
  
        trocaMinHeapNo(&minHeap->vetor[menor], &minHeap->vetor[indice]); 
  
        minHeapify(minHeap, menor); 
    } 
} 
    
struct MinHeapNo* pegaMin(struct MinHeap* minHeap) { 
    if (minHeap->tamanho == 0) return NULL; 
  
    struct MinHeapNo* raiz = minHeap->vetor[0]; 
    struct MinHeapNo* ultimoNo = minHeap->vetor[minHeap->tamanho - 1]; 
    minHeap->vetor[0] = ultimoNo; 
  
    minHeap->pos[raiz->v] = minHeap->tamanho-1; 
    minHeap->pos[ultimoNo->v] = 0; 
  
    --minHeap->tamanho; 
    minHeapify(minHeap, 0); 
  
    return raiz; 
} 

void decrementaChave(struct MinHeap* minHeap, int v, int dist){ 
   
    int i = minHeap->pos[v]; 
  
    minHeap->vetor[i]->dist = dist; 
  
    while (i && minHeap->vetor[i]->dist < minHeap->vetor[(i-1)/2]->dist) { 
        minHeap->pos[minHeap->vetor[i]->v] = (i-1)/2; 
        minHeap->pos[minHeap->vetor[(i-1)/2]->v] = i; 
        trocaMinHeapNo(&minHeap->vetor[i], &minHeap->vetor[(i-1)/2]); 
  
        i = (i-1)/2; 
    } 
} 
    
void dijkstra(struct Tgrafo* grafo, int origem) { 
    int V = grafo->V;
    int dist[V];      
  
    MinHeap* minHeap = criaMinHeap(V); 

    int v;
    for (v=0; v<V; ++v){ 
        dist[v] = INF; 
        minHeap->vetor[v] = novoMinHeapNo(v, dist[v]); 
        minHeap->pos[v] = v; 
    } 
  
    minHeap->vetor[origem] = novoMinHeapNo(origem, dist[origem]); 
    minHeap->pos[origem] = origem; 
    dist[origem] = 0; 
    decrementaChave(minHeap, origem, dist[origem]); 
  
    minHeap->tamanho = V; 
  
    while (!minHeap->tamanho == 0) { 
        MinHeapNo* MinHeapNo = pegaMin(minHeap); 
        int u = MinHeapNo->v;

        Tvertice* percorre = grafo->vetor[u].inicio; 
        while (percorre != NULL) { 
            int v = percorre->dest; 

            if(minHeap->pos[v] < minHeap->tamanho && dist[u] != INF && percorre->peso + dist[u] < dist[v]) { 
                dist[v] = dist[u] + percorre->peso; 
                decrementaChave(minHeap, v, dist[v]); 
            } 
            percorre = percorre->prox; 
        } 
    } 
  
    if(dist[(V/2)-1] != INF) printf("%d", dist[(V/2)-1]); 
    else printf("%d", -1); 
} 
  
int main(){ 

    int N, M;
    int tamanhog;
    scanf("%d %d", &N, &M);

    tamanhog = N*2;

    
    int antecessor[tamanhog];
    int dist[tamanhog];

    int V = tamanhog; 
    struct Tgrafo* grafo = criaGrafo(V);

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

        insereAresta(grafo, ui, vp, w);
        insereAresta(grafo, vi, up, w);
     
    }
  
    dijkstra(grafo, 0); 
  
    return 0; 
} 
