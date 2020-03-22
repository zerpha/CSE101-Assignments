//-----------------------------------------------------------------------------
// Henry Nguyen
// CruzID: hnguye87
// Assignment: pa3
//-----------------------------------------------------------------------------
// BigInteger.c
// Implementation file for BigInteger ADT
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include "BigInteger.h"
#include "List.h"

//global variables
long base = 1000000000;
int power = 9;

// structs --------------------------------------------------------------------

// private BigIntegerObj type
typedef struct BigIntegerObj{
    int sign; //specify sign (1, 0, -1)
    List list;
} BigIntegerObj;

List getList(BigInteger B){
    if(B == NULL){
        printf("BigInteger Error: called getList with NULL BigInteger");
        exit(-1);
    }
    return B->list;
}

// Returns a reference to a new BigInteger object in the zero state.
BigInteger newBigInteger(){
    BigInteger b;
    b = malloc(sizeof(BigIntegerObj));
    b->list = newList();
    b->sign = 0;
    return b;
}

// Frees heap memory associated with *pN, sets *pN to NULL.
void freeBigInteger(BigInteger* pN){
    if(*pN == NULL){
        return;
    }
    freeList(&(*pN)->list);
    free(*pN);
    *pN = NULL;
}

// Access functions -----------------------------------------------------------

// Returns -1 if N is negative, 1 if N is positive, and 0 if N is in the zero state.

int sign(BigInteger N){
    if(N == NULL){
        printf("BigInteger Error: called sign() on a NULL BigInteger");
        exit(-1);
    }
    return (N->sign);
}

//// Returns -1 if A<B, 1 if A>B, and 0 if A=B.
int compare(BigInteger A, BigInteger B){
    if(A == NULL || B == NULL){
        printf("Big Integer ADT Error: Called compare() when either A or B BigInteger is NULL");
        exit(-1);
    }

    if(A->list == B->list) return 0;

    if(A->sign > B->sign) return 1;
    if(A->sign < B->sign) return -1;
    if(A->sign == 0 && B->sign == 0) return 0;

    if(A->sign == 1 && B->sign == 1){
        if(length(A->list) > length(B->list)) return 1;
        if(length(A->list) < length(B->list)) return -1;
    }
    if(A->sign == -1 && B->sign == -1){
        if(length(A->list) > length(B->list)) return -1;
        if(length(A->list) < length(B->list)) return 1;
    }

    moveFront(A->list);
    moveFront(B->list);
    while(index(A->list) != -1 && index(B->list) != -1){
        if(A->sign == 1 && B->sign == 1){
            if(get(A->list) > get(B->list)) return 1;
            if(get(A->list) < get(B->list)) return -1;
        }
        if(A->sign == -1 && B->sign == -1){
            if(get(A->list) > get(B->list)) return -1;
            if(get(A->list) < get(B->list)) return 1;
        }
        moveNext(A->list);
        moveNext(B->list);
    }
    return 0;
}

//// Return true (1) if A and B are equal, false (0) otherwise.
int equals(BigInteger A, BigInteger B){
    if(A == NULL || B == NULL){
        printf("Big Integer ADT Error: Called equals() when either A or B BigInteger is NULL");
        exit(-1);
    }

    if(A->list == B->list) return 1;

    if(A->sign == 0 && B->sign == 0) return 1;
    if(A->sign != B->sign) return 0;
    if(length(A->list) != length(B->list)) return 0;

    moveFront(A->list);
    moveFront(B->list);
    while(index(A->list) != -1 && index(B->list) != -1){
        if(get(A->list) != get(B->list)) return 0;
        moveNext(A->list);
        moveNext(B->list);
    }
    return 1;
}
//// Manipulation procedures ----------------------------------------------------

//// Re-sets N to the zero state.
void makeZero(BigInteger N){
    if(N == NULL){
        printf("BigInteger Error: called makeZero() on a NULL BigInteger");
        exit(-1);
    }
    clear(N->list);
    N->sign = 0;
}

