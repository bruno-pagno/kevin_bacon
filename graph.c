/*
Nome: Bruno de Sousa Pagno		NUSP: 11366872
Nome: João Vitor de Mello Gomes	NUSP: 11218622
Professor: Elaine Parros Machado de Sousa
Disciplina: SCC0503
*/

#include <stdlib.h>
#include <string.h>
#include <graph.h>
#include <queue.h>
#include <math.h>

/* criacao e inicializacao do grafo */
GRAPH * create_graph() {
	GRAPH *new_graph = (GRAPH *) calloc(1, sizeof(GRAPH));

	int i = 0, j;
	for(; i < MAX_VERTEX; i++)
		for(j = i; j < MAX_VERTEX; j++)		/* preenche tudo com VAZIO */
			new_graph->edges[i][j] = new_graph->edges[j][i] = VAZIO;
}

/* insere um nome de ator no vetor de vertices e retorna seu indice */
int insert_vertex(GRAPH *graph, char * actor_name) {
	int actor_index = get_actor_index(graph, actor_name);

	if(actor_index == -1) {	/* nao existe */
		graph->actors_names[graph->num_vertex] = (char *) malloc(50 * sizeof(char));
		strcpy(graph->actors_names[graph->num_vertex++], actor_name);
		return graph->num_vertex - 1;
	}

	return actor_index;
}

/* substitui o valor de um vertice */
int replace_vertex(GRAPH * graph, int vertex_index, char * newName) {
	if(!graph)return -3;
	strcpy(graph->actors_names[vertex_index], newName);
	return 1;
}

/* retorna o valor do vertice */
char * vertex_value(GRAPH * graph, int pos) {
	if(!graph) return NULL;
	return graph->actors_names[pos];	
}

/* retorna a referencia para os dois extremos da aresta */
int * end_vertex(GRAPH *graph, int v1, int v2){
	int **results = (int **) malloc(2 * sizeof(int *));
	results[0] = &v1;
	results[1] = &v2;
	return results;
}

/* retorna o vertice oposto */
int * opposite(GRAPH *graph, int origin, int edge) {
	int i = 0;
	for(; i < graph->num_vertex; i++)
		if(graph->edges[origin][i] == edge)
			return &graph->edges[origin][i];
	return NULL;
}

/* insere uma aresta ligando dois atores pelo indice do filme */
int * insert_edge (GRAPH *graph, int v1, int v2, int movie_index) {
	graph->edges[v1][v2] = movie_index;
	graph->edges[v2][v1] = movie_index;
	return &graph->edges[v1][v2];
}

/* substitui o valor da aresta */
int replace_edge(GRAPH * graph, int v1, int v2, int elem) {
	if(!graph) return -3;
	graph->edges[v1][v2] = elem;
	return 1;
}

/* retorna o valor da aresta */
int edge_value(GRAPH * graph, int v1, int v2) {
	if(!graph) return -3;
	return graph->edges[v1][v2];
}

/* insere um nome de filme no vetor de filmes e retorna seu indice */
int insert_movie(GRAPH *graph, char *movie_name) {
	graph->movies_names[graph->num_movies] = (char *) malloc(50 * sizeof(char));
	strcpy(graph->movies_names[graph->num_movies++], movie_name);

	return graph->num_movies - 1;
}

/* retorna de dois vertices sao adjacentes */
int are_adjacent(GRAPH * graph, int v1, int v2) {
	return graph->edges[v1][v2] != VAZIO ;
}

/* retorna o indice de um ator */
int get_actor_index(GRAPH *graph, char *actor_name) {
	int index = 0;
	for(; index < graph->num_vertex; index++)
		if(!strcmp(actor_name, graph->actors_names[index]))
			break;

	if(index == graph->num_vertex)
		return -1;
	return index;
}

/* retorna o indice de um filme */
int get_movie_index(GRAPH *graph, char *movie_name) {
	int index = 0;
	for(; index < graph->num_movies; index++)
		if(!strcmp(movie_name, graph->movies_names[index]))
			break;

	if(index == graph->num_movies)
		return -1;
	return index;
}

