//-----------------------------------------------------------------------------
// Henry Nguyen
// CruzID: hnguye87
// Assignment: pa3
//----------------------------------------------------------------------------
// Arithmetic.c
// Client for BigInteger ADT
//----------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>
#include "List.h"
#include "BigInteger.h"

int main(int argc, char* argv[]){
    if((argv[1] == NULL) || argv[2] == NULL)
		fprintf(stderr, "Error: Didn't call input and/or output file  in the command line");

        FILE* fp;
        FILE* fq;

	int size1;
        int size2;
	fp = fopen(argv[1], "r");
        fq = fopen(argv[2], "w");
	fscanf(fp, "%d", &size1);
        char* c = (char*)malloc(size1 * sizeof(char) +2);
	fscanf(fp, " %100000s", c);
	fscanf(fp, " %d", &size2);
        char* d = (char*)malloc(size2 * sizeof(char) +2);
	fscanf(fp, " %100000s", d);


    BigInteger A = newBigInteger();
    BigInteger B = newBigInteger();

    BigInteger C = stringToBigInteger(c);
    printBigInteger(fq, C);

    BigInteger D = stringToBigInteger(d);
    printBigInteger(fq, D);

    add(A, C, D);
    printBigInteger(fq, A);

    subtract(B, C, D);
    printBigInteger(fq, B);

    subtract(A, C, C);
    printBigInteger(fq, A);

    char e[] = "3";
    BigInteger H = stringToBigInteger(e);
    BigInteger A3 = newBigInteger();
    multiply(A3, C, H);
    char f[] = "2";
    BigInteger I = stringToBigInteger(f);
    BigInteger B2 = newBigInteger();
    multiply(B2, D, I);
    subtract(A, A3, B2);
    printBigInteger(fq, A);

    multiply(A, C, D);
    printBigInteger(fq, A);

    multiply(A, C, C);
    printBigInteger(fq, A);

    multiply(B, D, D);
    printBigInteger(fq, B);

    BigInteger AAAA = newBigInteger();
    multiply(AAAA, A, A); //C^4     reuse from before
    BigInteger BBBB = newBigInteger();
    multiply(BBBB, B, B);
    BigInteger BBBBB = newBigInteger();
    multiply(BBBBB, BBBB, D);// D^5
    char g[] = "9";
    BigInteger M = stringToBigInteger(g);
    BigInteger A94 =newBigInteger();
    multiply(A94, AAAA, M); // 9A^4
    char h[] = "16";
    BigInteger N = stringToBigInteger(h);
    BigInteger B165 = newBigInteger();
    multiply(B165, BBBBB, N); // 16B^5
    add(A, A94, B165); // 9A^4 + 16B^5
    printBigInteger(fq, A);

    free(c);
    free(d);
    freeBigInteger(&A);
    freeBigInteger(&B);
    freeBigInteger(&C);
    freeBigInteger(&D);
    freeBigInteger(&H);
    freeBigInteger(&I);
    freeBigInteger(&A3);
    freeBigInteger(&B2);
    freeBigInteger(&AAAA);
    freeBigInteger(&BBBB);
    freeBigInteger(&BBBBB);
    freeBigInteger(&M);
    freeBigInteger(&A94);
    freeBigInteger(&N);
    freeBigInteger(&B165);
    
    fclose(fp);
    fclose(fq);

    return (0);
}
