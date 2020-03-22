//-----------------------------------------------------------------------------
// Henry Nguyen
// CruzID: hnguye87
// Assignment: pa4
//-----------------------------------------------------------------------------
// List.h
// Header file for List ADT
//-----------------------------------------------------------------------------
#ifndef _LIST_H_INCLUDE_
#define _LIST_H_INCLUDE_
#include <stdio.h>
// Exported type --------------------------------------------------------------
typedef struct ListObj* List;

// Constructors-Destructors ---------------------------------------------------
List newList(void); // Returns reference to new empty List object.
void freeList(List* pL); // Frees all heap memory associated with List *pL, and sets *pL to NULL.

// Access functions -----------------------------------------------------------
int index(List L); // Returns index of cursor element if defined, -1 otherwise.
int get(List L); // Returns cursor element of L. Pre: length()>0, index()>=0
int front(List L); //Returns the element of the front node of L. Pre: length()>0, index()>=0
int back(List L);   ////Returns the element of the front node of L. Pre: length()>0, index()>=0
int length(List L); // Returns the length of List.
int isEmpty(List L); //Returns true (1) if Q is empty, otherwise returns false (0)

// Manipulation procedures ----------------------------------------------------
void moveFront(List L); // If L is non-empty, sets cursor under the front element, otherwise does nothing.
void moveBack(List L); // If L is non-empty, sets cursor under the back element, otherwise does nothing.
void moveNext(List L); // If cursor is defined and not at back, move cursor one
                        // step toward the back of L; if cursor is defined and at
                        // back, cursor becomes undefined; if cursor is undefined do nothing
void movePrev(List L); // If cursor is defined and not at front, move cursor one
                        // step toward the front of L; if cursor is defined and at
                        // front, cursor becomes undefined; if cursor is undefined do nothing
void clear(List L);     //brings list L back into its original state
void prepend(List L, int data); //adds a node containing data to the front of L
void append(List L, int data);   //adds a node containing data to the back of L
void deleteFront(List L);       //delete the node at the front of L
void deleteBack(List L);        //delete the node at the back of L
void insertBefore(List L, int data); // Insert new element before cursor. Pre: length()>0, index()>=0
void insertAfter(List L, int data); // Insert new element after cursor.  Pre: length()>0, index()>=0
void delete(List L); // Delete cursor element, making cursor undefined. Pre: length()>0, index()>=0
// Other Functions ------------------------------------------------------------
List copyList(List L); // Returns a new List representing the same integer
                        // sequence as L. The cursor in the new list is undefined,
                        // regardless of the state of the cursor in L. The state of L is unchanged.
void printList(FILE* out, List L); // Prints data elements in Q on a single line to FILE*.
int equals(List A, List B); // returns true (1) if A is identical to B, false (0) otherwise

#endif