//// Reverses the sign of N: positive <--> negative. Does nothing if N is in the
//// zero state.
void negate(BigInteger N){
    if(N == NULL){
        printf("BigInteger Error: called negate() on a NULL BigInteger");
        exit(-1);
    }
    N->sign = ((N->sign) * (-1));
}

// BigInteger Arithmetic operations -----------------------------------------------

//// Returns a reference to a new BigInteger object representing the decimal integer
//// represented in base 10 by the string s.
//// Pre: s is a non-empty string containing only base ten digits {0,1,2,3,4,5,6,7,8,9}
//// and an optional sign {+, -} prefix.
BigInteger stringToBigInteger(char* s){
    char* ss = s; //keep a copy of s
    int numsize = 0; //number of digits in the num
    if(sizeof(s) == 0){
        printf("BigInteger Error: called stringToBigInteger() with a empty string");
        exit(-1);
    }
    if(s[0] != '+' && s[0] != '-' && !isdigit(s[0])){
        printf("BigInteger Error: called stringToBigInteger() with a string containing not '+', '-', or base ten digit");
        exit(-1);
    }
    if(isdigit(s[0]))numsize++;
    *s++;
    while(*s){
        numsize++;
        if(!isdigit(*s++)){
            printf("BigInteger Error: called stringToBigInteger() with a string containing not '+', '-', or base ten digits");
            exit(-1);
        }
    }

    BigInteger b = newBigInteger();
    if(ss[0] == '-')
        b->sign = -1;
    else
        b->sign = 1;

    int leftover = numsize%power;
    int times = numsize/power;

    if(ss[0] == '+' || ss[0] == '-') *ss++;

    long l = 0;
    for(int i = 0; i < leftover; i++){
        long POW = 1;
        for(int j = 0; j < leftover-1; j++){
           POW = POW * 10;
        }
        for(int j = 0; j < i; j++){
           POW = POW / 10;
        }
        l = l + ((ss[0] - '0') * POW);
        *ss++;
    }
    append(b->list, l);

    for(int z = 0; z < times; z++){
        l = 0;
        for(int i = 0; i < power; i++){
            long POW = 1;
            for(int j = 0; j < power-1; j++){
               POW = POW * 10;
            }
            for(int j = 0; j < i; j++){
               POW = POW / 10;
            }
            l = l + ((ss[0] - '0') * POW);
            *ss++;
        }
        append(b->list, l);
    }

    moveFront(b->list);
    while(!isEmpty(b->list) && get(b->list) == 0){
        deleteFront(b->list);
        moveFront(b->list);
    }
    if(isEmpty(b->list))
        b->sign = 0;

    return b;
}

//// Returns a reference to a new BigInteger object in the same state as N.
BigInteger copy(BigInteger N){
    if(N == NULL){
        printf("BigInteger Error: called copy() on a NULL BigInteger");
        exit(-1);
    }
    BigInteger copy = newBigInteger();
    copy->sign = N->sign;
    freeList(&(copy->list));
    copy->list = NULL;
    copy->list = copyList(N->list);
    return copy;
}

