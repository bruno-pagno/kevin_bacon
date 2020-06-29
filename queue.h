#ifndef _QUEUE_
#define _QUEUE_

/* retornos de erro */
#define SUCCESS	0
#define FAILED	-1
#define EMPTY	-2

/* estrutura de um elemento da fila */
typedef struct queue_elem {
	struct queue_elem *next;
	int value;
} QUEUE_ELEM;

/* cabecalho da fila */
typedef struct {
	int size;
	QUEUE_ELEM *first;
} QUEUE;

/* funcoes da fila */
QUEUE * create_queue();
int push_queue(QUEUE *, int);
int pop_queue(QUEUE *);
int display_queue(QUEUE *);
void free_queue(QUEUE *);

#endif