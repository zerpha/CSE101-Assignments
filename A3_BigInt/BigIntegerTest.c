//-----------------------------------------------------------------------------
// Henry Nguyen
// CruzID: hnguye87
// Assignment: pa3
//-----------------------------------------------------------------------------
// BigIntegerTest.c
// Test Client for BigInteger ADT
//-----------------------------------------------------------------------------
#include <stdlib.h>
#include <stdio.h>
#include "List.h"
#include "BigInteger.h"

int main(int argc, char* argv[]){
	
    char a[] = "94353454543534588888888";
    BigInteger A = stringToBigInteger(a);
    BigInteger B = copy(A);
    printf("%d", sign(A));
    printf("\n%d\n", compare(A, B));
    printf("%d\n", equals(B, B));
    printBigInteger(stdout, A);
    printf("\n");
    printBigInteger(stdout, B);
    printf("\n");
    makeZero(A);
    printBigInteger(stdout, A);
    printf("\n");

    char c[] = "-0041085449";
    BigInteger C = stringToBigInteger(c);
    printBigInteger(stdout, C);
    printf("\n");

    char d[] = "-702779357";
    BigInteger D = stringToBigInteger(d);
    printBigInteger(stdout, D);
    printf("\n");

    add(A, C, D);
    printf("C+D\n");
    printBigInteger(stdout, A);
    BigInteger E = sum(C, D);
    printf("\n");
    printBigInteger(stdout, E);

    printf("\n");

    subtract(B, C, D);
    printf("C-D\n");
    printBigInteger(stdout, B);
    BigInteger F = diff(C, D);
    printf("\n");
    printBigInteger(stdout, F);
    BigInteger G = diff(C, C);
    printf("\nC-C\n");
    printBigInteger(stdout, G);
    printf("\n");

    printf("C*D\n");
    multiply(A, C, D);
    printBigInteger(stdout, A);
    printf("\n");
    BigInteger H = prod(C, D);
    printBigInteger(stdout, H);
    printf("\n");


    printf("\nC*C\n");
    multiply(A, C, C);
    printBigInteger(stdout, A);
    printf("\n");
    BigInteger I = prod(C, C);
    printBigInteger(stdout, I);
    printf("\n");

    printf("\nD*D\n");
    multiply(B, D, D);
    printBigInteger(stdout, B);
    printf("\n");
    BigInteger J = prod(D, D);
    printBigInteger(stdout, J);
    printf("\n\n");

    freeBigInteger(&A);
    freeBigInteger(&B);
    freeBigInteger(&C);
    freeBigInteger(&D);
    freeBigInteger(&E);
    freeBigInteger(&F);
    freeBigInteger(&G);
    freeBigInteger(&H);
    freeBigInteger(&I);
    freeBigInteger(&J);


    return (0);
}

