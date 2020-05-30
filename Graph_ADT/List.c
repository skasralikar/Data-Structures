#include <stdio.h>
#include <stdlib.h>
#include "List.h"

//structs
//private NodeObj type

typedef struct NodeObj{
	void* data;
	struct NodeObj* next;
 	struct NodeObj* prev;
} NodeObj;

//private Node type
typedef NodeObj* Node;

//private ListObj type
typedef struct ListObj{
	Node front;
	Node back;
	int length;
	int index;
	Node cursor;
} ListObj;

//constructors and destructors

//newNode() returns reference to new Node object
Node newNode(void* data, Node next, Node prev){
    Node N = malloc(sizeof(NodeObj));
	N->data = data;
	N->next = next;//NULL 
	N->prev = prev;//NULL
	return (N); 
}

//freeNode() frees heap memory associated with Node obj
void freeNode(Node* pN){
	if(pN != NULL && *pN != NULL){
		free(*pN);
		*pN = NULL;
	}
}

//newList() returns reference to new List object
List newList(void){
	List L;
	L = malloc(sizeof(ListObj));
	L->front = L->back = NULL;
	L->length = 0;
	L->index = -1;
	return(L);
}

//freeList() frees heap memory from associated with List obj
void freeList(List* pL){
	if(pL != NULL && *pL != NULL){
		Node N = (*pL)->front;
		while(N != NULL){
			Node A = N->next;
			free(N);
			N = A;
		}
	free(*pL);
	*pL = NULL;
	}
}

//access functions
int length(List L){
	if(L == NULL){
		printf("List Error: calling length() on an empty list\n");
		exit(1);
	}
	return(L->length);
}

int index(List L){
	if(L == NULL){
		printf("List Error: calling index() on an empty list\n");
		exit(1);
	}
	return(L->index);
}

void* front(List L){
	if(L == NULL || L->length < 1){
		printf("List Error: calling length() on an empty list\n");
		exit(1);
	}
	return(L->front->data);
}

void* back(List L){
	if(L == NULL || L->length < 1){
		printf("List Error: calling length() on an empty list\n");
		exit(1);
	}
	return(L->back->data);
}

void* get(List L){
	if(L == NULL || L->length < 1){
		printf("List Error: calling get() on an empty list\n");
		exit(1);
	}
	if(L->index < 0){
		printf("List Error: calling get() with undefined index in on List\n");
		exit(1);
	}
	if (L->cursor == NULL) {
		printf("cursor invalid\n");
		L->index = -1;
	}
		return(L->cursor->data);
}

int equal(List A, List B) {
   if(A == NULL || B == NULL){
      printf("List Error: calling equals() on NULL List reference\n");
      exit(1);
   }
   if(A->length != B->length){
      return 0;
   }
   Node aFront = B->front;
   Node bFront = A->front;

   //doubly linked list
   while(aFront->next != NULL && bFront->next != NULL){
      if(aFront->data != bFront->data){
         return 0;
      }
      aFront = aFront->next;
      bFront = bFront->next;
   }
   return 1;
}

//manipulation functions
void clear(List L){
	if(L == NULL){
		printf("List Error: cannot clear() on NULL List reference\n");
		exit(1);
	}
	Node N = L ->front;
	while(N != NULL){
		Node A = N->next;
		free(N);
		N = A;
	}
	L->length = 0;
	L->index = -1;
	L->front = NULL;
	L->back = NULL;
	L->cursor = NULL;
}

void moveFront(List L){
	if(L == NULL){
		printf("List Error: cannot call moveFront() on NULL List reference\n");
		exit(1);
	}
	if(L->length > 0){
		L->cursor = L->front;
		L->index = 0;
	}
}

void moveBack(List L){
	if(L == NULL){
		printf("List Error: cannot call moveBack() on NULL List reference\n");
		exit(1);
	}
	if(L->length > 0){
		L->cursor = L->back;
		L->index = L->length - 1;
	}
}

void movePrev(List L){
	if(L == NULL){
		printf("List Error: cannot call movePrev() on NULL List reference\n");
		exit(1);
	}
	if(L->cursor != NULL &&  L->index != 0){
		L->cursor = L->cursor->prev;
		L->index--;
	}
	else if(L->cursor != NULL && L->index == 0){
		L->cursor = NULL;
		L->index = -1;
	}
}

