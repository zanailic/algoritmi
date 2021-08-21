#ifndef __clique_h
#define __clique_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

#include "graph.h"
#include "queue.h"
#include "bool.h"

void fillQueueWithPairOfAutors(struct Queue** q, struct GraphNode* node);

void addNewAutorsConnectionToQueue(struct Queue** q, struct GraphNode* node);

bool checkIfAutorisConnectedWithGivenAutors(struct QueueElement* element, struct GraphNode* node);

bool checkIfQueueElementsAreEqual(struct QueueElement* a, struct QueueElement* b);

void sortQueue(struct Queue** q);

int getCliqueMaximumNumber(struct Queue* queue);

#endif
