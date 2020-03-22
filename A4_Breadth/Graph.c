//-----------------------------------------------------------------------------
// Henry Nguyen
// CruzID: hnguye87
// Assignment: pa4
//-----------------------------------------------------------------------------
// Graph.c
// Implementation file for Graph ADT
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "Graph.h"
#include "List.h"

// private Graph Obj type
typedef struct GraphObj{
   List* listArr;
   int* color; // 0 = white, 1 = gray, 2 = black
   int* dist; // -1 = inf
   int* parent; // 0 = nil
   int order; //vertices
   int size; //edges
   int source;
} GraphObj;

 //Returns a reference to a new Graph object in the zero state.
Graph newGraph(int n){
    Graph G;
    G = malloc(sizeof(GraphObj) * n);
    G->listArr = malloc(sizeof(GraphObj) * (n+1));
    for(int i = 0; i < n+1; i++){
        G->listArr[i] = newList();
    }
    G->color = (int*)malloc(sizeof(int) * (n+1));
    G->parent = (int*)malloc(sizeof(int) * (n+1));
    G->dist = (int*)malloc(sizeof(int) * (n+1));
    for(int i = 1; i < n+1; i++){
	G->dist[i] = INF;
    }
    G->order = n; //vertex
    G->size = 0; //edges
    G->source = NIL; // 0 = nil source | most recently used source
    return(G);
}

//frees Graph* pG of all allocated memory
void freeGraph(Graph* pG){
    if(pG == NULL){
        printf("Called freeGraph() with a NULL pointer");
        exit(-1);
    }
    for(int i = 0; i < (*pG)->order+1; i++)
        freeList(&(*pG)->listArr[i]);
    free((*pG)->listArr);
    (*pG)->listArr = NULL;
    free((*pG)->color);
    free((*pG)->parent);
    free((*pG)->dist);
    free(*pG);
    *pG = NULL;
}

int getOrder(Graph G){ //vertex
    if(G == NULL){
        printf("Called getOrder() with a NULL pointer");
        exit(-1);
    }
    return G->order;
}
int getSize(Graph G){ //edges
    if(G == NULL){
        printf("Called getSize() with a NULL pointer");
        exit(-1);
    }
    return G->size;

}
int getSource(Graph G){ //most recently used source
    if(G == NULL){
        printf("Called getSource() with a NULL pointer");
        exit(-1);
    }
    return G->source;
}

int getParent(Graph G, int u){
    if(G == NULL){
        printf("Called getParent() with a NULL pointer");
        exit(-1);
    }
    if(u < 1 || u > getOrder(G)){
        printf("Called getParent() with invalid number");
        exit(-1);
    }
    return G->parent[u];
}

int getDist(Graph G, int u){
    if(G == NULL){
        printf("Called getDist() with a NULL pointer");
        exit(-1);
    }
    if(u < 1 || u > getOrder(G)){
        printf("Called getDist() with invalid number");
        exit(-1);
    }
    return G->dist[u];
}

//path from source to u
void getPath(List L, Graph G, int u){ //reads backwards from u to source
    if(G == NULL){
        printf("Called getPath() with a NULL pointer");
        exit(-1);
    }
    if(getSource(G) == 0){
        printf("Called getPath() without calling BST first");
        exit(-1);
    }
    if(u < 1 || u > getOrder(G)){
        printf("Called getPath() with invalid number");
        return;
    }

    if(getSource(G) == u){
        append(L, getSource(G));
        return;
    }
    else if(G->parent[u] == 0){ //0 == nil
	clear(L);
        append(L, 0); //0 == nil, not reachable
        return;
    }
    else{
        getPath(L, G, G->parent[u]);
	append(L,u);
    }
}

