#ifndef _GRAPH_
#define _GRAPH_

/* macros que definem os retornos de erro */
#define SUCCESS		0
#define FAILED		-1
#define INDEX_ERROR	-2
#define NOT_FOUND	-3
#define KEVIN_BACON	-4

#define VAZIO  -1

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
	char *actors_names[MAX_VERTEX];		/* Guarda os vértices */
	char *movies_names[MAX_MOVIES];
	int edges[MAX_VERTEX][MAX_VERTEX];	/* Guarda as arestas com os filmes */
} GRAPH;

/* cabecalhos das funcoes */
GRAPH * create_graph();

int insert_vertex(GRAPH *, char *);
int replace_vertex(GRAPH *, int, char *);
char * vertex_value(GRAPH *, int);

int * end_vertex(GRAPH *, int, int);
int * opposite(GRAPH *, int, int);

int * insert_edge(GRAPH *, int, int, int);
int replace_edge(GRAPH *, int, int, int);
int edge_value(GRAPH *, int, int);

int insert_movie(GRAPH *, char *);

int are_adjacent(GRAPH *, int, int);

int get_actor_index(GRAPH *, char *);
int get_movie_index(GRAPH *, char *);

int get_kevin_bacon_number(GRAPH *, char *, int []);
float * get_kevin_bacon_average(GRAPH *);

void free_graph(GRAPH *);

#endif