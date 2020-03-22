//-----------------------------------------------------------------------------
// Henry Nguyen
// CruzID: hnguye87
// Assignment: pa1
//-----------------------------------------------------------------------------
// List.c
// Implementation file for List ADT
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include "List.h"

// structs --------------------------------------------------------------------

// private NodeObj type
typedef struct NodeObj{
   int data;
   struct NodeObj* next;
   struct NodeObj* prev;
} NodeObj;

// private Node type
typedef NodeObj* Node;

// private QueueObj type
typedef struct ListObj{
   Node front;
   Node back;
   Node cursor;
   int length;
   int indexCursor;
} QueueObj;


// Constructors-Destructors ---------------------------------------------------

// Returns reference to new Node object. Initializes next and data fields.
// Private.
Node newNode(int data){
   Node N = malloc(sizeof(NodeObj));
   N->data = data;
   N->next = NULL;
   N->prev = NULL;
   return(N);
}

// Frees heap memory pointed to by *pN, sets *pN to NULL.
// Private.
void freeNode(Node* pN){
   if( pN!=NULL && *pN!=NULL ){
      free(*pN);
      *pN = NULL;
   }
}

// Returns reference to new empty Line object.
List newList(void){
   List Q;
   Q = malloc(sizeof(QueueObj));
   Q->front = Q->back = NULL;
   Q->cursor = NULL;
   Q->length = 0;
   Q->indexCursor = -1;
   return(Q);
}


// Frees all heap memory associated with List *pL, and sets *pL to NULL.S
void freeList(List* pL){
   if(pL!=NULL && *pL!=NULL) {
      while( !isEmpty(*pL) ) {
         deleteFront(*pL);
      }
      free(*pL);
      *pL = NULL;
   }
}


// Access functions -----------------------------------------------------------

// Returns index of cursor element if defined, -1 otherwise.
int index(List L){
    if( L==NULL ){
      printf("List Error: calling index() on NULL List reference\n");
      exit(1);
   }
   if( L->cursor == NULL ){
        return -1;
   }
    return L->indexCursor;
}
// Returns cursor element of L if defined, -1 otherwise.
int get(List L){
    if( L==NULL ){
      printf("List Error: calling get() on NULL List reference\n");
      exit(1);
   }
   if( index(L) == -1 ){
      printf("Called get() on a NULL cursor\n");
      return -1;
   }
   if( length(L) <= 0){
        printf("Called get() on a List of length 0\n");
        return -1;
   }
    return L->cursor->data;
}

//Returns the element of the front node of L if defined, -1 otherwise.
int front(List L){
   if( L==NULL ){
      printf("List Error: calling front() on NULL List reference\n");
      exit(1);
   }
   if( isEmpty(L) ){
      printf("Called front() on an empty List\n");
      return -1;
   }
   return(L->front->data);
}

//Returns the element of the back node of L
int back(List L){
   if( L==NULL ){
      printf("List Error: calling back() on NULL List reference\n");
      exit(1);
   }
   if( isEmpty(L) ){
      printf("Called front() on an empty List\n");
      return -1;
   }
   return(L->back->data);
}

// Returns the length of Q.
int length(List L){
   if( L==NULL ){
      printf("List Error: calling length() on NULL List reference\n");
      exit(1);
   }
   return(L->length);
}

// Returns true (1) if Q is empty, otherwise returns false (0)
int isEmpty(List L){
   if( L==NULL ){
      printf("List Error: calling isEmpty() on NULL List reference\n");
      exit(1);
   }
   return(L->length==0);
}

// Manipulation procedures ----------------------------------------------------
// If L is non-empty, sets cursor under the front element, otherwise does nothing.
void moveFront(List L){
    if( L==NULL ){
      printf("List Error: calling moveFront() on NULL List reference\n");
      exit(1);
   }
   if( isEmpty(L) ){
      return;
   }
   L->cursor = L->front;
   L->indexCursor = 0;
}

// If L is non-empty, sets cursor under the back element, otherwise does nothing.
void moveBack(List L){
    if( L==NULL ){
      printf("List Error: calling moveBack() on NULL List reference\n");
      exit(1);
   }
   if( isEmpty(L) ){
      return;
   }
   L->cursor = L->back;
   L->indexCursor = (L->length) -1;
}

//moves cursor one step back if possible, else does nothing
void moveNext(List L){
    if( L==NULL ){
      printf("List Error: calling moveNext() on NULL List reference\n");
      exit(1);
   }
   if( index(L) == -1 || isEmpty(L) ){
      printf("Called moveNext() on undefined cursor\n");
      return;
   }
   L->cursor = L->cursor->next;
   L->indexCursor++;
}

//moves cursor one step forward if possible, else does nothing
void movePrev(List L){
    if( L==NULL ){
      printf("List Error: calling movePrev() on NULL List reference\n");
      exit(1);
   }
   if( index(L) == -1 || isEmpty(L) ){
      printf("Called movePrev() on undefined cursor\n");
      return;
   }
   L->cursor = L->cursor->prev;
   L->indexCursor--;
}

//brings list L back into its original state
void clear(List L){
    while(L->length != 0)
    {
        deleteBack(L);
    }
    L->indexCursor = -1;
}

