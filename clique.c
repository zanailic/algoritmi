/* clique.c */

/* Direttive */
#include "clique.h"	

/* Aggiunge le coppie di grafo */
void fillQueueWithPairOfAutors(struct Queue** q, struct GraphNode* node)
{
	struct Queue* queue = *q;

	while (node != NULL)
	{
		struct GraphNeighbour* neighbour = node->neighbour;

		while (neighbour != NULL)
		{
			struct GraphNode* neighbourNode = neighbour->node;

			struct QueueElement* element = createQueueElement();
			addAutorToQueueElement(&element, node->autorName);
			addAutorToQueueElement(&element, neighbourNode->autorName);
			enqueue(queue, element);

			neighbour = neighbour->link;
		}
		node = node->next;
	}
	sortQueue(&queue);

	*q = queue;
}

/* Conesso tutte le coppie che esistono e li aggiungo tutti possibili nodi di grafo */
void addNewAutorsConnectionToQueue(struct Queue** q, struct GraphNode* node)
{
    struct Queue* helpQueue;
	struct Queue* queue = *q;

	bool connectedFlag = false;
	while (node != NULL)
	{
		if (node->neighbour == NULL)
		{
			node = node->next;
			continue;
		}

		helpQueue = createQueue(queue->capacity);

		while (!isEmpty(queue))
		{
			struct QueueElement* element = dequeue(queue);

			/* Controllo se elemento (autore) e' conesso con la coppia data */
			connectedFlag = checkIfAutorisConnectedWithGivenAutors(element, node);
			/* Se sono conessi, aggiungo nuovo elemento (autore) in sottoinsieme */
			if (connectedFlag)
			{
				addAutorToQueueElement(&element, node->autorName);
			}
			/* Ritorno sottoinsieme indietro in helpQueue */
			enqueue(helpQueue, element);
		}

		queue = helpQueue;
		node = node->next;
	}

	sortQueue(&queue);

	*q = queue;
}

/* Controllo se autore e gli altri autori dati sono conessi cioe' se sono vicini */
bool checkIfAutorisConnectedWithGivenAutors(struct QueueElement* element, struct GraphNode* node)
{
    int i;
	bool connectedFlag = true;
	for (i = 0; (i < element->numberOfAutors) && connectedFlag; i++)
	{
		char* elementAutorName = element->autors[i];

		struct GraphNeighbour* neighbour = node->neighbour;
		connectedFlag = false;
		while ((neighbour != NULL) && !connectedFlag)
		{
			struct GraphNode* neighbourNode = neighbour->node;

			if (strcmp(elementAutorName, neighbourNode->autorName) == 0)
			{
				connectedFlag = true;
			}
			neighbour = neighbour->link;
		}
	}

	return connectedFlag;
}

void sortQueue(struct Queue** q)
{
    int i, j, k;
	struct Queue* queue = *q;
	struct QueueElement** helperArray = calloc(queue->size, sizeof(struct QueueElement*));
	int n = 0;

	/* Metto in ordine */
	while (!isEmpty(queue))
	{
		struct QueueElement* element = dequeue(queue);

		int i;
		for (i = n - 1; i >= 0 && element->numberOfAutors > helperArray[i]->numberOfAutors; i--)
		{
			helperArray[i + 1] = helperArray[i];
		}
		
		helperArray[i + 1] = element;
		n++;
	}

	/* Rimuovo tutti i duplicati */
	for (i = 0; i < n; i++)
	{
		for (j = i + 1; j < n; )
		{
			if (checkIfQueueElementsAreEqual(helperArray[j], helperArray[i])) {
				for (k = j; k < n; k++)
				{
					helperArray[k] = helperArray[k + 1];
				}
				n--;
			}
			else
			{
				j++;
			}
		}
	}

	/* Aggiungo in coda */
	for (i = 0; i < n; i++)
	{
		enqueue(queue, helperArray[i]);
	}

	*q = queue;
}

/* Controllo se elementi in coda sono uguali */
bool checkIfQueueElementsAreEqual(struct QueueElement* a, struct QueueElement* b)
{
    int i;

	if (a->numberOfAutors != b->numberOfAutors)
	{
		return false;
	}

	for (i = 0; i < a->numberOfAutors; i++)
	{
		if (strcmp(a->autors[i], b->autors[i]) != 0) 
		{
			return false;
		}
	}

	return true;
}

/* Numero di clique massimali */
int getCliqueMaximumNumber(struct Queue* queue)
{
	struct QueueElement* front = queueFront(queue);

	return front->numberOfAutors;
}
