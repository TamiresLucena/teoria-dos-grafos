#include <stdio.h>
#include <stdlib.h>


typedef struct Titem{
    int x;
    int y;
    struct Titem *prox;    
}Titem;

typedef struct Tfila {
    Titem *inicio;
    Titem *fim;
    int tamanho;
}Tfila;

void InicializaFila(Tfila *fila){
    fila->inicio = NULL;
    fila->fim = NULL;
    fila->tamanho = 0;
}

void Insere(Tfila *fila, Titem item){
    Titem *aux = malloc(sizeof(Titem));
    *aux = item;

    if(fila->inicio == NULL){
        fila->inicio = aux;
    }
    else {
        fila->fim->prox = aux;
    }
    fila->fim = aux;
    fila->tamanho ++;
}

Titem Remove(Tfila *fila){

    Titem *aux = fila->inicio->prox;
    Titem item = *fila->inicio;
    fila->tamanho --;
    fila->inicio = aux;

    if(fila->inicio == NULL) fila->fim == NULL;
    
    return item;
}

// int Valido(int x, int y, int **visitados){
//     if(x < 0 || x > 7 || y < 0 || y > 7) return 0;
//     if(visitados[x][y] == 1) return 0;
//     return 1;
// }

int main(){

    int dx[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
    int dy[8] = {1, 2, 2, 1, -1, -2, -2, -1};

    int visitados[10][10];
    // int **visitados = malloc(10 * sizeof(int*));
    // int i;
    // for(i=0; i<11; i++) visitados[i] = malloc(10 * sizeof(int));

    int distancia[8][8];

    int dist = 0;

    char x;
    int y;

    char x1;
    int y1;

    scanf("%c%d %c%d", &x, &y, &x1, &y1);

    x = x - 97;
    x1 = x1 - 97;
    y = y - 1;
    y1 = y1 - 1;
    

    int i, j;
    for(i=0; i<10; i++){
        for(j=0; j<10; j++){
            visitados[i][j] = 0;
        }
    }

    Tfila fila;
    InicializaFila(&fila);

    Titem item;
    item.x = x;
    item.y = y;
    item.prox = NULL;
    Insere(&fila, item);

    distancia[x][y] = 0;
    visitados[x][y] = 1;
    if(x == x1 && y == y1) dist = distancia[x][y];



    while(fila.inicio != NULL){
        
        Titem removido = Remove(&fila);
        // printf("fila inicio %d%d\n", removido.x, removido.y);

        for(i=0; i<8; i++){

            if(!(removido.x + dx[i] < 0 || removido.x + dx[i] > 7 || removido.y + dy[i] < 0 || removido.y + dy[i] > 7 || visitados[removido.x + dx[i]][removido.y + dy[i]])){

            // printf("valido = %d ", removido.x + dx[i]);
            // printf("%d\n", removido.y + dy[i]);
            
            // int valido = Valido(removido.x + dx[i], removido.y + dy[i]);
            // if(valido == 1){
                x = removido.x + dx[i];
                y = removido.y + dy[i];

                distancia[x][y] = distancia[removido.x][removido.y] + 1;

                // printf("dist  = %d\n", distancia[x][y]);
                visitados[x][y] = 1;

                Titem item;
                item.x = x;
                item.y = y;
                item.prox = NULL;
                Insere(&fila, item);

                // printf("tamanho = %d\n", fila.tamanho);

                if(x == x1 && y == y1){
                    dist = distancia[x][y];
                    break;
                }
            }

        }

        // printf("fila inicio = %d%d", fila.inicio->x, fila.inicio->y);
        // printf("fila fim = %d%d", fila.fim->x, fila.fim->y);
    }

    printf("%d", dist);

    return 0;
}