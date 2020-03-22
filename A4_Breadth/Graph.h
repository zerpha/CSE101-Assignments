//-----------------------------------------------------------------------------
// Henry Nguyen
// CruzID: hnguye87
// Assignment: pa4
//-----------------------------------------------------------------------------
// Graph.h
// Header file for Graph ADT
//-----------------------------------------------------------------------------
#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED
#include <stdio.h>
#include "List.h"
#define INF -1
#define NIL 0

typedef struct GraphObj* Graph;

/*** Constructors-Destructors ***/
Graph newGraph(int n);
void freeGraph(Graph* pG);
/** Access functions **/
int getOrder(Graph G); //number of vertex
int getSize(Graph G); //number of edges
int getSource(Graph G);
int getParent(Graph G, int u);
int getDist(Graph G, int u);
void getPath(List L, Graph G, int u);
/** Manipulation procedures **/
void makeNull(Graph G);
void addEdge(Graph G, int u, int v); //add edge
void addArc(Graph G, int u, int v); //add directed edge
void BFS(Graph G, int s);
/*** Other operations ***/
void printGraph(FILE* out, Graph G);



#endif // MATRIX_H_INCLUDED
