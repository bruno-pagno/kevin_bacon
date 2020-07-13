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

void getKevinBaconNumber(GRAPH *graph) {
	char actor_name[30];
	printf("\tDigite o nome do ator: ");
	scanf(" %[^\n]s", actor_name);

	int actor_index = getActorIndex(graph, actor_name);
	int kevin_bacon_index = getActorIndex(graph, "Bacon, Kevin");

	if(actor_index == kevin_bacon_index)
		printf("\tEste é o próprio Kevin Bacon!\n");
	
	else if(actor_index == VAZIO)
		printf("\tNão possui ligação com Kevin Bacon...\n");
	
	else {
		if(GRAPH_DEBUG)
			printf("\nO ator tem indice %d e o Kevin Bacon tem indice %d\n", actor_index, kevin_bacon_index);

		/*  Criando o vetor de antecessores */
		int *vetAnt  = (int *) malloc(graph->num_vertex * sizeof(int));
		int *visited  = (int *) malloc(graph->num_vertex * sizeof(int));
		int i = 0;
		for(; i < graph->num_vertex; i++) {
			vetAnt[i] = VAZIO;
			visited[i] = 0;
		}
		
		/*  Criando a fila e colocando o indice do ator*/
		QUEUE * queue = create_queue();
		push_queue(queue, actor_index);

		/*  Enquanto a fila nao estiver vazia */
		while(queue->size) {
			int queueElem = pop_queue(queue);	/*  Pega o elemento do topo da fila */

			for(i = 0; i < graph->num_vertex; i++) {	/* Passa por todos os elementos */
				if(graph->edges[queueElem][i] != VAZIO && vetAnt[i] == VAZIO && !visited[i]) {
					/* se for adjacente E nao foi passado no caminho E nao foi visitado */
					vetAnt[i] = queueElem;	/* faz o adjacente ter o atual como anterior */
					push_queue(queue, i);	/* Adiciona na fila */
				}
			}

			/* marca como visitado */
			visited[queueElem] = 1;
		}

		/* Vetor de antecessores finalizado */
		if(GRAPH_DEBUG) printf("Vetor de antecessores finalizado, vetant[kb] = %d\n", vetAnt[kevin_bacon_index]);

		if(GRAPH_DEBUG){
			for(i = 0; i < graph->num_vertex; i++)
				printf("[%d]%d\n", i, vetAnt[i]);
			printf("\n");
		}

		if(vetAnt[kevin_bacon_index] == VAZIO) {
			printf("\tNão possui ligação com Kevin Bacon...\n");
			return;
		}

		int current = kevin_bacon_index;
		int caminho[100], count = 0;

		while(current != -1) {
			caminho[count++] = current;
			current = vetAnt[current];
		}

		printf("\n");
		char first_name[50], second_name[50], movie_name[60];
		for(i = count - 1; i > 0; i--) {
			strcpy(first_name, graph->actors_names[caminho[i-1]]);
			strcpy(second_name, graph->actors_names[caminho[i]]);

			int movie_index = graph->edges[caminho[i-1]][caminho[i]];
			strcpy(movie_name, graph->movies_names[movie_index]);

			printf("\t%s atuou com %s em %s\n", second_name, first_name, movie_name);
		}
		
		printf("\n\t%s tem kb = %d\n", actor_name, count-1);
	}
}