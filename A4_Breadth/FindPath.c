//-----------------------------------------------------------------------------
// Henry Nguyen
// CruzID: hnguye87
// Assignment: pa4
//-----------------------------------------------------------------------------
// FindPath.c
// Main Client for pa4
//-----------------------------------------------------------------------------

#include<stdlib.h>
#include<stdio.h>
#include "Graph.h"
#include "List.h"

int main(int argc, char* argv[]){
   FILE* fp;
   FILE* fq;
   char x[99];
   fp = fopen(argv[1], "r");
   fq = fopen(argv[2], "w");
   fscanf(fp, " %100s", x);
   int G_size = atoi(x);
   Graph A = newGraph(G_size);
   while(!feof(fp)){
        fscanf(fp, " %100s", x);
        if(atoi(x) == 0){
            fscanf(fp, " %100s", x);
            break;
        }
        int num1 = atoi(x);

        fscanf(fp, " %100s", x);
        int num2 = atoi(x);
        addEdge(A, num1, num2);
   }

   printGraph(fq, A);
   fprintf(fq,"\n");
   List X = newList();

    while(!feof(fp)){
        fscanf(fp, " %100s", x);
        if(atoi(x) == 0) break;
        int num1 = atoi(x);
        BFS(A, num1);

        fscanf(fp, " %100s", x);
        int num2 = atoi(x);
        getPath(X, A, num2);
        fprintf(fq,"The distance from %d to %d is ", num1, num2);
        if(front(X) == 0){
           fprintf(fq, "infinity\n");
        }
        else{
            fprintf(fq,"%d\n", length(X)-1);
        }

        if(front(X) == 0){
            fprintf(fq, "No %d-%d path exists\n\n", num1, num2);
        }
        else{
            fprintf(fq,"A shortest %d-%d path is: ", num1, num2);
            printList(fq, X);
            fprintf(fq,"\n\n");
        }
        clear(X);
   }

   freeList(&X);
   freeGraph(&A);

   fclose(fp);
   fclose(fq);
    return(0);
}
