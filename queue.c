/* queue.c */

/* Direttive */
#include "queue.h"

/* Funzione per creazione di coda con data capacita' */
/* Al inizio size = 0 */
struct Queue* createQueue(unsigned capacity)
{
	struct Queue* queue = (struct Queue*) malloc(sizeof(struct Queue));
	queue->capacity = capacity;
	queue->front = queue->size = 0;
	queue->rear = capacity - 1;
	queue->array = (struct QueueElement**)malloc(queue->capacity * sizeof(struct QueueElement**));
	return queue;
}

/* Pieno quando size = capacity */
int isFull(struct Queue* queue)
{
	return (queue->size == queue->capacity);
}

/* Vuoto quando size = 0 */
int isEmpty(struct Queue* queue)
{
	return (queue->size == 0);
}

/* Aggiunge un elemento in coda */
void enqueue(struct Queue* queue, struct QueueElement* item)
{
	if (isFull(queue)) 
	{
		return;
	}

	queue->rear = (queue->rear + 1) % queue->capacity;
	queue->array[queue->rear] = item;
	queue->size = queue->size + 1;
}

/* Rimuove elemento da coda */
struct QueueElement* dequeue(struct Queue* queue)
{
    struct QueueElement* item;

	if (isEmpty(queue))
	{
		return NULL;
	}

	item = queue->array[queue->front];
	queue->front = (queue->front + 1) % queue->capacity;
	queue->size = queue->size - 1;
	return item;
}

/* Va al inizio della coda */
struct QueueElement* queueFront(struct Queue* queue)
{
	if (isEmpty(queue))
	{
		return NULL;
	}

	return queue->array[queue->front];
}

/* Va alla fine della coda */
struct QueueElement* queueRear(struct Queue* queue)
{
	if (isEmpty(queue))
	{
		return NULL;
	}

	return queue->array[queue->rear];
}

/* Crea un elemento per la coda */
struct QueueElement* createQueueElement()
{
	struct QueueElement* element = calloc(10, sizeof(struct QueueElement*));

	element->numberOfAutors = 0;
	element->autors = calloc(100, sizeof(char*));
	
	return element;
}

/* Aggiunge autore come elemento di coda */
void addAutorToQueueElement(struct QueueElement** el, char* name)
{
	struct QueueElement* element = *el;
	int numberOfAutors = element->numberOfAutors;

	/* Lo aggiunge in ordine */
	int i;
	for (i = numberOfAutors - 1; i >= 0 && (strcmp(element->autors[i], name) > 0); i--)
	{
		element->autors[i + 1] = element->autors[i];
	}
	
	element->autors[i + 1] = name;
	element->numberOfAutors++;

	*el = element;
}

/* Stampa la coda */
void printQueue(struct Queue* queue)
{
    int i;

	while (!isEmpty(queue))
	{
		struct QueueElement* element = dequeue(queue);
		for (i = 0; i < element->numberOfAutors; i++)
		{
			printf("%s ", element->autors[i]);
		}
		printf("\n");
	}
}

/* Calcola numero di sottoinsiemi e stampa la coda  */
void calculateSubsetNumberAndPrintQueue(struct Queue* queue)
{
	int i;
	int subsetMax = 0;
	int subsetCount = 1;
	
	while (!isEmpty(queue))
	{
		struct QueueElement* element = dequeue(queue);
		if (element->numberOfAutors > subsetMax) 
		{
			subsetMax = element->numberOfAutors;
		} 
		else if (element->numberOfAutors == subsetMax)
		{
			subsetCount++;
		}
		
		for (i = 0; i < element->numberOfAutors-1; i++)
		{
			printf("%s ", element->autors[i]);
			printf("& ");
		}
		printf("%s ", element->autors[element->numberOfAutors-1]);
		printf("\n");
	}

	printf("\nSottoinsiemi %d\n", subsetCount);
}
