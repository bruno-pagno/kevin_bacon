#include <stdlib.h>
#include <graph.h>

/* criacao e inicializacao do grafo */
GRAPH * create_graph(int num_vertex) {
	if(num_vertex < 1)	/* previne numero de arestas invalido */
		exit(0);
	
	GRAPH *new_graph = (GRAPH *) malloc(sizeof(GRAPH));
	new_graph->num_vertex = num_vertex;
	new_graph->edges = (EDGE **) malloc(num_vertex * sizeof(EDGE *));

	int i = 0;
	for(; i < num_vertex; i++)	/* inicializa os vetores de arestas */
		new_graph->edges[i] = NULL;
	
	return new_graph;
}

/* insercao de uma aresta */
int insert_edge(GRAPH *graph, int origin, int destination, int weight) {
	if(!graph)
		return FAILED;
	
	if(origin < 0 || origin > graph->num_vertex || destination < 0 || destination > graph->num_vertex)
		return INDEX_ERROR;
	
	EDGE *new_edge = (EDGE *) malloc(sizeof(EDGE));
	new_edge->destination = destination;
	new_edge->weight = weight;

	/* insercao na cabeça */
	new_edge->next = graph->edges[origin];
	graph->edges[origin] = new_edge;

	return SUCCESS;
}

/* retorna se, a partir desta origem, existe uma arestas */
int exists_edge(GRAPH *graph, int origin, int destination) {
	if(!graph)
		return FAILED;
	
	if(origin < 0 || origin > graph->num_vertex)
		return INDEX_ERROR;

	EDGE *edge = graph->edges[origin];
	while(edge) {
		if(edge->destination == destination)
			return 1;
		
		edge = edge->next;
	}

	return 0;
}

int have_adjacent(GRAPH *graph, int origin) {
	if(!graph)
		return FAILED;
	
	if(origin < 0 || origin > graph->num_vertex)
		return INDEX_ERROR;
	
	if(graph->edges[origin] != NULL)
		return 1;

	return 0;
}

/* retorna o primeiro adjacente da origem */
EDGE * get_first_adjacent(GRAPH *graph, int origin) {
	if(!graph || origin < 0 || origin > graph->num_vertex)
		return NULL;
	return graph->edges[origin];
}

/* retorna o proximo adjacente */
EDGE * next_edge(GRAPH *graph, int origin, EDGE *previous) {
	if(!graph || !previous || origin < 0 || origin > graph->num_vertex)
		return NULL;
	return previous->next;
}

/* recupera o peso de uma aresta, se houver */
int get_edge_weight(GRAPH *graph, int origin, int destination) {
	if(!graph)
		return FAILED;
	
	if(origin < 0 || origin > graph->num_vertex || destination < 0 || destination > graph->num_vertex)
		return INDEX_ERROR;
	
	if(!graph->edges[origin])
		return NOT_FOUND;

	EDGE *edge = graph->edges[origin];
	while(edge) {
		if(edge->destination == destination)
			return edge->weight;		
		edge = edge->next;
	}
	
	return NOT_FOUND;
}

/* remove uma aresta do grafo */
int remove_edge(GRAPH *graph, int origin, int destination) {
	if(!graph)
		return FAILED;
	
	if(origin < 0 || origin > graph->num_vertex || destination < 0 || destination > graph->num_vertex)
		return INDEX_ERROR;

	if(!graph->edges[origin])
		return NOT_FOUND;
	
	EDGE *edge = graph->edges[origin];
	while(edge) {
		if((edge)->destination == destination) {
			EDGE *aux = edge;
			edge = aux->next;
			free(aux);
			return SUCCESS;
		}
		edge = edge->next;
	}

	return NOT_FOUND;
}

/* libera o grafo da memoria */
void free_graph(GRAPH *graph) {
	if(graph) {
		int i = 0;
		for(; i < graph->num_vertex; i++) {	/* para cada vetor de adjacencias */
			while(graph->edges[i]) {	/* libera o vetor de adjacencias a partir do inicio */
				EDGE *edge = graph->edges[i];
				graph->edges[i] = edge->next;
				free(edge);
			}
		}
		free(graph->edges);
		free(graph);
		graph = NULL;
	}
}

int __depth_search(GRAPH *graph, int vertex, int colors[]) {
	colors[vertex] = GREY;

	EDGE *adjacent = get_first_adjacent(graph, vertex);
	while(adjacent) {
		int k = adjacent->destination;
		if(colors[k] == WHITE)
			__depth_search(graph, k, colors);
		adjacent = adjacent->next;
	}
	colors[vertex] = BLACK;
}

int depth_search(GRAPH *graph) {
	if(!graph)
		return FAILED;
	
	int *colors = (int *) malloc(graph->num_vertex * sizeof(int));
	
	int i = 0;
	for(i = 0; i < graph->num_vertex; i++) 
		colors[i] = WHITE;
	
	for(i = 0; i < graph->num_vertex; i++)
		if(colors[i] == WHITE)
			__depth_search(graph, i, colors);
}

int __breadth_search(GRAPH *graph, int vertex, int *colors) {
	colors[vertex] = GREY;

	
}

int breadth_search(GRAPH *graph) {
	if(!graph)
		return FAILED;
	
	int *colors = (int *) malloc(graph->num_vertex * sizeof(int));
	
	int i = 0;
	for(i = 0; i < graph->num_vertex; i++) 
		colors[i] = WHITE;
	
	for(i = 0; i < graph->num_vertex; i++)
		if(colors[i] == WHITE)
			__breadth_search(graph, i, colors);
}