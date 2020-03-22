#include<stdlib.h>
#include<stdio.h>
#include"Matrix.h"

int main(int argc, char* argv[]){
	if((argv[1] == NULL) || (argv[2] == NULL))
		fprintf(stderr, "Error: More or less than 2 strings were called in the command line");
	FILE* fp;
	FILE* fq;
	int A_nnz;
	int B_nnz;
	int M_size;
	char x[999];
	fp = fopen(argv[1], "r");
	fscanf(fp, " %100s", x);
	M_size = atoi(x);
	fscanf(fp, " %100s", x);
	A_nnz = atoi(x);
	fscanf(fp, " %100s", x);
	B_nnz = atoi(x);
	Matrix A = newMatrix(M_size);
	Matrix B = newMatrix(M_size);
	for(int i = 0; i < A_nnz; i++){
		if(!feof(fp)){ 
			int row;
			int col;
			double val;
			fscanf(fp, " %100s", x);
			row = atoi(x);
			fscanf(fp, " %100s", x);
			col = atoi(x);
			fscanf(fp, " %100s", x);
			val = atof(x);
			changeEntry(A, row, col, val);
		}	
	}
	for(int i = 0; i < B_nnz; i++){
		if(!feof(fp)){
			int row;
			int col;
			double val;
			fscanf(fp, " %100s", x);
			row = atoi(x);
			fscanf(fp, " %100s", x);
			col = atoi(x);
			fscanf(fp, " %100s", x);
			val = atof(x);
			changeEntry(B, row, col, val);
		}
	}
	fclose(fp);
	
	Matrix C = scalarMult(1.5, A);
	Matrix D = sum(A, B);
	Matrix E = sum(A, A);
	Matrix F = diff(B,A);
	Matrix G = diff(A,A);
	Matrix H = transpose(A);
	Matrix I = product(A, B);
	Matrix J = product(B, B); 
	
	fq = fopen(argv[2], "w");
	fprintf(fq, "A has %d non-zero entries:\n", A_nnz);
	printMatrix(fq, A);
	fprintf(fq, "\nB has %d non-zero entries:\n", B_nnz);
	printMatrix(fq, B);
	fprintf(fq, "\n(1.5)*A = \n");
	printMatrix(fq, C);
	fprintf(fq, "\nA+B = \n");
	printMatrix(fq, D);
	fprintf(fq, "\nA+A = \n");
	printMatrix(fq, E);
	fprintf(fq, "\nB-A = \n");
	printMatrix(fq, F);
	fprintf(fq, "\nA-A = \n");
	printMatrix(fq, G);
	fprintf(fq,"\nTranspose(A) = \n");
	printMatrix(fq, H);
	fprintf(fq,"\nA*B = \n");
	printMatrix(fq, I);
	fprintf(fq,"\nB*B = \n");
	printMatrix(fq, J);
		
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
	fclose(fq);
	return 0;
}
