#include<stdlib.h>
#include<stdio.h>
#include"List.h"
#include"graph.h"

/* TODO: implement graph constructor
Instantiate a graph given the number of vertices
There are no edges at instantiation
*/

graph createGraph(int num){
	graph g = (graph)malloc(sizeof(graphObj));
	g->n = num;
	g->matrix  = (int**)malloc(num * sizeof(int *));
	for(int i = 0; i < num; i++){
		g->matrix[i] = calloc(num, sizeof(int));
	}
	return g;
}



/* TODO: implement graph destructor
destruct graph and free allocated memory as appropriate
*/

void destructGraph(graph g){
	for(int i = 0; i< g->n; i++){
		free(g->matrix[i]);
		g->matrix[i] = NULL;
	}
	free(g->matrix);
	g->matrix = NULL;
	free(g);
	g = NULL;
}



// TODO: implement addEdge function

void addEdge(graph g, int i, int j){
	g->matrix[i][j] = 1;
}
	


// TODO: implement removeEdge function

void removeEdge(graph g, int i, int j){
	g->matrix[i][j] = 0;
}




// TODO: implement hasEdge function

int hasEdge(graph g, int i, int j){
	return g->matrix[i][j];
}


// TODO: implement outEdges function

void outEdges(graph g, int i, node** list){
	for(int q = 0; q < g->n; q++){
		if(g->matrix[i][q] == 1){
			node *n = createList(q);
			insertList(list, n);
		}
	}
}


// TODO: implement inEdges function

void inEdges(graph g, int j, node** list){
	for(int a = 0; a < g->n; a++){
		if(g->matrix[a][j] == 1){
			node *n = createList(a);
			insertList(list, n);
		}
	}
}




// TODO: implement getNumVer

int getNumVer(graph g){
	return g->n;
}




// TODO: implement printGraph
	
void printGraph(graph g){
	for(int t = 0; t < g->n; t++){
		printf("\n");
		for(int u = 0; u < g->n; u++){
			printf("%d ", g->matrix[t][u]);
		}
	}
	printf("\n");
}










	

