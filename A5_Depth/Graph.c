//-----------------------------------------------------------------------------
// Henry Nguyen
// CruzID: hnguye87
// Assignment: pa5
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
   int* dis; // -1 = undef
   int* parent; // 0 = nil
   int* finish;
   int order; //vertices
   int size; //edges
} GraphObj;

 //Returns a reference to a new Graph object in the zero state.
Graph newGraph(int n){
    Graph G;
    G = malloc(sizeof(GraphObj) * n);
    G->listArr = malloc(sizeof(GraphObj) * n+1);
    for(int i = 0; i < n+1; i++){
        G->listArr[i] = newList();
    }
    G->color = (int*)malloc(sizeof(int) * (n+1));
    G->parent = (int*)malloc(sizeof(int) * (n+1));
    G->dis = (int*)malloc(sizeof(int) * (n+1));
    for(int i = 1; i < n+1; i++){
        G->dis[i] = UNDEF;
    }
    G->finish = (int*)malloc(sizeof(int) * (n+1));
    for(int i = 1; i < n+1; i++){
	G->finish[i] = UNDEF;
    }
    G->order = n; //vertex
    G->size = 0; //edges
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
    free((*pG)->dis);
    free((*pG)->finish);
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

int getDiscover(Graph G, int u){
    if(G == NULL){
        printf("Called getDiscover() with a NULL pointer");
        exit(-1);
    }
    if(u < 1 || u > getOrder(G)){
        printf("Called getDiscover() with invalid number");
        exit(-1);
    }
    return G->dis[u];
}

int getFinish(Graph G, int u){
    if(G == NULL){
        printf("Called getFinish() with a NULL pointer");
        exit(-1);
    }
    if(u < 1 || u > getOrder(G)){
        printf("Called getFinish() with invalid number");
        exit(-1);
    }
    return G->finish[u];
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

void DFS(Graph G, List S){
    for(int i = 1; i < getOrder(G)+1; i++){
        G->color[i] = 0; // 0 = white
        G->parent[i] = NIL; // 0 = nil
    }
    int* time = (int*)malloc(sizeof(int));
    time = 0;
    List temp = newList();
    for(moveFront(S); index(S) != -1; moveNext(S)){
        if(G->color[get(S)] == 0){ // 0 = white
            visit(G, get(S), temp, &time);
        }
    }
    clear(S);
    for(moveBack(temp); index(temp) != -1; movePrev(temp))
        append(S, get(temp));
    //free(time);
    freeList(&temp);
}

void visit(Graph G, int x, List L, int* time){
        G->dis[x] = ++(*time);
        G->color[x] = 1;
        for(moveFront(G->listArr[x]); index(G->listArr[x]) != -1; moveNext(G->listArr[x])){
            int y  = get(G->listArr[x]);
            if(G->color[y] == 0){
                G->parent[y] = x;
                visit(G, y, L,time);
            }
        }
        G->color[x] = 2;
        G->finish[x] = ++(*time);
        append(L, x);
}

Graph transpose(Graph G){
    Graph A = newGraph(getOrder(G));
    List* L = G->listArr;
    for(int i = 1; i < G->order+1; i++){
        List li = L[i];
        for(moveFront(li); index(li)!= -1; moveNext(li))
            addArc(A, get(li), i);
    }
    return A;
}

Graph copyGraph(Graph G){
    if(G == NULL){
        printf("Called copyGraph() with a NULL pointer");
        exit(-1);
    }
    Graph A = newGraph(G->order);
    List* L = G->listArr;
    for(int i = 1; i < G->order+1; i++){
        List li = L[i];
        for(moveFront(li); index(li)!= -1; moveNext(li))
            append(A->listArr[i], get(li));
    }
    return A;
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

//    printf("\n");
//    for(int i = 1; i < getOrder(G)+1; i++){
//        printf("%d ", G->finish[i]);
//    }
}
