//-----------------------------------------------------------------------------
// Henry Nguyen
// CruzID: hnguye87
// Assignment: pa2
//-----------------------------------------------------------------------------
// Matrix.c
// Implementation file for Matrix ADT
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "Matrix.h"
#include "List.h"

// structs --------------------------------------------------------------------

// private EntryObj type
typedef struct EntryObj{
   int row;
   int col;
   double val;
} EntryObj;

// private Entry type
typedef EntryObj* Entry;

// private MatrixtObj type
typedef struct MatrixObj{
   List* listArr;
   int size;
   int nnz;
} MatrixObj;

List* getArr(Matrix m){
    return m->listArr;
}

//getters for Entry
int getRow(Entry e){
    return e->row;
}

int getCol(Entry e){
    return e->col;
}

double getVal(Entry e){
    return e->val;
}

//setters for Entry
void setRow(Entry e, int n){
    e->row = n;
}

void setCol(Entry e, int n){
    e->col = n;
}

void setVal(Entry e, double d){
    e->val = d;
}

//creates and returns a new entry
Entry newEntry(int r, int c, double v){
    Entry e = malloc(sizeof(EntryObj));
    e->row = r;
    e->col = c;
    e->val = v;
    return e;
}

// Returns a reference to a new nXn Matrix object in the zero state.
Matrix newMatrix(int n){
    Matrix M;
    M = malloc(sizeof(MatrixObj) * n);
    M->listArr = malloc(sizeof(MatrixObj) * n);
    for(int i = 0; i < n; i++){
        M->listArr[i] = newList();
    }
    M->size = n;
    M->nnz = 0;
    return(M);
}

//frees Matrix* pM of all allocated memory
void freeMatrix(Matrix* pM){
    if(pM == NULL){
        printf("Called freeMatrix() with a NULL pointer");
        exit(-1);
    }
    List* L = getArr(*pM);
    for(int i = 0; i < size(*pM); i++){
	List li = L[i];
	for(moveFront(li); index(li)!= -1; moveNext(li)){
		free(get(li));
	}
    }    

    for(int i = 0; i < (*pM)->size; i++)
        freeList(&(*pM)->listArr[i]);
    free((*pM)->listArr);
    (*pM)->listArr = NULL;
    free(*pM);
    *pM = NULL;
}

//returns size n of the Matrix nXn
int size(Matrix M){
    if(M == NULL){
        printf("Called size() with a NULL pointer");
        exit(-1);
    }
    return (M->size);
}

//return number of nonzero values in the matrix
int NNZ(Matrix M){
    if(M == NULL){
        printf("Called size() with a NULL pointer");
        exit(-1);
    }
    return (M->nnz);
}

//// Return true (1) if matrices A and B are equal, false (0) otherwise.
int equals(Matrix A, Matrix B){
    if (A == NULL && B == NULL) return 1;
    if (A == NULL || B == NULL) return 0;
    if (A->size != B->size) return 0;
    if (A->nnz != B->nnz) return 0;

    List* AL = getArr(A);
    List* BL = getArr(B);
    if(AL == BL) return 1;
    for(int i = 0; i < size(A); i++){
        List al = AL[i];
        List bl = BL[i];
        moveFront(al);
        moveFront(bl);

        while(index(al)!= -1 && index(bl)!= -1){
            if(getVal(get(al)) != getVal(get(bl))) return 0;
            moveNext(al);
            moveNext(bl);
        }
    }
    return 1;
}

//// Re-sets M to the zero Matrix.
void makeZero(Matrix M)
{
    if(M == NULL){
        printf("Called makeZero() with a NULL pointer");
        exit(-1);
    }
    List* L = getArr(M);
    for(int i = 0; i < size(M); i++){
        List li = L[i];
        clear(li);
    }
    M->nnz = 0;
}

// Changes the ith row, jth column of M to the value x.
// Pre: 1<=i<=size(M), 1<=j<=size(M)
void changeEntry(Matrix M, int i, int j, double x){
    if(M == NULL){
        printf("Called changeEntry() with a NULL pointer");
        exit(-1);
    }
    if(i > size(M) || j > size(M)){
        printf("Matrix error, called changeEntry() when index is more than size");
        exit(-1);
    }
    if(i < 1 || j < 1){
        printf("Matrix error, called changeEntry() when index is less than one");
        exit(-1);
    }
    List* L = getArr(M);
    List l = L[i-1];

    if(isEmpty(l)){
	if(x == 0) return;
        append(l, newEntry(i, j, x));
        M->nnz++;
        return;
    }
    moveFront(l);
    while(index(l)!= -1 && j > getCol(get(l)))
        moveNext(l);

    if(index(l)== -1){
	if(x == 0) return;
        append(l, newEntry(i, j, x));
        M->nnz++;
        return;
    }

    if(j == getCol(get(l))){
       setVal(get(l), x);
       if(x==0){
	 free(get(l));
	 delete(l);
	 M->nnz--;
       }
       return;
    }
    if(x != 0)
       insertBefore(l, newEntry(i, j, x));
    M->nnz++;

}