//// Places the sum of A and B in the existing BigInteger S, overwriting its
//// current state: S = A + B
void add(BigInteger S, BigInteger AA, BigInteger BB){
    if(S == NULL || AA == NULL || BB == NULL){
        printf("BigInteger Error: called add() with a NULL BigInteger");
        exit(-1);
    }

    if(AA->sign == 0 && BB->sign == 0){
        makeZero(S);
        return;
    }
	
    BigInteger A = copy(AA);
    BigInteger B = copy(BB);

    int carryover = 0;
    makeZero(S);
    if(A->sign == 0 && B->sign != 0){
        free(S->list);
        S->list = copyList(B->list);
        S->sign = B->sign;
    }
    if(B->sign == 0 && A->sign != 0){
        free(S->list);
        S->list = copyList(A->list);
        S->sign = A->sign;
    }

    moveBack(A->list);
    moveBack(B->list);
    if(A->sign == B->sign){
        S->sign = A->sign;
        while(index(A->list) != -1 && index(B->list) != -1){
            long long i = (get(A->list)) + (get(B->list)) + carryover;
            if(i > base){
                long long i2 = (i/base) * base;
                long long i3 = i - i2; //remainder
                prepend(S->list, (long)i3);
                carryover = 1;
            }
            else{
                prepend(S->list, (long)i);
                carryover = 0;
            }
            movePrev(A->list);
            movePrev(B->list);
        }
        if(index(A->list) == -1 && index(B->list) != -1){
            while(index(B->list) != -1){
                prepend(S->list, get(B->list) + carryover);
                carryover = 0;
                movePrev(B->list);
            }
        }
        if(index(A->list) != -1 && index(B->list) == -1){
            while(index(A->list) != -1){
                prepend(S->list, get(A->list) + carryover);
                carryover = 0;
                movePrev(A->list);
            }
        }
    }
    else if(A->sign == 1 && B->sign == -1){
        negate(B);
        if(compare(A, B) == -1){
            subtract(S, B, A);
            S->sign = -1;
            negate(B);
        }
        else if(compare(A, B) == 1){
            subtract(S, A, B);
            S->sign = 1;
            negate(B);
        }
        else{
            negate(B);
            freeBigInteger(&A);
            freeBigInteger(&B);
            return;
        }
    }
    else if(A->sign == -1 && B->sign == 1){
        negate(A);
        if(compare(B, A) == -1){
            subtract(S, A, B);
            S->sign = -1;
            negate(A);
        }
        else if(compare(B, A) == 1){
            subtract(S, B, A);
            S->sign = 1;
            negate(A);
        }
        else{
            negate(A);
            freeBigInteger(&A);
            freeBigInteger(&B);
            return;
        }
    }

    freeBigInteger(&A);
    freeBigInteger(&B);
}

//// Returns a reference to a new BigInteger object representing A + B.
BigInteger sum(BigInteger AA, BigInteger BB){
    if(AA == NULL || BB == NULL){
        printf("BigInteger Error: called sum() with a NULL BigInteger");
        exit(-1);
    }
    BigInteger S = newBigInteger();

    if(AA->sign == 0 && BB->sign == 0){
        return S;
    }

    if(AA->sign == 0 && BB->sign != 0){
        free(S->list);
        S->list = copyList(BB->list);
        S->sign = BB->sign;
    }
    if(BB->sign == 0 && AA->sign != 0){
        free(S->list);
        S->list = copyList(AA->list);
        S->sign = AA->sign;
    }

    BigInteger A = copy(AA);
    BigInteger B = copy(BB);
	
    int carryover = 0;
    moveBack(A->list);
    moveBack(B->list);
    if(A->sign == B->sign){
        S->sign = A->sign;
        while(index(A->list) != -1 && index(B->list) != -1){
            long long i = (get(A->list)) + (get(B->list)) + carryover;
            if(i > base){
                long long i2 = (i/base) * base;
                long long i3 = i - i2; //remainder
                prepend(S->list, (long)i3);
                carryover = 1;
            }
            else{
                prepend(S->list, (long)i);
                carryover = 0;
            }
            movePrev(A->list);
            movePrev(B->list);
        }
        if(index(A->list) == -1 && index(B->list) != -1){
            while(index(B->list) != -1){
                prepend(S->list, get(B->list) + carryover);
                carryover = 0;
                movePrev(B->list);
            }
        }
        if(index(A->list) != -1 && index(B->list) == -1){
            while(index(A->list) != -1){
                prepend(S->list, get(A->list) + carryover);
                carryover = 0;
                movePrev(A->list);
            }
        }
    }
    else if(A->sign == 1 && B->sign == -1){
        negate(B);
        if(compare(A, B) == -1){
            subtract(S, B, A);
            S->sign = -1;
            negate(B);
        }
        else if(compare(A, B) == 1){
            subtract(S, A, B);
            S->sign = 1;
            negate(B);
        }
        else{ // B-A=0
            negate(B);
            freeBigInteger(&A);
            freeBigInteger(&B);
            return S;
        }
    }
    else if(A->sign == -1 && B->sign == 1){
        negate(A);
        if(compare(B, A) == -1){
            subtract(S, A, B);
            S->sign = -1;
            negate(A);
        }
        else if(compare(B, A) == 1){
            subtract(S, B, A);
            S->sign = 1;
            negate(A);
        }
        else{
            negate(A);
            freeBigInteger(&A);
            freeBigInteger(&B);
            return S;
        }
    }

    freeBigInteger(&A);
    freeBigInteger(&B);
    return S;
}