//adds a node containing data to the back of L
void append(List L, int data)
{
   Node N = newNode(data);

   if( L==NULL ){
      printf("List Error: calling append() on NULL List reference\n");
      exit(1);
   }
   if( isEmpty(L) ) {
      L->front = L->back = N;
   }else{
      L->back->next = N;
      N->prev = L->back;
      L->back = N;
   }
   L->length++;
}

//adds a node containing data to the front of L
void prepend(List L, int data)
{
   Node N = newNode(data);

   if( L==NULL ){
      printf("List Error: calling prepend() on NULL List reference\n");
      exit(1);
   }
   if( isEmpty(L) ) {
      L->front = L->back = N;
   }else{
       L->front->prev = N;
       N->next = L->front;
       L->front = N;
   }
   L->length++;
   if(L->cursor != NULL)
       L->indexCursor++;
}

//adds a node containing data to the front of L
void deleteFront(List L){
   Node N = NULL;

   if( L==NULL ){
      printf("List Error: calling deleteFront() on NULL List reference\n");
      exit(1);
   }
   if( isEmpty(L) ){
      printf("List Error: calling deleteFront() on empty List\n");
      exit(1);
   }
   N = L->front;
   if( length(L)>1 ) {
      L->front->next->prev = NULL;
      L->front = L->front->next;

   }else{
      L->front = L->back = NULL;
   }
   L->length--;
   if(L->cursor != NULL)
      L->indexCursor--;
   freeNode(&N);
}

//adds a node containing data to the back of L
void deleteBack(List L){
   Node N = NULL;

   if( L==NULL ){
      printf("List Error: calling deleteBack() on NULL List reference\n");
      exit(1);
   }
    if( isEmpty(L) ){
      printf("List Error: calling deleteBack() on empty List\n");
      exit(1);
   }
   N = L->back;
   if(index(L) != -1){
   	if(get(L) == back(L))
      	    L->indexCursor = -1;
   }
   if( length(L)>1 ) {
      L->back->prev->next = NULL;
      L->back = L->back->prev;
   }else{
      L->front = L->back = NULL;
   }
   L->length--;
   freeNode(&N);
}

// Insert new element before cursor.
void insertBefore(List L, int data){
    Node N = newNode(data);
    if( L==NULL ){
      printf("List Error: calling insertBefore() on NULL List reference\n");
      exit(1);
   }
   if(L->cursor == NULL){
        printf("Calling insertBefore() on an undefined cursor\n");
       return;
   }
   if( isEmpty(L) ){
      L->front = L->back = N;
      return;
    }
    else{
        N->next = L->cursor;
        N->prev = L->cursor->prev;
        if (L->cursor->prev != NULL) L->cursor->prev->next = N;
            else L->front = N;
        L->cursor->prev = N;
    }
    L->length++;
    if(L->cursor != NULL)
	L->indexCursor++;
}

// Insert new element after cursor.
void insertAfter(List L, int data){
    Node N = newNode(data);
    if( L==NULL ){
      printf("List Error: calling insertAfter() on NULL List reference\n");
      exit(1);
   }
      if(L->cursor == NULL){
        printf("Calling insertAfter() on an undefined cursor\n");
       return;
   }
   if( isEmpty(L) ){
      L->front = L->back = N;
      return;
    }
    else{
        N->prev = L->cursor;
        N->next = L->cursor->next;
        if (L->cursor->next != NULL) L->cursor->next->prev = N;
            else L->back = N;
        L->cursor->next = N;
    }
    L->length++;
}

// Delete cursor element, making cursor undefined.
void delete(List L){

    if( L==NULL ){
      printf("List Error: calling delete() on NULL List reference\n");
      exit(1);
   }
    if(L->cursor == NULL){
        printf("Calling delete() on an undefined cursor\n");
       return;
   }
   if( isEmpty(L) ){
      printf("List Error: calling delete() on empty List\n");
      exit(1);
   }
   if(L->cursor->prev != NULL)
      L->cursor->prev->next = L->cursor->next;
   else
      L->front = L->cursor->next;
   if(L->cursor->next != NULL)
      L->cursor->next->prev = L->cursor->prev;
   else
      L->back = L->cursor->prev;

    freeNode(&(L->cursor));
    L->cursor = NULL;
    L->length--;
}
// Other Functions ------------------------------------------------------------

// Returns a new List representing the same integer sequence as L
List copyList(List L){
   List Q = newList();
    Node N = NULL;
    for(N = L->front; N != NULL; N = N->next){
      append(Q, N->data);
   }
   return Q;
}

// Prints data elements in Q on a single line.
void printList(FILE* out, List L){
   Node N = NULL;

   if( L==NULL ){
      printf("List Error: calling printList() on NULL List reference\n");
      return;
   }

   for(N = L->front; N != NULL; N = N->next){
      fprintf(out, "%d ", N->data);
   }
   printf("\n");
}

// returns true (1) if A is identical to B, false (0) otherwise
int equals(List A, List B){
   int eq = 0;
   Node N = NULL;
   Node M = NULL;

   if( A==NULL || B==NULL ){
      printf("List Error: calling equals() on NULL List reference\n");
      exit(1);
   }

   eq = ( A->length == B->length );
   N = A->front;
   M = B->front;
   while( eq && N!=NULL){
      eq = (N->data==M->data);
      N = N->next;
      M = M->next;
   }
   return eq;
}
