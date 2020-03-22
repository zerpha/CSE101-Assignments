/***************************************************************************************
 Henry Nguyen
 CruzID: hnguye87
 Assignment: pa2
****************************************************************************************
*  ListTest.c
*  Test client for List ADT
*****************************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include"List.h"

int main(int argc, char* argv[]){

   List A = newList();
   List B = newList();
   int i;

   for(i=1; i<20; i++){
      append(A,i);
   }

   for(moveFront(A); index(A)>=0; moveNext(A)){
      printf("%d ", get(A));
   }
   printf("\n");


   moveFront(A);
   for(i=0; i<5; i++) moveNext(A); // at index 5
   insertBefore(A, 999);            // at index 6
   for(i=0; i<9; i++) moveNext(A); // at index 15
   insertAfter(A, 1000);
   for(i=0; i<5; i++) movePrev(A); // at index 10
   delete(A);

   moveFront(A);
   insertAfter(A, 500);
   insertBefore(A, 400);
   moveBack(A);
   insertAfter(A, 700);
   insertBefore(A, 600);


   for(moveFront(A); index(A)>=0; moveNext(A)){
      printf("%d ", get(A));
   }
   printf("\n");
   printf("Front Element: %d\n", front(A));
   printf("Back Element: %d\n", back(A));
   deleteFront(A);
   deleteBack(A);
   printf("Front Element: %d\n", front(A));
   printf("Back Element: %d\n", back(A));
   printf("%d\n", length(A));
   clear(A);
   printf("%d\n", length(A));

    for(i=1; i<20; i++){
      prepend(B,"l");
   }

   for(moveFront(B); index(B)>=0; moveNext(B)){
      printf("%s", get(B));
   }
   printf("\n");


   moveFront(B);
   for(i=0; i<5; i++) moveNext(B); // at index 5
   insertBefore(B, "O");            // at index 6
   for(i=0; i<9; i++) moveNext(B); // at index 15
   insertAfter(B, "O");


   for(moveBack(B); index(B)!=-1; movePrev(B)){
      printf("%s ", get(B));
   }
   printf("\n");
   printf("%d\n", isEmpty(B));
   clear(B);
   printf("%d\n", isEmpty(B));

   freeList(&A);
   freeList(&B);

   return(0);
}

/*
Output of this program:
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
false
false
true
1 2 3 4 5 -1 6 7 8 9 11 12 13 14 15 -2 16 17 18 19 20
21
0
*/