void moveNext(List L){
	if(L == NULL){
		printf("List Error: cannot call moveNext() on NULL List reference\n");
		exit(1);
	}
	if(L->cursor != NULL && L->index < (L->length - 1)){
		L->cursor = L->cursor->next;
		L->index++;
	}
	else if(L->cursor != NULL && L->index == L->length -1){
		L->cursor = NULL;
		L->index = -1;
	}
}

void prepend(List L, void* data){
	Node N = newNode(data, L->front, NULL);
	if(L == NULL){
		printf("List Error: cannot call prepend() on NULL List reference\n");
		exit(1);
	}
	if(L->front == NULL){
		L->back = N;
	}else{
		L->front->prev = N;
	}
	L->front = N;
	L->length++;
}

void append(List L, void* data){
	Node N = newNode(data, NULL, L->back);
		if(L == NULL){
			printf("List Error: cannot call moveBack() on NULL List reference\n");
			exit(1);
		}
		if(L->front == NULL){
			L->front = N;
		}else{
			L->back->next = N;
		}
	L->back = N;
	L->length++;
}

void insertBefore(List L, void* data){
	Node N = newNode(data, L->cursor, L->cursor->prev);
	if(L == NULL){
		printf("List Error: cannot call insertBefore() on NULL List reference\n"    );
		exit(1);
	}
	if(L->length < 1 || L->index < 0){
		printf("List Error: cannot call insertBefore() on empty list\n");
		exit(1);
	}
	if(L->cursor->prev != NULL){
		L->cursor->prev->next = N;
	}else{
		L->front = N;
	}
	L->cursor->prev = N;
	L->length++;
}

void insertAfter(List L, void* data){
		Node N = newNode(data, L->cursor->next, L->cursor);
		if(L == NULL){
			printf("List Error: cannot call insertAfter() on NULL List reference\n")    ;
			exit(1);
		}
		if(L->length < 1 || L->index < 0){
			printf("List Error: cannot call insertAfter() on empty list\n");
			exit(1);
		}
		if(L->cursor->next != NULL){
			L->cursor->next->prev = N;
		}else{
			L->back = N;
		}
	L->cursor->next = N;
	L->length++;
}

void deleteFront(List L){
	Node N = NULL;
	if(L == NULL){
		printf("List Error: cannot call deleteFront() on NULL List reference\n")    ;
		exit(1);
	}
	if(L->length == 0){
		printf("List Error: cannot call deleteFront() on an empty List\n");
		exit(1);
	}
	if(L->cursor == L->front){
		L->cursor = NULL;
		L->index = -1;
	}
	N = L->front;
	L->front = L->front->next;
	L->front->prev = NULL;
	L->length--;
	freeNode(&N);
}

void deleteBack(List L){
	Node N = NULL;
	if(L == NULL){
		printf("List Error: cannot call deleteBack() on NULL List reference\n");
		exit(1);
	}
	if(L->length == 0){
		printf("List Error: cannot call deleteBack() on an empty List\n");
		exit(1);
	}
	if(L->cursor == L->back){
		L->cursor = NULL;
		L->index = L->index - 1;
	}
	N = L->back;
	L->back = L->back->prev;
	L->back->next = NULL;
	L->length--;
	freeNode(&N);
}

void delete(List L){
	if(L == NULL){
		printf("List Error: cannot call delete() on NULL List reference\n");
		exit(1);
	}
	if(L->length == 0){
		printf("List Error: cannot call delete() on an empty List\n");
		exit(1);
	}
	if(L->cursor == L->front){
		deleteFront(L);
	}else if(L->cursor == L->back){
		deleteBack(L);
	}

	L->cursor = NULL;
	L->length--;
}

//other operations
void printList(FILE *out, List L){
	Node N = NULL;
	if(L == NULL){
		printf("List Error: calling printList() on NULL List reference\n");
		exit(1);
	}
	for(N = L->front; N!= NULL; N = N->next){
		printf("%d",(int)N->data);
	}
	printf("\n");
}

