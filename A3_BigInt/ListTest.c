/***************************************************************************************
 Henry Nguyen
 CruzID: hnguye87
 Assignment: pa3
****************************************************************************************
*  ListClient.c
*  Test client for List ADT
*****************************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include"List.h"

int main(int argc, char* argv[]){

   List A = newList();
   List B = newList();
   List C = NULL;
   long i;

   for(i=1; i<=20; i++){
      append(A,i);
      prepend(B,i);
   }

   printList(stdout,A);
   printf("\n");
   printList(stdout,B);
   printf("\n");

   for(moveFront(A); index(A)>=0; moveNext(A)){
      printf("%d ", get(A));
   }
   printf("\n");
   for(moveBack(B); index(B)>=0; movePrev(B)){
      printf("%d ", get(B));
   }
   printf("\n");

   C = copyList(A);

   moveFront(A);
   for(i=0; i<5; i++) moveNext(A); // at index 5
   insertBefore(A, -1);            // at index 6
   for(i=0; i<9; i++) moveNext(A); // at index 15
   insertAfter(A, -2);
   for(i=0; i<5; i++) movePrev(A); // at index 10
   delete(A);
   printList(stdout,A);
   printf("\n");
   moveFront(A);
   for(i=0; i<5; i++) moveNext(A); // at index 5
   set(A, -2000000000);
   for(i=0; i<10; i++) moveNext(A); // at index 15
   set(A, 2000000000);
   for(i=0; i<5; i++) movePrev(A); // at index 10
   set(A, -2111111111);
   printList(stdout,A);
   printf("\n");
   printf("%d\n", length(A));
   clear(A);
   printf("%d\n", length(A));

   freeList(&A);
   freeList(&B);
   freeList(&C);

   return(0);
}

/*
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20

20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1

1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
1 2 3 4 5 -1 6 7 8 9 11 12 13 14 15 -2 16 17 18 19 20

1 2 3 4 5 -2000000000 6 7 8 9 -2111111111 12 13 14 15 2000000000 16 17 18 19 20

21 0
*/
