#ifndef __queue_h
#define __queue_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bool.h"

struct QueueElement {
	int numberOfAutors;
	char** autors;
};

/* Struttura per la rapressentazione di coda */
struct Queue {
	int front, rear, size;
	unsigned capacity;
	struct QueueElement** array;
};

struct Queue* createQueue(unsigned capacity);

int isFull(struct Queue* queue);

int isEmpty(struct Queue* queue);

void enqueue(struct Queue* queue, struct QueueElement* item);

struct QueueElement* dequeue(struct Queue* queue);

struct QueueElement* queueFront(struct Queue* queue);

struct QueueElement* queueRear(struct Queue* queue);

struct QueueElement* createQueueElement();

void addAutorToQueueElement(struct QueueElement** el, char* name);

void printQueue(struct Queue* queue);

void calculateSubsetNumberAndPrintQueue(struct Queue* queue);

#endif