// Places the difference of A and B in the existing BigInteger D, overwriting
// its current state: D = A - B
void subtract(BigInteger D, BigInteger AA, BigInteger BB){
    if(D == NULL || AA == NULL || BB == NULL){
        printf("BigInteger Error: called subtract() with a NULL BigInteger");
        exit(-1);
    }

    BigInteger A;
    BigInteger B;
    if(equals(AA, BB)){
        makeZero(D);
        return;
    }

    if(AA->sign == 0 && BB->sign != 0){
        makeZero(D);
        free(D->list);
        D->list = copyList(BB->list);
        D->sign = (BB->sign) * (-1);
    }
    if(BB->sign == 0 && AA->sign != 0){
        makeZero(D);
        free(D->list);
        D->list = copyList(AA->list);
        D->sign = (AA->sign) * (-1);
    }

    if(AA->sign != BB->sign){
        negate(BB);
        makeZero(D);
        add(D, AA, BB);
        negate(BB);
        return;
    }

    if(AA->sign == 1 && BB->sign == 1){
        if(compare(AA, BB) == 1){
            A = copy(AA);
            B = copy(BB);
            makeZero(D);
            D->sign = 1;
        }
        else if(compare(AA, BB) == -1){
            A = copy(BB);
            B = copy(AA);
            makeZero(D);
            D->sign = -1;
        }
    }
    else if(AA->sign == -1 && BB->sign == -1){
        if(compare(AA, BB) == 1){
            A = copy(BB);
            B = copy(AA);
            makeZero(D);
            D->sign = 1;
        }
        else if(compare(AA, BB) == -1){
            A = copy(AA);
            B = copy(BB);
            makeZero(D);
            D->sign = -1;
        }
    }

    int carryover = 0;
    moveBack(A->list);
    moveBack(B->list);

    while(index(A->list) != -1 && index(B->list) != -1){
        double i = (get(A->list)) - (get(B->list)) + carryover;
        if(i < 0){
            prepend(D->list, (long)(i+base));
            carryover = -1;
        }
        else{
            prepend(D->list, (long)i);
            carryover = 0;
        }
        movePrev(A->list);
        movePrev(B->list);
    }
    if(index(A->list) == -1 && index(B->list) != -1){
        while(index(B->list) != -1){
            prepend(D->list, get(B->list) + carryover);
            carryover = 0;
            movePrev(B->list);
        }
    }
    if(index(A->list) != -1 && index(B->list) == -1){
        while(index(A->list) != -1){
            prepend(D->list, get(A->list) + carryover);
            carryover = 0;
            movePrev(A->list);
        }
    }

    freeBigInteger(&A);
    freeBigInteger(&B);
}