void makeNull(Graph G){
    if(G == NULL){
        printf("Called makeNull() with a NULL pointer");
        exit(-1);
    }
    for(int i = 0; i < G->size; i++)
        freeList(&(G)->listArr[i]);
    free(G->listArr);
    G->listArr = NULL;
    free(G->color);
    G->color = NULL;
    free(G->parent);
    G->parent = NULL;
    free(G->dist);
    G->dist = NULL;
    G->order = 0; //vertex
    G->size = 0;  //edge
    G->source = NIL; //most recently used source

}

//add edge
void addEdge(Graph G, int u, int v){
    if(G == NULL){
        printf("Called addEdge() with a NULL pointer");
        exit(-1);
    }
    if(u < 1 || u > getOrder(G)){
        printf("Called addEdge() with invalid number");
        return;
    }
    if(v < 1 || v > getOrder(G)){
        printf("Called addEdge() with invalid number");
        return;
    }
    for(moveFront(G->listArr[u]); index(G->listArr[u]) != -1; moveNext(G->listArr[u])){
        if(get(G->listArr[u]) == v){
            break;
        }
        if(get(G->listArr[u]) > v){
            insertBefore(G->listArr[u], v);
            break;
        }
    }
    if(index(G->listArr[u]) == -1){
        append(G->listArr[u], v);
        }

    for(moveFront(G->listArr[v]); index(G->listArr[v]) != -1; moveNext(G->listArr[v])){
        if(get(G->listArr[v]) == u){
            break;
        }
        if(get(G->listArr[v]) > u){
            insertBefore(G->listArr[v], u);
            break;
        }
    }
    if(index(G->listArr[v]) == -1){
        append(G->listArr[v], u);
    }
	G->size++;
}

//directed edge
void addArc(Graph G, int u, int v){
    if(G == NULL){
        printf("Called addArc() with a NULL pointer");
        exit(-1);
    }
    if(u < 1 || u > getOrder(G)){
        printf("Called addArc() with invalid number");
        return;
    }
    for(moveFront(G->listArr[u]); index(G->listArr[u]) != -1; moveNext(G->listArr[u])){
        if(get(G->listArr[u]) == v){
            break;
        }
        if(get(G->listArr[u]) > v){
            insertBefore(G->listArr[u], v);
            G->size++;
            break;
        }
    }
    if(index(G->listArr[u]) == -1){
        append(G->listArr[u], v);
        G->size++;
    }
}

void BFS(Graph G, int s){
    if(G == NULL){
        printf("Called BFS() with a NULL pointer");
        exit(-1);
    }
    if(s < 1 || s > getOrder(G)){
        printf("Called BFS() with invalid number");
        return;
    }
    G->source = s;
    for(int i = 1; i < getOrder(G)+1; i++){
        if(i != s){
            G->color[i] = 0; // 0 = white
            G->dist[i] = INF; //infinite
            G->parent[i] = NIL; // 0 = nil
        }
    }
    G->color[s] = 1; //gray
    G->dist[s] = 0;
    G->parent[s] = NIL;
    List A = newList(); //new empty queue
    append(A, s);
    while(!isEmpty(A)){
        int x = front(A);
        deleteFront(A);
        for(moveFront(G->listArr[x]); index(G->listArr[x]) != -1; moveNext(G->listArr[x])){
            int y  = get(G->listArr[x]);
            if(G->color[y] == 0){ //white
                G->color[y] = 1; //gray
                G->dist[y] = G->dist[x] + 1;
                G->parent[y] = x;
                append(A, y);
            }
        }
        G->color[x] = 2; //black
    }
    freeList(&A);
}

void printGraph(FILE* out, Graph G){
    if(G == NULL){
        printf("Called printGraph() with a NULL pointer");
        exit(-1);
    }

    bool flag = false;
    List* L = G->listArr;
    for(int i = 1; i < getOrder(G)+1; i++){
        List li = L[i];
        if(flag == false){
            flag = true;
            fprintf(out, "%d: ",  i);
        }
        for(moveFront(li); index(li)!= -1; moveNext(li)){
            fprintf(out, "%d ", get(li));
        }
        if(flag == true)
            fprintf(out, " \n");
        flag = false;
   }
}
