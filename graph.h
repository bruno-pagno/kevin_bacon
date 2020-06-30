#ifndef _GRAPH_
#define _GRAPH_

/* macros que definem os retornos de erro */
#define SUCCESS		0
#define FAILED		-1
#define INDEX_ERROR	-2
#define NOT_FOUND	-3

/* cores da visitação */
#define WHITE	0
#define GREY	1
#define BLACK	2

/* estruturas que compoem o grafo */
typedef struct {
	int index;
	char *actor_name;
} VERTEX;

typedef struct edge {
	VERTEX *origin, *destination;
	char *movie_name;
	struct edge *next;
} EDGE;

typedef struct {
	int num_vertex;
	EDGE **edges;
	VERTEX **vertex;
} GRAPH;

/* cabecalhos das funcoes */
GRAPH * create_graph();
int insert_edge(GRAPH *, int, int, int);
int exists_edge(GRAPH *, int, int);
int have_adjacent(GRAPH *, int);
EDGE * get_first_adjacent(GRAPH *, int);
int next_adjacent(GRAPH *, int, int);
int get_edge_weight(GRAPH *, int, int);
int remove_edge(GRAPH *, int, int);
void free_graph(GRAPH *);

/* funcoes pedidas */
VERTEX * end_vertex(GRAPH *, EDGE *);
VERTEX * opposite(GRAPH *, VERTEX *, EDGE *);
int are_adjacent(GRAPH *, VERTEX *, VERTEX *);
VERTEX * insert_vertex(GRAPH *, char *);
EDGE * insert_edge2(GRAPH *, VERTEX *, VERTEX *, char *);
int replace_edge(GRAPH *, EDGE *, char *);
int replace_vertex(GRAPH *, VERTEX *, char *);
char * edge_value(GRAPH *, EDGE *);
char * vertex_value(GRAPH *, VERTEX *);

#endif