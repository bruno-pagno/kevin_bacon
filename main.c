/*
Nome: Bruno de Sousa Pagno		NUSP: 11366872
Nome: João Vitor de Mello Gomes	NUSP: 11218622
Professor: Elaine Parros Machado de Sousa
Disciplina: SCC0503
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <graph.h>

#define FILE_NAME "input-top-grossing.txt"

int show_menu();
void read_inputs(GRAPH *);
void kevin_bacon_number(GRAPH *);
void kevin_bacon_average(GRAPH *);

int main() {
	GRAPH * graph = create_graph();		/* Cria o grafo */ 
	read_inputs(graph);

	/* interacao com o usuario */
	int result = 1;
	while(result == 1 || result == 2){
		result = show_menu();
		switch(result) {
			case 1:
				kevin_bacon_number(graph);
				break;
			case 2:
				kevin_bacon_average(graph);
				break;
		}
	}

	printf("\n\tFinalizando execução e liberando o grafo...\n\n");
	/* liberar grafo */
	free_graph(graph);
	return 0;
}

/* funcoes auxiliares */
MOVIE * __new_movie(char movie_name[]) {
	MOVIE *movie = (MOVIE *) malloc(sizeof(MOVIE));
	strcpy(movie->movie_name, movie_name);
	movie->num_actors = 0;
	movie->actors_indexes = NULL;

	return movie;
}

void __add_actor(MOVIE *movie, int index) {
	movie->actors_indexes = (int *) realloc(movie->actors_indexes, (movie->num_actors + 1) * sizeof(int));
	movie->actors_indexes[movie->num_actors++] = index;
}

void __add_edges(GRAPH *graph, MOVIE *movie) {
	int i = 0, j;
	int movie_index = get_movie_index(graph, movie->movie_name);
	for(; i < movie->num_actors; i++)
		for(j = i + 1; j < movie->num_actors; j++) {
			insert_edge(graph, movie->actors_indexes[i], movie->actors_indexes[j], movie_index);
			insert_edge(graph, movie->actors_indexes[j], movie->actors_indexes[i], movie_index);
		}
		
}

void __read_line(FILE *arq_input, char line[]) {
	/* leitura das linhas por completo */
	char aux[2] = "\0";
	strcpy(line, "");
	while(fscanf(arq_input, "%c", &aux[0]) != EOF && aux[0] != '\n')
		strcat(line, aux);
}

/* funcoes principais */
int show_menu() {
	int result = 0;
	printf("\n");
	printf("|------------------------MENU------------------------|\n");
	printf("|1 - Consultar numero de Kevin Bacon de um ator/atriz|\n");
	printf("|2 - Média / Desvio Padrão do universo Kevin Bacon   |\n");
	printf("|3 - Sair do programa                                |\n");
	printf("|----------------------------------------------------|\n");
	printf("Opção: ");
	scanf("%d", &result);
	
	return result;
}

void read_inputs(GRAPH * graph) {
	FILE *arq_input = fopen(FILE_NAME, "r");
	if(!arq_input) {
		printf("Erro ao abrir arquivo...\n");
		exit(0);
	}

	char line[2000];
	__read_line(arq_input, line);
	while(strlen(line)) {	/* para cada filme */
		line[strlen(line) - 1] = '\0';
		
		MOVIE *movie = __new_movie(strtok(line, "/"));

		char *actor_name = strtok(NULL, "/");
		while(actor_name) {	/* para cada ator */
			int actor_index = insert_vertex(graph, actor_name);
			__add_actor(movie, actor_index);
			
			actor_name = strtok(NULL, "/");
		}

		insert_movie(graph, movie->movie_name);
		__add_edges(graph, movie);

		free(movie);
		__read_line(arq_input, line);
	}
	
	fclose(arq_input);
}

void kevin_bacon_number(GRAPH *graph) {
	char actor_name[30];
	printf("\n\tDigite o nome do ator: ");
	scanf(" %[^\n]s", actor_name);

	int path[100];
	int result = get_kevin_bacon_number(graph, actor_name, path);

	if(result == KEVIN_BACON)
		printf("\tEste é o próprio Kevin Bacon!\n");

	else if(result == NOT_FOUND)
		printf("\tEste ator não tem ligação com Kevin Bacon...\n");

	else if(result > 0) {
		printf("\n");
		char actor_name2[50], actor_name1[50], movie_name[60];
		int i = result - 1;

		for(; i > 0; i--) {
			strcpy(actor_name1, graph->actors_names[path[i]]);
			strcpy(actor_name2, graph->actors_names[path[i-1]]);

			int movie_index = graph->edges[path[i-1]][path[i]];
			strcpy(movie_name, graph->movies_names[movie_index]);

			printf("\t%s atuou com %s em %s\n", actor_name1, actor_name2, movie_name);
		}
		
		printf("\n\t%s tem KB = %d\n", actor_name, result - 1);
	}
}

void kevin_bacon_average(GRAPH *graph) {
	float *results = get_kevin_bacon_average(graph);
	printf("\n\tMédia de KB = %.4f\n", results[0]);
	printf("\tDesvio padrão de KB = %.4f\n", results[1]);
}
