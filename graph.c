#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <graph.h>
#include <queue.h>

#define GRAPH_DEBUG 0

/* criacao e inicializacao do grafo */
GRAPH * create_graph() {
	GRAPH *new_graph = (GRAPH *) calloc(1, sizeof(GRAPH));

	int i = 0, j;
	for(; i < MAX_VERTEX; i++)
		for(j = i; j < MAX_VERTEX; j++) {	/* preenche tudo com VAZIO */
			new_graph->edges[i][j] = new_graph->edges[j][i] = VAZIO;
		}
}

int getActorIndex(GRAPH *graph, char *actor_name) {
	int index = 0;
	for(; index < graph->num_vertex; index++) {
		if(GRAPH_DEBUG)
			printf("\n\tComparando %s com %s", actor_name, graph->actors_names[index]);
		
		if(!strcmp(actor_name, graph->actors_names[index])) {
			break;
		}
	}

	if(index == graph->num_vertex)
		return -1;
	return index;
}

int getMovieIndex(GRAPH *graph, char *movie_name) {
	int index = 0;
	for(; index < graph->num_movies; index++)
		if(!strcmp(movie_name, graph->movies_names[index]))
			break;

	if(index == graph->num_movies)
		return -1;
	return index;
}

/* insere um nome de ator no vetor de vertices e retorna seu indice */
int insertVertex(GRAPH *graph, char * actor_name) {
	int actor_index = getActorIndex(graph, actor_name);

	if(actor_index == -1) {	/* nao existe */
		graph->actors_names[graph->num_vertex] = (char *) malloc(50 * sizeof(char));
		strcpy(graph->actors_names[graph->num_vertex++], actor_name);
		return graph->num_vertex - 1;
	}

	return actor_index;
}

/* insere um nome de filme no vetor de filmes e retorna seu indice */
int insertMovie(GRAPH *graph, char *movie_name) {
	graph->movies_names[graph->num_movies] = (char *) malloc(50 * sizeof(char));
	strcpy(graph->movies_names[graph->num_movies++], movie_name);

	return graph->num_movies - 1;
}

/* insere uma aresta ligando dois atores pelo indice do filme */
int * insertEdge (GRAPH *graph, int v1, int v2, int movie_index) {
	graph->edges[v1][v2] = movie_index;
	graph->edges[v2][v1] = movie_index;
	return &graph->edges[v1][v2];
}

void __breadth_search(GRAPH *graph, int vertex, int *colors) {
	colors[vertex] = GREY;

	QUEUE *queue = create_queue();
	push_queue(queue, vertex);

	while(queue->size) {
		vertex = pop_queue(queue);

		int i = 0;
		for(; i < graph->num_vertex; i++) {
			if(graph->edges[vertex][i] != VAZIO) {
				if(colors[i] == WHITE) {
					colors[i] = GREY;
					push_queue(queue, i);
				}
			}
		}
		colors[vertex] = BLACK;
	}

	free_queue(queue);
}

void breadth_search(GRAPH *graph) {
	int *colors = (int *) malloc(graph->num_vertex * sizeof(int));
	int i = 0;
	for(i = 0; i < graph->num_vertex; i++)
		colors[i] = WHITE;
	
	for(i = 0; i < graph->num_vertex; i++) 
		if(colors[i] == WHITE)
			__breadth_search(graph, i, colors);
}