/* calcula o numero de kb de um ator */
int get_kevin_bacon_number(GRAPH *graph, char *actor_name, int path[]) {
	int actor_index = get_actor_index(graph, actor_name);
	int kevin_bacon_index = get_actor_index(graph, "Bacon, Kevin");

	if(actor_index == kevin_bacon_index)
		return KEVIN_BACON;
	
	else if(actor_index == VAZIO)
		return NOT_FOUND;
	
	/*  Criando o vetor de antecessores */
	int *vetAnt  = (int *) malloc(graph->num_vertex * sizeof(int));
	int *visited  = (int *) calloc(graph->num_vertex, sizeof(int));
	int i = 0;
	for(; i < graph->num_vertex; i++) {
		vetAnt[i] = VAZIO;
	}
	
	/*  Criando a fila e colocando o indice do ator*/
	QUEUE * queue = create_queue();
	push_queue(queue, actor_index);

	/*  Enquanto a fila nao estiver vazia */
	while(queue->size) {
		int queueElem = pop_queue(queue);	/*  Pega o elemento do topo da fila */

		for(i = 0; i < graph->num_vertex; i++) {	/* Passa por todos os elementos */
			if(graph->edges[queueElem][i] != VAZIO && vetAnt[i] == VAZIO && !visited[i]) {
				/* se for adjacente E nao foi passado no path E nao foi visitado */
				vetAnt[i] = queueElem;	/* faz o adjacente ter o atual como anterior */
				push_queue(queue, i);	/* Adiciona na fila */
			}
		}

		/* marca como visitado */
		visited[queueElem] = 1;
	}

	if(vetAnt[kevin_bacon_index] == VAZIO) 
		return NOT_FOUND;

	int current = kevin_bacon_index, path_size = 0;

	while(current != -1) {
		path[path_size++] = current;
		current = vetAnt[current];
	}

	return path_size;
}

/* calcula media e desvio padrao */
float * get_kevin_bacon_average(GRAPH * graph) {
	int kevin_bacon_index = get_actor_index(graph, "Bacon, Kevin");	
	int * kb_index  = (int *) malloc(graph->num_vertex * sizeof(int));
	int i = 0;	
	for(; i < graph->num_vertex; i++) 
		kb_index[i] = VAZIO;

	kb_index[kevin_bacon_index] = 0; /* Colocando zero no Indice de Kb do Kevin Bacon */
	int flag_continue = 1, current_index = 0;
	
	/* Encontrando todos os indices de Kb */
	while(flag_continue) {
		flag_continue = 0;
		int j = 0;
		for(i = 0; i < graph->num_vertex; i++)
			if(kb_index[i] == current_index)
				for(j = 0; j < graph->num_vertex; j++)
					if(are_adjacent(graph, i, j) && kb_index[j] == VAZIO) {
						flag_continue = 1;
						kb_index[j] = current_index + 1;
					}
		current_index++;
	}

	float *result = (float *) malloc(2 * sizeof(float));

	float sum = 0.0;
	for(i = 0; i < graph->num_vertex; i++)
		if(kb_index[i] != VAZIO) 
			sum += kb_index[i];

	result[0] = (float) sum / graph->num_vertex;	/* media */

	sum = 0.0;
	for(i = 0; i < graph->num_vertex; i++)
		if(kb_index[i] != VAZIO) 
			sum += (kb_index[i] - result[0]) * (kb_index[i] - result[0]);
	
	result[1] = sqrt((double) sum / graph->num_vertex);	/* desvio padrao */

	return result;
}

/* libera toda a estrutura */
void free_graph(GRAPH *graph) {
	if(graph) {
		while(graph->num_vertex--)
			free(graph->actors_names[graph->num_vertex]);
		
		while(graph->num_movies--)
			free(graph->movies_names[graph->num_movies]);
		
		free(graph);
		graph = NULL;
	}
}