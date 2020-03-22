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

int main(int argc, char* argv[])
{
   FILE* fp;
   FILE* fq;
   char x[99];
   fp = fopen(argv[1], "r");
   fq = fopen(argv[2], "w");

   fscanf(fp, " %100s", x);
   int G_size = atoi(x);
   Graph A = newGraph(G_size);
   Graph B;
   while(!feof(fp)){
        fscanf(fp, " %100s", x);
        if(atoi(x) == 0){
            fscanf(fp, " %100s", x);
            break;
        }
        int num1 = atoi(x);

        fscanf(fp, " %100s", x);
        int num2 = atoi(x);
        addArc(A, num1, num2);
   }
   List S = newList();
   for(int i = 1; i < getOrder(A) + 1; i++)
        append(S, i);
   DFS(A, S);

   fprintf(fq, "Adjacency list representation of G:\n");
   printGraph(fq, A);
   B = transpose(A);
   DFS(B,S);

   int total = 0;
   for(moveFront(S); index(S) != -1; moveNext(S)){
        if(getParent(B, get(S)) == 0)
            total++;
   }
   fprintf(fq, "\nG contains %d strongly connected components:\n", total);

   List temp = newList();
   int compNum = 1;
   moveBack(S);
   for(moveBack(S); index(S) != -1; movePrev(S)){
        while(index(S) != -1 && getParent(B, get(S)) != 0){
            prepend(temp, get(S));
            movePrev(S);
        }
        prepend(temp, get(S));
        fprintf(fq, "Component %d : ", compNum);
        for(moveFront(temp); index(temp) != -1; moveNext(temp)){
            fprintf(fq, "%d ", get(temp));
        }
        fprintf(fq, "\n");
        clear(temp);
        compNum++;
   }


   fclose(fp);
   fclose(fq); 
  
   freeGraph(&A);
   freeGraph(&B);
   freeList(&S);
   freeList(&temp);

    return 0;
}
