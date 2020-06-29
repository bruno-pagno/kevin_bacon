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
typedef struct edge {
	int destination;
	int weight;
	struct edge *next;
} EDGE;

typedef struct {
	int num_vertex;
	EDGE **edges;
} GRAPH;

/* cabecalhos das funcoes */
GRAPH * create_graph(int);
int insert_edge(GRAPH *, int, int, int);
int exists_edge(GRAPH *, int, int);
int have_adjacent(GRAPH *, int);
EDGE * get_first_adjacent(GRAPH *, int);
int next_adjacent(GRAPH *, int, int);
int get_edge_weight(GRAPH *, int, int);
int remove_edge(GRAPH *, int, int);
void free_graph(GRAPH *);

#endif