//// Returns a reference to a new BigInteger object representing A - B.
BigInteger diff(BigInteger AA, BigInteger BB){
    if(AA == NULL || BB == NULL){
        printf("BigInteger Error: called diff() with a NULL BigInteger");
        exit(-1);
    }
    BigInteger D = newBigInteger();
    BigInteger A;
    BigInteger B;
    if(equals(AA, BB)){
        return D;
    }

    if(AA->sign == 0 && BB->sign != 0){
        free(D->list);
        D->list = copyList(BB->list);
        D->sign = (BB->sign) * (-1);
    }
    if(BB->sign == 0 && AA->sign != 0){
        free(D->list);
        D->list = copyList(AA->list);
        D->sign = (AA->sign) * (-1);
    }

    if(AA->sign != BB->sign){
        negate(BB);
        add(D, AA, BB);
        negate(BB);
        return D;
    }

    if(AA->sign == 1 && BB->sign == 1){
        if(compare(AA, BB) == 1){
            A = copy(AA);
            B = copy(BB);
            D->sign = 1;
        }
        else if(compare(AA, BB) == -1){
            A = copy(BB);
            B = copy(AA);
            D->sign = -1;
        }
    }
    else if(AA->sign == -1 && BB->sign == -1){
        if(compare(AA, BB) == 1){
            A = copy(BB);
            B = copy(AA);
            D->sign = 1;
        }
        else if(compare(AA, BB) == -1){
            A = copy(AA);
            B = copy(BB);
            D->sign = -1;
        }
    }

    int carryover = 0;
    moveBack(A->list);
    moveBack(B->list);

    while(index(A->list) != -1 && index(B->list) != -1){
        double i = (get(A->list)) - (get(B->list)) + carryover;
        if(i < 0){
            prepend(D->list, (long)(i+base));
            carryover = -1;
        }
        else{
            prepend(D->list, (long)i);
            carryover = 0;
        }
        movePrev(A->list);
        movePrev(B->list);
    }
    if(index(A->list) == -1 && index(B->list) != -1){
        while(index(B->list) != -1){
            prepend(D->list, get(B->list) + carryover);
            carryover = 0;
            movePrev(B->list);
        }
    }
    if(index(A->list) != -1 && index(B->list) == -1){
        while(index(A->list) != -1){
            prepend(D->list, get(A->list) + carryover);
            carryover = 0;
            movePrev(A->list);
        }
    }

    freeBigInteger(&A);
    freeBigInteger(&B);
    return D;
}

//// Places the product of A and B in the existing BigInteger P, overwriting
//// its current state: P = A*B
void multiply(BigInteger P, BigInteger AA, BigInteger BB){
    if(P == NULL || AA == NULL || BB == NULL){
        printf("BigInteger Error: called multiply() with a NULL BigInteger");
        exit(-1);
    }
    makeZero(P);
    if(AA->sign == 0 || BB->sign == 0) return;

    if(AA->sign != BB->sign)
        P->sign = -1;
    else
        P->sign = 1;

    BigInteger A;
    BigInteger B;

    if(AA->sign == 1 && BB->sign == -1){
        negate(BB);
        if(compare(AA, BB) == 1){
            A = copy(AA);
            B = copy(BB);
        }
        else{
            A = copy(BB);
            B = copy(AA);
        }
        negate(BB);
    }
    else if(AA->sign == -1 && BB->sign == 1){
            negate(AA);
        if(compare(AA, BB) == 1){
            A = copy(AA);
            B = copy(BB);
        }
        else{
            A = copy(BB);
            B = copy(AA);
        }
        negate(AA);
    }
    else if(AA->sign == -1 && BB->sign == -1){
        if(compare(AA, BB) == -1){
            A = copy(AA);
            B = copy(BB);
        }
        else{
            A = copy(BB);
            B = copy(AA);
        }
    }
    else{
        if(compare(AA, BB) == 1){
            A = copy(AA);
            B = copy(BB);
        }
        else{
            A = copy(BB);
            B = copy(AA);
        }
    }

    BigInteger X = newBigInteger();
    int ind = 0;

    moveBack(B->list);

    while(index(B->list) != -1){
        long long carryover = 0;
        moveBack(A->list);
        X->sign = P->sign;
        for(int j = 0; j < ind; j++){
            prepend(X->list, 0);
        }
        while(index(A->list) != -1){
            long long i = ((long long)get(A->list) * (long long)get(B->list)) + carryover;
            if(i > base){
                long long i2 = (i/base) * base;
                long long i3 = i - i2; //remainder
                prepend(X->list, i3);
                i = i - i3;
                i = i / base;
                carryover = i;
            }
            else{
                prepend(X->list, (long)i);
                carryover = 0;
            }
            movePrev(A->list);
        }
        if(carryover != 0){
            prepend(X->list, carryover);
        }

        add(P, P, X);
        makeZero(X);
        ind++;
        movePrev(B->list);
    }

    freeBigInteger(&X);
    freeBigInteger(&A);
    freeBigInteger(&B);
}

