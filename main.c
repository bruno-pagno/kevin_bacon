/*
Nome: Bruno de Sousa Pagno		NUSP: 11366872
Nome: João Vitor de Mello Gomes	NUSP: 11218622
Professor: Elaine Parros Machado de Sousa
Disciplina: SCC0503
*/

/*
OBSERVAÇÕES:
    criei esse main.c pras funcoes entre os .h

	o valor das arestas vai ser o titulo do filme
	o valor dos vértices vai ser o nome do ator
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <graph.h>
#include <queue.h>

#define DEBUG 1
#define FILE_NAME "input-top-grossing.txt"

int showMenu();
void readInsertInputs(GRAPH *);
void printAdjacents(GRAPH *);

int main() {
	GRAPH * graph = create_graph(); /* Cria o grafo */ 
	readInsertInputs(graph);

	/* Interação com o usuário */
	int result = 1;
	while(result == 1 || result == 2){
		result = showMenu();
		switch(result) {
			case 1:
				printAdjacents(graph);
				break;
			case 2:
				kb_word(graph);
				break;
		}
	}

	if(DEBUG)
		printf("Result is %d\n", result);
	printf("Finalizando execução e liberando o grafo ... \n");
	/* liberar grafo */
	return 0;
}

/* Funçoes */
int showMenu() {
	int result = 0;
	printf("\n");
	printf("|------------------------MENU------------------------|\n");
	printf("|1 - Consultar numero de Kevin Bacon de um ator/atriz|\n");
	printf("|2 - Média / Desvio Padrão do universo Kevin Bacon   |\n");
	printf("|3 - Sair do programa                                |\n");
	printf("|----------------------------------------------------|\n");
	scanf("%d", &result);
	
	return result;
}

MOVIE * __newMovie(char movie_name[]) {
	MOVIE *movie = (MOVIE *) malloc(sizeof(MOVIE));
	strcpy(movie->movie_name, movie_name);
	movie->num_actors = 0;
	movie->actors_indexes = NULL;

	return movie;
}

void __addActor(MOVIE *movie, int index) {
	movie->actors_indexes = (int *) realloc(movie->actors_indexes, (movie->num_actors + 1) * sizeof(int));
	movie->actors_indexes[movie->num_actors++] = index;
}

void __addEdges(GRAPH *graph, MOVIE *movie) {
	int i = 0, j;
	int movie_index = getMovieIndex(graph, movie->movie_name);
	for(; i < movie->num_actors; i++)
		for(j = i + 1; j < movie->num_actors; j++) {
			insertEdge(graph, movie->actors_indexes[i], movie->actors_indexes[j], movie_index);
			insertEdge(graph, movie->actors_indexes[j], movie->actors_indexes[i], movie_index);
		}
	if(DEBUG) printf("%d atores relacionados\n", movie->num_actors);
		
}

void __readLine(FILE *arq_input, char line[]) {
	/* leitura das linhas por completo */
	char aux[2] = "\0";
	strcpy(line, "");
	while(fscanf(arq_input, "%c", &aux[0]) != EOF && aux[0] != '\n')
		strcat(line, aux);
}

void readInsertInputs(GRAPH * graph) {
	FILE *arq_input = fopen(FILE_NAME, "r");
	if(!arq_input) {
		printf("Erro ao abrir arquivo...\n");
		exit(0);
	}

	char line[2000];
	__readLine(arq_input, line);
	while(strlen(line)) {	/* para cada filme */
		line[strlen(line) - 1] = '\0';
		if(DEBUG) printf("\n\t%s\n", line);	/* linha toda */
		
		MOVIE *movie = __newMovie(strtok(line, "/"));

		char *actor_name = strtok(NULL, "/");
		while(actor_name) {	/* para cada ator */
			int actor_index = insertVertex(graph, actor_name);
			__addActor(movie, actor_index);

			if(DEBUG) printf("\t%4d) [%02d] {%s}\n", actor_index, strlen(actor_name), actor_name);
			
			actor_name = strtok(NULL, "/");
		}

		int movie_index = insertMovie(graph, movie->movie_name);
		if(DEBUG)
			printf("\t\tO filme %s é o %dº filme, com %d atores\n", movie->movie_name, movie_index + 1, movie->num_actors);

		__addEdges(graph, movie);

		__readLine(arq_input, line);
	}
	if(DEBUG)
		printf("%d atores contabilizados\n", graph->num_vertex);
}