//// Returns a reference to a new Matrix object having the same entries as A.
Matrix copy(Matrix A){
    if(A == NULL){
        printf("Called copy() with a NULL pointer");
        exit(-1);
    }
    Matrix M = newMatrix(size(A));
    List* L = getArr(A);
    for(int i = 0; i < size(A); i++){
        List li = L[i];
        for(moveFront(li); index(li)!= -1; moveNext(li))
            changeEntry(M, getRow(get(li)), getCol(get(li)), getVal(get(li)));
    }
    return M;
}

// Returns a reference to a new Matrix object representing xA.
Matrix scalarMult(double x, Matrix A){
    if(A == NULL){
        printf("Called scalarMult() with a NULL pointer");
        exit(-1);
    }
    Matrix M = newMatrix(size(A));
    List* AL = getArr(A);
    for(int i = 0; i < size(M); i++){
        List la = AL[i];
        moveFront(la);
        while(index(la) != -1){
            changeEntry(M, getRow(get(la)), getCol(get(la)), (getVal(get(la))*x));
            moveNext(la);
        }
    }
    return M;
}

//// Returns a reference to a new Matrix object representing A+B.
//// pre: size(A)==size(B)
Matrix sum(Matrix A, Matrix B){
    if(A == NULL || B == NULL){
        printf("Called sum() with a NULL pointer");
        exit(-1);
    }
    if(size(A)!=size(B)){
        printf("Matrix error, called sum() when Matrix A and Matrix B are not the same size");
        exit(-1);
    }
    if(getArr(A) == getArr(B)){
        return scalarMult(2, A);
    }
    Matrix M = newMatrix(size(A));
    List* AL = getArr(A);
    List* BL = getArr(B);

    for(int i = 0; i < size(A); i++){
        List la = AL[i];
        List lb = BL[i];
        moveFront(la);
        moveFront(lb);
        while(index(la)!= -1 || index(lb)!= -1){
            if(index(la)!= -1 && index(lb)!= -1){
                if(getCol(get(la)) < getCol(get(lb))){
                    changeEntry(M, getRow(get(la)), getCol(get(la)), getVal(get(la)));
                    moveNext(la);
                    continue;
                }
                if(getCol(get(lb)) < getCol(get(la))){
                    changeEntry(M, getRow(get(lb)), getCol(get(lb)), getVal(get(lb)));
                    moveNext(lb);
                    continue;
                }
                if(getCol(get(la)) == getCol(get(lb))){
                    if((getVal(get(la)) + getVal(get(lb))) != 0)
                        changeEntry(M, getRow(get(la)), getCol(get(la)), (getVal(get(la)) + getVal(get(lb))));
                    moveNext(la);
                    moveNext(lb);
                    continue;
                }
            }
            else if(index(la)!= -1 && index(lb)== -1){
                while(index(la)!= -1){
                    changeEntry(M, getRow(get(la)), getCol(get(la)), getVal(get(la)));
                    moveNext(la);
                }
            }
            else{
                while(index(lb)!= -1){
                    changeEntry(M, getRow(get(lb)), getCol(get(lb)), getVal(get(lb)));
                    moveNext(lb);
                }
            }
        }
    }
    return M;
}

