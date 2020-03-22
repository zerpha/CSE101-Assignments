#include<stdio.h>
#include<stdlib.h>
#include "List.h"

int main(int argc, char* argv[])
{
	Lex(argv[1], argv[2]);

	List A = newList();
	append(A,1);
	append(A,2);
	moveFront(A);
	delete(A);
	append(A,3);
	append(A,5);
	moveFront(A);
	insertAfter(A, 12);
	delete(A);
	if (length(A) != 3) return 1;
	return 0;
}
