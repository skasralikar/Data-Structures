//skasrali
//pa2
//List.h
//List module

#ifndef _LIST_H_INCLUDED
#define _LIST_H_INCLUDED
#include <stdio.h>

//Defines pointer to List object
typedef struct ListObj* List;

//Contructors and Destructors
List newList(void);             //Creates and returns a new empty List.
void freeList(List* pL);        //Frees all heap memory associated with *pL

//Access functions
int length(List L);             //returns the numer of elements in L
int index(List L);              //returns index of cursor element if defined, else -1
void* front(List L);              //returns front element of L
void* back(List L);               //returns back element of L
void* get(List L);                //returns cursor element of :
int equal(List A, List B);     //returns true(1) is A = B, else return false(0)

//Manipulation procedures
void clear(List L);             //resets L to empty state
void moveFront(List L);         //sets cursor to front element
void moveBack(List L);          //sets cursor to back element
void movePrev(List L);          //move cursor one step toward front of L (head) if cursor not at front and defined already
void moveNext(List L);          //move cursor one step toward back of L if cursor not at back and defined; else become undefined
void prepend(List L, void* data); //insert new element into L before front element
void append(List L, void* data);  //insert new element into L after back element
void insertBefore(List L, void* data); //insert new element before cursor
void insertAfter(List L, void* data);  //insert new element after cursor
void deleteFront(List L);       //delete front element
void deleteBack(List L);        //delete back element
void delete(List L);            //delete cursor element

//Other operations
void printList(FILE* out, List L);
List copyList(List L);

#endif