//// Returns a reference to a new BigInteger object representing A*B
BigInteger prod(BigInteger AA, BigInteger BB){
    if(AA == NULL || BB == NULL){
        printf("BigInteger Error: called prod() with a NULL BigInteger");
        exit(-1);
    }
    BigInteger P = newBigInteger();

    if(AA->sign == 0 || BB->sign == 0) return P;

    if(AA->sign != BB->sign)
        P->sign = -1;
    else
        P->sign = 1;

    BigInteger A;
    BigInteger B;

    if(AA->sign == 1 && BB->sign == -1){
        negate(BB);
        if(compare(AA, BB) == 1){
            A = copy(AA);
            B = copy(BB);
        }
        else{
            A = copy(BB);
            B = copy(AA);
        }
        negate(BB);
    }
    else if(AA->sign == -1 && BB->sign == 1){
            negate(AA);
        if(compare(AA, BB) == 1){
            A = copy(AA);
            B = copy(BB);
        }
        else{
            A = copy(BB);
            B = copy(AA);
        }
        negate(AA);
    }
    else if(AA->sign == -1 && BB->sign == -1){
        if(compare(AA, BB) == -1){
            A = copy(AA);
            B = copy(BB);
        }
        else{
            A = copy(BB);
            B = copy(AA);
        }
    }
    else{
        if(compare(AA, BB) == 1){
            A = copy(AA);
            B = copy(BB);
        }
        else{
            A = copy(BB);
            B = copy(AA);
        }
    }

    BigInteger X = newBigInteger();
    int ind = 0;

    moveBack(B->list);

    while(index(B->list) != -1){
        long long carryover = 0;
        moveBack(A->list);
        X->sign = P->sign;
        for(int j = 0; j < ind; j++){
            prepend(X->list, 0);
        }
        while(index(A->list) != -1){
            long long i = ((long long)get(A->list) * (long long)get(B->list)) + carryover;
            if(i > base){
                long long i2 = (i/base) * base;
                long long i3 = i - i2; //remainder
                prepend(X->list, i3);
                i = i - i3;
                i = i / base;
                carryover = i;
            }
            else{
                prepend(X->list, (long)i);
                carryover = 0;
            }
            movePrev(A->list);
        }
        if(carryover != 0){
            prepend(X->list, carryover);
        }

        add(P, P, X);
        makeZero(X);
        ind++;
        movePrev(B->list);
    }

    freeBigInteger(&X);
    freeBigInteger(&A);
    freeBigInteger(&B);

    return P;
}
//// Other operations -----------------------------------------------------------

// printBigInteger()
// Prints a base 10 string representation of N to filestream out.
void printBigInteger(FILE* out, BigInteger N){
    if(N == NULL){
        printf("BigInteger Error: called printBigInteger() on a NULL BigInteger");
        exit(-1);
    }
    if(N ->sign == 0){
        fprintf(out, "0\n\n");
        return;
    }
    if(N->sign == -1)
        fprintf(out, "-");

    while(front(N->list) == 0){
        deleteFront(N->list);
    }
    moveFront(N->list);
    fprintf(out, "%ld", get(N->list));
    moveNext(N->list);
    while(index(N->list) != -1){
        fprintf(out, "%0*ld", power, get(N->list));
        moveNext(N->list);
    }
    fprintf(out, "\n\n");
}
