#include <stdlib.h>
#include <string.h>
#include <graph.h>

/* criacao e inicializacao do grafo */
GRAPH * create_graph() {
	return (GRAPH *) calloc(1, sizeof(GRAPH));
}