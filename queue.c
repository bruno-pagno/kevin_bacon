#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

/* cria uma fila com todas as variaveis inicializadas */
QUEUE * create_queue() {
	return (QUEUE *) calloc(1, sizeof(QUEUE));
}

/* insercao no fim da fila */
int push_queue(QUEUE *queue, int newValue) {
	if(!queue)
		return FAILED;

	QUEUE_ELEM **element = &queue->first;
	while(*element)
		element = &(*element)->next;
	
	QUEUE_ELEM *new_element = (QUEUE_ELEM *) malloc(sizeof(QUEUE_ELEM));
	new_element->next = NULL;
	new_element->value = newValue;
	*element = new_element;

	queue->size++;
	return SUCCESS;
}

/* remocao e retorno do primeiro elemento */
int pop_queue(QUEUE *queue) {
	if(!queue) 
		return FAILED;

	if(!queue->size) 
		return EMPTY;

	QUEUE_ELEM *first = queue->first;
	queue->first = queue->first->next;
	queue->size--;

	return first->value;
}

/* mostra a fila */
int display_queue(QUEUE *queue) {
	if(!queue) 
		return FAILED;

	printf("Fila com %d elementos: [ ", queue->size);
	QUEUE_ELEM *element = queue->first;
	while(element) {
		printf("%d ", element->value);
		element = element->next;
	}
	printf("]\n");

	return SUCCESS;
}

void free_queue(QUEUE *queue) {
	if(queue) {
		while(queue->first) {
			QUEUE_ELEM *aux = queue->first;
			queue->first = aux->next;
			free(aux);
		}

		free(queue);
		queue = NULL;
	}
}