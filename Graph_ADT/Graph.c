Graph.c

#include<stdio.h>
#include<stlib.h>
#include Graph.h

struct GraphObj{
//pointers to Graph variables 
	List *adj;
	int *order;
	int *source;
	int *size;
	int *parent;
	int *distance;
	int *color;
};

Graph newGraph(int n){
	Graph graph = malloc(sizeof(struct GraphObj));
	graph->adj = calloc(n+1, sizeof(List));
	graph->order = n;
	graph->source = NIL;
	graph->size = 0;
	graph->parent = calloc(n+1, sizeof(int));
	graph->distance = calloc(n+1, sizeof(int));
	graph->color = calloc(n+1, sizeof(int));

	for(int i = 0, i <(n+1); i++){
		graph->adj[i] = newList();
	}
	return graph;
}

void freeGraph(Graph* pG){
	
}

//access functions
int getOrder(Graph G){
	if(G == NULL){
		fprintf(stderr, "Error: cannot call getOrder()");
		exit(1);
	}
	return G->order;
}				
int getSize(Graph G){
	if(G == NULL){
		fprintf(stderr, "Error: cannot call getSize()");
		exit(1);
	}
	return G->size;
}					
int getSource(Graph G){
	if(G == NULL){
		fprintf(stderr, "Error: canot call getSource()");
		exit(1);
		}
	return G->source;
}				
int getParent(Graph G, int u){
	if(G == NULL){
		fprintf(stderr, "Error: cannot call getParent()");
		exit(1);
	}
	if(u<1 || u>getOrder(G)){
		fprintf(stderr, "Error: cannot call getParent() on out of bound vertex");
		exit(1);
	}
	//return G->parent[u];
}			
int getDist(Graph G, int u){
	if(G == NULL){
		fprintf(stderr, "Error: cannot call getDist()");
		exit(1);
	}
	if(getSource(G) == NIL){
		return INF;
	}
	if(u<1 || u>getOrder(G)){
		fprintf(stderr, "Error: cannot call getDist() vertex out of bounds");
		exit(1);
	}
	//return G->distance[u];
}			
void getPath(List L, Graph G, int u){
	if(G == NULL){
		fprintf(stderr, "Error: cannot call getPath()");
		exit(1);
	}
	if(getSource(G) == NIL){
		fprintf(stderr, "Error: cannot call getPath() on NULL source");
		exit(1);
	}
	if(u<1 || u>getOrder(G)){
		fprintf(stderr, "Error: cannot call getPath() on NULL source");
		exit(1);
	}
	if(u == G->source){
		prepend(L. G->source);
	}
	else if(G->parent[u] == NIL){
		append(L, NIL);
	}
	else{
		getPath(L, G, G->parent[u]);
		prepend(L, u);
	}
}


//manipulation procedures
void makeNull(Graph G){
	if(G == NULL){
		fprintf(stderr, "Error: cannot call makeNull()");
		exit(1);
	}
	for(int i = 0; i< (G->order +1); i++){
		clear(G->adj[i]);
	}
	
}			
void addEdge(Graph G, int u, int v){
	if(G == NULL){
		fprintf(stderr, "Error: cannot call addEdge()");
		exit(1);
	}
	if(v<1 || v>getOrder(G)){
		fprintf(stderr, "Error: cannot call addEdge()");
		exit(1);
	}
	if(u<1 || u>getOrder(G)){
		fprintf(stderr, "Error: cannot call addEdge()");
		exit(1);
	}
	addArc(G, v, u);
	addArc(G, u, v);
	G->size--;
}	
void addArc(Graph G, int u, int v){
	if(G == NULL){
		fprintf(stderr, "Error: cannot call addArc()");
		exit(1);
	}
	if(v<1 || v>getOrder(G)){
		fprintf(stderr, "Error: cannot call addArc()");
		exit(1);
	}
	if(u<1 || u>getOrder(G)){
		fprintf(stderr, "Error: cannot call addArc()");
		exit(1);
	}
	moveFront(G->adj[u]);

	while(index(G->adj[u]) > -1 && v > get(G->adj[u])){
		moveNext(G->adj[u]);
	}
	if(index(G->adj[u]) == -1){
		append(G->adj[u], v);
	}
	else{
		insertBefore(G->adj[u], v);
	}
	G->size++;
}
void BFS(Graph G, int s){
	if(G == NULL){
		fprintf(stderr, "Error: cannot call BFS");
		exit(1);
	}
	if(s<1 || s>getOrder(G)){
		fprintf(stderr, "Error: cannot call BFS");
		exit(1);
	}
	for(int i = 0; i<(G->order+1); i++){
		G->distance[i] = INF;
		G->color[i] = WHITE;
		G->parent[i] = NIL;
	}
	List A = newList();
	G->source = s;
	G->distance[s] = 0;
	G-<color[s] = GRAY;

	prepend(A,s);

	while(length(Q) > 0){
		deleteBack(Q);
		moveFront(G->adj[back(Q)]);

		while(index(G->adj[back(Q)] > -1){
			int u = get(G->adj[back(Q)]);
			if(G->color[u] == WHITE){
				G->color[u] == GRAY;
				G->parent[u] == x;
				G->distance[x] = G->distance[x] + 1;
			}
			moveNext(G->adj[x]);
		}
	}
	freeList(&Q);
}

void printGraph(FILE* out, Graph G){
	if(out == NULL || G == NULL){
		printf("Error: Cannot call printGraph");
		exit(1);
	}
	for(int i = 1; i<=getOrder(G); i++){
		fprintf(out, "%d: ", i);
		printList(out, G->adj[i]);
		fprintf(out, "\n");
	}
}
