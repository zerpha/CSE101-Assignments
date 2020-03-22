//-----------------------------------------------------------------------------
// Henry Nguyen
// CruzID: hnguye87
// Assignment: pa2
//-----------------------------------------------------------------------------
// MatrixTest.c
// Test Client for Matrix ADT
//-----------------------------------------------------------------------------

#include<stdlib.h>
#include<stdio.h>
#include "Matrix.h"


int main(int argc, char* argv[]){

    int n=3;
   Matrix A = newMatrix(n);
   Matrix B = newMatrix(n);
   Matrix C, D, E, F, G, H, I, J, K;

   changeEntry(A, 1,1,1); changeEntry(B, 1,1,1);
   changeEntry(A, 1,2,2); changeEntry(B, 1,2,0);
   changeEntry(A, 1,3,3); changeEntry(B, 1,3,1);
   changeEntry(A, 2,1,4); changeEntry(B, 2,1,0);
   changeEntry(A, 2,2,5); changeEntry(B, 2,2,1);
   changeEntry(A, 2,3,6); changeEntry(B, 2,3,0);
   changeEntry(A, 3,1,7); changeEntry(B, 3,1,1);
   changeEntry(A, 3,2,8); changeEntry(B, 3,2,1);
   changeEntry(A, 3,3,9); changeEntry(B, 3,3,1);
   changeEntry(A, 3,1,7); changeEntry(B, 3,1,0);
   changeEntry(A, 3,2,8); changeEntry(B, 3,2,5);
   changeEntry(A, 3,3,4); changeEntry(B, 3,3,0);
   printf("A: %d\n", NNZ(A));
   printMatrix(stdout, A);
   printf("\n");

   printf("B: %d\n", NNZ(B));
   printMatrix(stdout, B);
   printf("\n");

   C = scalarMult(1.5, A);
   printf("A*1.5: %d\n", NNZ(C));
   printMatrix(stdout, C);
   printf("\n");

   D = sum(A, B);
   printf("A+B: %d\n", NNZ(D));
   printMatrix(stdout, D);
   printf("\n");

   I = sum(B, B);
   printf("B+B: %d\n", NNZ(I));
   printMatrix(stdout, I);
   printf("\n");

   E = diff(A, A);
   printf("A-A: %d\n", NNZ(E));
   printMatrix(stdout, E);
   printf("\n");

   J = diff(A, B);
   printf("A-B: %d\n", NNZ(J));
   printMatrix(stdout, J);
   printf("\n");

   F = transpose(B);
   printf("Transpose B: %d\n", NNZ(F));
   printMatrix(stdout, F);
   printf("\n");

   K = product(A, B);
   printf("A*B: %d\n", NNZ(K));
   printMatrix(stdout, K);
   printf("\n");

   G = product(B, B);
   printf("B*B: %d\n", NNZ(G));
   printMatrix(stdout, G);
   printf("\n");

   H = copy(A);
   printf("Copy A: %d\n", NNZ(H));
   printMatrix(stdout, H);
   printf("\n");

   printf("%s\n", equals(A, H)?"true":"false" );
   printf("%s\n", equals(A, B)?"true":"false" );
   printf("%s\n", equals(A, A)?"true":"false" );

   makeZero(A);
   printf("MakeZero A: %d\n", NNZ(A));
   printMatrix(stdout, A);

   freeMatrix(&A);
   freeMatrix(&B);
   freeMatrix(&C);
   freeMatrix(&D);
   freeMatrix(&E);
   freeMatrix(&F);
   freeMatrix(&G);
   freeMatrix(&H);
   freeMatrix(&I);
   freeMatrix(&J);
   freeMatrix(&K);

   return EXIT_SUCCESS;
}
