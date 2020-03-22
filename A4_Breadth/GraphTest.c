//-----------------------------------------------------------------------------
// Henry Nguyen
// CruzID: hnguye87
// Assignment: pa4
//-----------------------------------------------------------------------------
// Test Client for Graph ADT
//-----------------------------------------------------------------------------

#include<stdlib.h>
#include<stdio.h>
#include "Graph.h"
#include "List.h"

int main(int argc, char* argv[]){

   Graph A = newGraph(6);
   addEdge(A, 1, 2);
   addEdge(A, 1, 3);
   addEdge(A, 1, 4);
   addEdge(A, 1, 5);
   addArc(A, 6, 1);
   addArc(A, 6, 2);
   addArc(A, 6, 3);
   addArc(A, 6, 4);
   addArc(A, 6, 5);

   printGraph(stdout, A);

   BFS(A, 1);
   printf("Order: %d\n Size: %d\n Source: ", getOrder(A), getSize(A), getSource(A));
   for(int i = 1; i < getOrder(A)+1; i++){
        printf("%d ", getParent(A, i));
   }
   printf("\n");
    for(int i = 1; i < getOrder(A)+1; i++){
        printf("%d ", getDist(A, i));
   }
   printf("\n");

   List X = newList();
   getPath(X, A, 6);
   printList(stdout, X);
   makeNull(A);
   printGraph(stdout, A);

   freeList(&X);
   freeGraph(&A);


    return(0);
}