//// Returns a reference to a new Matrix object representing A-B.
//// pre: size(A)==size(B)
Matrix diff(Matrix A, Matrix B){
    if(A == NULL || B == NULL){
        printf("Called diff() with a NULL pointer");
        exit(-1);
    }
    if(size(A)!=size(B)){
        printf("Matrix error, called diff() when Matrix A and Matrix B are not the same size");
        exit(-1);
    }

    Matrix M = newMatrix(size(A));
    List* AL = getArr(A);
    List* BL = getArr(B);
    if(AL == BL) return M;

    for(int i = 0; i < size(A); i++){
        List la = AL[i];
        List lb = BL[i];
        moveFront(la);
        moveFront(lb);
        while(index(la)!= -1 || index(lb)!= -1){
            if(index(la)!= -1 && index(lb)!= -1){
                if(getCol(get(la)) < getCol(get(lb))){
                    changeEntry(M, getRow(get(la)), getCol(get(la)), getVal(get(la)));
                    moveNext(la);
                    continue;
                }
                if(getCol(get(lb)) < getCol(get(la))){
                    changeEntry(M, getRow(get(lb)), getCol(get(lb)), getVal(get(lb))* (-1));
                    moveNext(lb);
                    continue;
                }
                if(getCol(get(la)) == getCol(get(lb))){
                    if((getVal(get(la)) - getVal(get(lb))) != 0)
                        changeEntry(M, getRow(get(la)), getCol(get(la)), (getVal(get(la)) - getVal(get(lb))));
                    moveNext(la);
                    moveNext(lb);
                    continue;

                }
            }
            else if(index(la)!= -1 && index(lb)== -1){
                while(index(la)!= -1){
                    changeEntry(M, getRow(get(la)), getCol(get(la)), getVal(get(la)));
                    moveNext(la);
                }
            }
            else{
                while(index(lb)!= -1){
                    changeEntry(M, getRow(get(lb)), getCol(get(lb)), getVal(get(lb))*(-1));
                    moveNext(lb);
                }
            }
        }
    }
    return M;
}

//// Returns a reference to a new Matrix object representing the transpose of A.
Matrix transpose(Matrix A){
    if(A == NULL){
        printf("Called transpose() with a NULL pointer");
        exit(-1);
    }
    Matrix M = newMatrix(size(A));
    List* L = getArr(A);
    for(int i = 0; i < size(A); i++){
        List li = L[i];
        for(moveFront(li); index(li)!= -1; moveNext(li))
            changeEntry(M, getCol(get(li)), getRow(get(li)), getVal(get(li)));
    }
    return M;
}

//// Returns a reference to a new Matrix object representing AB
//// pre: size(A)==size(B)
Matrix product(Matrix A, Matrix B){
    if(A == NULL || B == NULL){
        printf("Called product() with a NULL pointer");
        exit(-1);
    }
    if(size(A)!=size(B)){
        printf("Matrix error, called product() when Matrix A and Matrix B are not the same size");
        exit(-1);
    }

    double sum = 0;
    Matrix M = newMatrix(size(A));
    Matrix tpose = transpose(B);

    List* L = getArr(A);
    List* L2 = getArr(tpose);

    for(int j = 0; j < size(A); j++){ //moves down the rows of Matrix A
        List la = L[j];
        moveFront(la);
        for(int i = 0; i < size(A); i++){ //moves down the rows of Matrix B
            List lb = L2[i];
            moveFront(lb);
            while(index(la)!= -1 && index(lb)!= -1){ //moves through the list in Matrix A and Matrix B
                if(getCol(get(la)) < getCol(get(lb))){
                    moveNext(la);
                    continue;
                }
                if(getCol(get(la)) > getCol(get(lb))){
                    moveNext(lb);
                    continue;
                }
                if(getCol(get(la)) == getCol(get(lb))){
                    sum = sum + (getVal(get(la)) * getVal(get(lb)));
                    moveNext(la);
                    moveNext(lb);
                    continue;
                }
            }
            if(sum != 0){
                changeEntry(M, j+1, i+1, sum);
                sum = 0;
            }
            moveFront(la);
        }
    }
    freeMatrix(&tpose);
    return M;
}

// Prints a string representation of Matrix M to filestream out. Zero rows
// are not printed. Each non-zero is represented as one line consisting
// of the row number, followed by a colon, a space, then a space separated
// list of pairs "(col, val)" giving the column numbers and non-zero values
// in that row. The double val will be rounded to 1 decimal point.
void printMatrix(FILE* out, Matrix M){
    if(M == NULL){
        printf("Called printMatrix() with a NULL pointer");
        exit(-1);
    }
    if(M->nnz == 0) return;

    bool flag = false;
    List* L = getArr(M);
    for(int i = 0; i < size(M); i++){
        List li = L[i];
        for(moveFront(li); index(li)!= -1; moveNext(li)){
            if(flag == false){
                flag = true;
                fprintf(out, "%d: ",  i+1);
            }
            fprintf(out, "(%d, %.1f) ", getCol(get(li)), getVal(get(li)));

        }
        if(flag == true)
            fprintf(out, " \n");
        flag = false;
    }
}
