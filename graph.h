#ifndef _GRAPH_
#define _GRAPH_

/* macros que definem os retornos de erro */
#define SUCCESS		0
#define FAILED		-1
#define INDEX_ERROR	-2
#define NOT_FOUND	-3

#define VAZIO  -1

/* cores da visitação */
#define WHITE	0
#define GREY	1
#define BLACK	2

#define MAX_VERTEX 8300
#define MAX_MOVIES 200

/* estrutura auxiliar de filme */
typedef struct {
	char movie_name[60];
	int num_actors;
	int *actors_indexes;
} MOVIE;

/* estruturas que compoem o grafo */
typedef struct {
	int num_vertex, num_movies;
	char *actors_names[MAX_VERTEX];			/* Guarda os vértices */
	char *movies_names[MAX_MOVIES];
	int edges[MAX_VERTEX][MAX_VERTEX];		/* Guarda as arestas com os filmes */
} GRAPH;

/* cabecalhos das funcoes */
GRAPH * create_graph();

int getActorIndex(GRAPH *, char *);
int getActorIndex(GRAPH *, char *);

int insertVertex(GRAPH *, char *);
int insertMovie(GRAPH *, char *);
int * insertEdge (GRAPH *, int, int, int);

void breadth_search(GRAPH *);
int kb_word(GRAPH * graph);


/* funcoes pedidas 
VERTEX * end_vertex(GRAPH *, EDGE *);
VERTEX * opposite(GRAPH *, VERTEX *, EDGE *);
int are_adjacent(GRAPH *, VERTEX *, VERTEX *);
int replace_edge(GRAPH *, EDGE *, char *);
int replace_vertex(GRAPH *, VERTEX *, char *);
char * edge_value(GRAPH *, EDGE *);
char * vertex_value(GRAPH *, VERTEX *); 
*/
void free_graph(GRAPH *);

#endif