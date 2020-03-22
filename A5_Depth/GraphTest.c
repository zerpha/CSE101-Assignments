//-----------------------------------------------------------------------------
// Henry Nguyen
// CruzID: hnguye87
// Assignment: pa5
//-----------------------------------------------------------------------------
// Test Client for Graph ADT
//-----------------------------------------------------------------------------
#include<stdlib.h>
#include<stdio.h>
#include "Graph.h"
#include "List.h"

int main()
{
   Graph A = newGraph(6);
   Graph B;
   Graph C;
   List S = newList();

   addEdge(A, 1, 2); //EXAMPLE 3 from Graph Algorithm handout
   addEdge(A, 1 ,3);
   addEdge(A, 2, 4);
   addEdge(A, 2 ,5);
   addEdge(A, 2, 6);
   addEdge(A, 3, 4);
   addEdge(A, 4, 5);
   addArc(A, 5, 6);
   addArc(A, 6, 5);

   printGraph(stdout, A);
   printf("Order: %d Size:%d \n", getOrder(A), getSize(A));
   B = copyGraph(A);
   printGraph(stdout, B);
   printf("\n");
   C = transpose(A);

   for(int i = 1; i < getOrder(A)+1; i++)
	append(S, i);

   DFS(C,S);
   printf("\n");
   printGraph(stdout, C);

   for(int i = 1; i < getOrder(C)+1; i++){
        printf("%d ", getDiscover(C, i));
   }
   printf("\n");
      for(int i = 1; i < getOrder(C)+1; i++){
        printf("%d ", getParent(C, i));
   }
   printf("\n");
      for(int i = 1; i < getOrder(C)+1; i++){
        printf("%d ", getFinish(C, i));
   }
   printf("\n");
   for(moveFront(S); index(S) != -1; moveNext(S))
	printf("%d ", get(S));
   printf("\n");

   freeGraph(&A);
   freeGraph(&B);
   freeGraph(&C);
   freeList(&S);

    return 0;
}
