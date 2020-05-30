//Dictionary.c
//skasrali
//pa5
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "Dictionary.h"

const int tableSize = 101;

//roate_left()
unsigned int rotate_left(unsigned int value, int shift) {
	int sizeInBits = 8*sizeof(unsigned int);
	shift = shift & (sizeInBits - 1);  // remainder of shift on division by sizeInBits
	if ( shift == 0 )
		return value;
	else
		return (value << shift) | (value >> (sizeInBits - shift)); // perform rotation
}

//pre_hash()
unsigned int pre_hash(char* input) {  // input points to first char in string
	unsigned int result = 0xBAE86554;  // = 10111010111010000110010101010100, begin with a random looking bit pattern
	while (*input) {                   // while *input is not '\0' (not end of string)
		result ^= *input++;                // result = result ^ *input (current char alters result) 
                                         // input++  (go to next char)
		result = rotate_left(result, 5);   // rotate result by fixed amount
	}
	return result;  // result is now a random looking bit pattern depending on input string
}

// hash()
int hash(char* key){
	return pre_hash(key)%tableSize;
}

typedef struct NodeObj{
	char *key;
	char *value;
	struct NodeObj * next;
}
NodeObj;

typedef NodeObj * Node;

Node newNode(char*k, char*v){
	Node N = malloc(sizeof(NodeObj));
	assert(N != NULL);
	N -> key = k;
	N -> value = v;
	N -> next = NULL;
	return(N);
}

void freeNode(Node * pN){
	if(pN != NULL && *pN != NULL){
		free(*pN);
		*pN = NULL;
	}
}

//Dictionary
typedef struct DictionaryObj{
	Node *hashtable;
	int numItems;
} DictionaryObj;

//newDictionary()
Dictionary newDictionary(void){
	Dictionary D = malloc(sizeof(DictionaryObj));
	assert( D!= NULL);
	D-> hashtable = calloc(tableSize, sizeof(NodeObj));
	assert(D -> hashtable != NULL);
	D-> numItems = 0;
	return D;
}

//freeDictionary()
void freeDictionary(Dictionary* pD){
	if(pD != NULL && *pD != NULL){
		makeEmpty(*pD);
		free((*pD) -> hashtable);
		free(*pD);
		*pD = NULL;
	}
}

//isEmpty()
int isEmpty(Dictionary D){
	return D-> numItems == 0;
}

//size()
int size(Dictionary D){
	return D-> numItems;
}

//lookup()
char* lookup(Dictionary D, char*k){
	Node N = D->hashtable[hash(k)];
	if (D == NULL){
		fprintf(stderr, "Dictionary Error: lookup() cannot be called on NULL Dictionary\n");
		exit(EXIT_FAILURE);
	}
	while(N != NULL){
		if(strcmp(N ->key, k) == 0){
			return N-> value;
		}
		N = N-> next;
	}
	return NULL;
}

//insert
void insert(Dictionary D, char*k, char*v){
	if(lookup(D, k) != NULL){
		fprintf(stderr, "cannot insert duplicate  key\n");
	}
	if(D -> numItems == 0){
		Node N = newNode(k, v);
		N-> next = D-> hashtable[hash(k)];
		D-> hashtable[hash(k)] = N;
	}else{
		Node N;
		N = newNode(k, v);
		N-> next = D-> hashtable[hash(k)];
		D-> hashtable[hash(k)] = N;
	}
	D-> numItems++;
}

//delete()
void delete(Dictionary D, char* k){
	if(lookup(D, k) == NULL){
		fprintf(stderr, "cannot delete non-existend key\n");
	}
	Node N = D-> hashtable[hash(k)];
	Node A = NULL;
	if(D -> numItems == 0){
		D-> hashtable[hash(k)] = N-> next;
		N-> next = NULL;
	}else{
		if(strcmp(N-> key, k) == 0){
			D-> hashtable[hash(k)] = N-> next;
		}else{
			while(strcmp(N-> key, k) != 0 && N != NULL){
				A = N;
				N = N->next;
			}
			A-> next = N-> next;
		}
	}
	D-> numItems--;
	freeNode(&N);
}

//makeEmpty
void makeEmpty(Dictionary D){
	if(D == NULL){
		fprintf(stderr, "cannot call makeEmpty() on NULL dictionary\n");
		exit(EXIT_FAILURE);
	}else{
		for(int i = 0; i < tableSize; i++){
			while(D-> hashtable[i] != NULL){
				Node N;
				N = D->hashtable[i];
				D-> hashtable[i] = N-> next;
				freeNode(&N);
				N = NULL;
			}
		}
		D-> numItems = 0;
	}
}

//printDictionary()
void printDictionary(FILE* out, Dictionary D){
	Node N;
	int i = 0;
	while(i < tableSize){
		for(N = D-> hashtable[i]; N != NULL; N = N->next){
			fprintf(out, "%s %s\n", N-> key, N-> value);
		}
		i++;
	}
}