void printAdjacents(GRAPH *graph) {
	char actor_name[30];
	printf("\tDigite o nome do ator: ");
	scanf(" %[^\n]s", actor_name);

	int actor_index = getActorIndex(graph, actor_name);
	int kevin_bacon_index = getActorIndex(graph, "Bacon, Kevin");


	if(actor_index == VAZIO)
		printf("Não encontrado...\n");
	else {
		int i = 0;
		printf("\n");
		
		/*
		for(; i < graph->num_vertex; i++) {
			int movie_index = graph->edges[actor_index][i];
			if(movie_index != VAZIO) {
				char other_actor[30];
				char movie_name[60];
				strcpy(other_actor, graph->actors_names[i]);
				strcpy(movie_name, graph->movies_names[movie_index]);

				printf("\t%s atuou com %s em %s\n", actor_name, other_actor, movie_name);
			}
		}
		*/
		printf("O ator tem indice %d e o Kevin Bacon tem indice %d\n", actor_index, kevin_bacon_index);

		/*  Criando o vetor de antecessores */
		int * vetAnt  = (int *) malloc(graph->num_vertex * sizeof(int));
		int * visited  = (int *) malloc(graph->num_vertex * sizeof(int));
		for(i =0; i < graph->num_vertex; i++) 
			vetAnt[i] = visited[i] = VAZIO;
		/*  Criando a pilha */
		QUEUE * queue = create_queue();
		/*  Colocando o valor inicial na pilha (Indice do ator desejado) */
		push_queue(queue, actor_index);
		/*  Enquanto houver pilha */
		while(queue->size) {
			int queueElem = pop_queue(queue);/*  Pega o elemento do topo da pilha */

			for(i = 0; i < graph->num_vertex; i++) { /* Passa por todos os elementos */
				if(graph->edges[queueElem][i] != VAZIO && vetAnt[i] == VAZIO && visited[i] != 1) { /* Se for adjancente*/
					vetAnt[i] = queueElem;
					push_queue(queue, i); /* Adiciona na pilha */
				}
			}
			visited[queueElem] = 1;
		}
		/* Vetor de antecessores finalizado */
		if(DEBUG)
			printf("Vetor de antecessores finalizado, vetant[kb] = %d\n", vetAnt[kevin_bacon_index]);

		if(DEBUG){
			for(i = 0; i < graph->num_vertex; i++)
				printf("[%d]%d ", i, vetAnt[i]);
			printf("\n");
		}

		int current = vetAnt[kevin_bacon_index];
		int caminho[100], count = 0;

		while(current != actor_index && current != -1) {
			caminho[count++] = current;
			current = vetAnt[current];
		}

		for(i = 0; i < count ; i++)
			printf("%s atuou com %s em %s\n", actor_name, graph->actors_names[caminho[i]], graph->movies_names[graph->edges[actor_index][caminho[i]]]);
		printf("%s atuou com %s em %s\n", graph->actors_names[caminho[count - 1]], graph->actors_names[kevin_bacon_index], graph->movies_names[graph->edges[kevin_bacon_index][caminho[count -1]]]);
		

		printf("%s tem kb = %d\n", actor_name, count);
	}
}


int kb_word(GRAPH * graph) {
	int kevin_bacon_index = getActorIndex(graph, "Bacon, Kevin");	
	int * kb_index  = (int *) malloc(graph->num_vertex * sizeof(int));
	int i, j;	
	for(i =0; i < graph->num_vertex; i++) 
		kb_index[i] = VAZIO;

	kb_index[kevin_bacon_index] = 0; /* Colocando zero no Indice de Kb do Kevin Bacon */
	int haveToContinue = 1, current_index = 0;
	
	/* Encontrando todos os indices de Kb */
	while(haveToContinue) {
		haveToContinue = 0;

		for(i = 0; i < graph->num_vertex; i++)
			if(kb_index[i] == current_index)
				for(j = 0; j < graph->num_vertex; j++)
					if(graph->edges[i][j] != VAZIO && kb_index[j] == VAZIO) {
						haveToContinue = 1;
						kb_index[j] = current_index + 1;
					}

		current_index++;
	}

	int sum = 0;

	if(DEBUG)
		printf("Achei todos os Kbs\n");

	for(i =0; i < graph->num_vertex; i++) 	{
		printf("%s tem Kb = %d\n", graph->actors_names[i], kb_index[i]);
		
		if(kb_index[i] != -1) 
			sum += kb_index[i]; 
	}
	float averageKb = (float) sum / graph->num_vertex;
	printf("A média de Kb dos atores é %.3f", averageKb);
}