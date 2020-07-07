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
#include <kevin_bacon.h>
#include <graph.h>

#define DEBUG 1

int show_menu();
void read_inputs(GRAPH *);

int main() {
	printf("construindo o grafo com o arquivo input-top-grossing.txt\n");
		/* Construir o grafo */
	GRAPH * graph = create_graph(); /* Cria o grafo */ 
	read_input(graph);

	/* Interação com o usuário */
	int result = 0;
	while(result != 3){
		result = show_menu();
		switch (result) {
			case 1:		/* consultar numero de KB */
				bfs(graph);
				break;
			case 2:		/* media e desvio padrao */

				break;
		}
	}

	printf("Finalizando execução e liberando o grafo ... \n");
	/* liberar grafo */
	return 0;
}

/* Funçoes */
int show_menu() {
	int result = 0;
	while(result < 1 || result > 3) {
		printf("\n");
		printf("|------------------------MENU------------------------|\n");
		printf("|1 - Consultar numero de Kevin Bacon de um ator/atriz|\n");
		printf("|2 - Média / Desvio Padrão do universo Kevin Bacon   |\n");
		printf("|3 - Sair do programa                                |\n");
		printf("|----------------------------------------------------|\n");
		scanf("%d", &result);
	}
	return result;
}

void read_input( GRAPH * graph) {
	FILE *arq_input = fopen("input-top-grossing.txt", "r");
	if(!arq_input) {
		printf("Erro ao abrir arquivo...\n");
		exit(0);
	}

	while(1) {
		char line[2000];
		strcpy(line, "");
		int i = 0;

		/* leitura das linhas por completo */
		char aux;
		while(fscanf(arq_input, "%c", &aux) != EOF && aux != '\n')
			line[i++] = aux;
		line[i] = '\0';

		if(i == 0) break;

		if(DEBUG)
			printf("[%d] %s\n", i, line);	/* linha toda */

		char *movie_name = strtok(line, "/");
		char *actor_name = strtok(NULL, "/");
		int *adjacentes = NULL;
		int count_adjacents = 0;

		/* Inserindo o filme no vetor de filmes do grafo */
		graph->num_movies++;
		graph->movies = (char **) realloc(graph->movies, (graph->num_movies * sizeof(char*)));
		graph->movies[graph->num_movies - 1] = (char *) malloc(60 * sizeof(char));
		strcpy(graph->movies[graph->num_movies - 1], movie_name);
		
		if(DEBUG)
			printf("Filme %s inserido\n", movie_name); 

		while(actor_name) {
			if(DEBUG)
				printf("\n\t%s\n", actor_name);

			int j, k;
			/* Verificando se o ator já foi colocado antes */
			for(j = 0; j < graph->num_vertex; j++) {
				if(!strcmp(actor_name, graph->vertex[j]))
					break; 
			}
			
			if(DEBUG)
				printf("O grafo tem %d vertices\n", graph->num_vertex);

			if(j == graph->num_vertex) {/* Neste caso, devemos inserir um novo ator */
				insertVertex(graph, actor_name);  
			} 
			
			adjacentes = (int *) realloc(adjacentes, (count_adjacents + 1) * sizeof(int));
			adjacentes[count_adjacents++] = j;
			actor_name = strtok(NULL, "/");


		}
		if(DEBUG){
			for(i = 0; i < count_adjacents ; i++)
				printf("%d ", adjacentes[i]);
			printf("\n");
		}

		/* Ligando as arestas */
		int j;
		for(i = 0; i < count_adjacents ; i++)
			for(j = i + 1; j < count_adjacents ; j++){
				/* graph->edges[i][j] = graph->edges[j][i] = graph->num_movies - 1; */
				insertEdge(graph, i, j, (graph->num_movies - 1));
			}
	}
	fclose(arq_input);
}


char ** insertVertex(GRAPH * graph, char * actor_name) {
	graph->num_vertex++;
	graph->vertex = (char **) realloc(graph->vertex, (graph->num_vertex * sizeof(char *)));
	graph->vertex[graph->num_vertex - 1] = (char *) malloc(100 * sizeof(char));
	strcpy(graph->vertex[graph->num_vertex - 1], actor_name);
	int k;
	if(DEBUG)
		printf("Adicionei %s\n", graph->vertex[graph->num_vertex - 1]);
	
	graph->edges = (int **) realloc(graph->edges, (graph->num_vertex * sizeof(int *)));	
	graph->edges[graph->num_vertex - 1] = NULL;

	for(k = 0; k < graph->num_vertex ; k++)
		graph->edges[k] = (int *) realloc(graph->edges[k], (graph->num_vertex * sizeof(int))); 
	

	for(k = 0; k < graph->num_vertex ; k++)
		graph->edges[graph->num_vertex -1][k] = graph->edges[k][graph->num_vertex -1] = VAZIO;
	
	return &graph->vertex[graph->num_vertex - 1];
}

int * insertEdge (GRAPH * graph, int v1, int v2, int elem) {
	graph->edges[v1][v2] = graph->edges[v2][v1] = elem;
	return &graph->edges[v1][v2];
}

int bfs(GRAPH * graph) {
	if(!graph){
		printf("Grafo inválido\n");
		exit(1);
	}

	char actorname[70];
	scanf(" %[^\n]s", actorname);
	printf("actor name: %s\n", actorname);
	int i;
	for(i = 0; i < graph->num_vertex; i++)
		if(!strcmp(graph->vertex[i], actorname)){
			printf("O ator existe no grafo :-)\n");
			return 1;
		}
	
	printf("O ator não existe no grafo :-(\n");
	return -1;
}

int _bfs(GRAPH * graph, int index) {

}