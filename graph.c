/* graph.c */

/* Direttive */
#include "graph.h"

/* Crea grafo - all inizio vuoto */
struct Graph* createGraph()
{
	struct Graph* graph = malloc(sizeof(struct Graph*));
	graph->start = NULL;
	graph->numberOfNodes = 0;

	return graph;
}

/* Crea nuovo nodo in grafo */
struct GraphNode* createGraphNode(char* autorName)
{
	struct GraphNode* graphNode = calloc(10, sizeof(struct GraphNode*));

	graphNode->autorName = autorName;
	graphNode->next = NULL;
	graphNode->neighbour = NULL;

	return graphNode;
}

struct GraphNeighbour* createGraphNeighbour(struct GraphNode* node)
{
	struct GraphNeighbour* graphNeighbour = calloc(10, sizeof(struct GraphNeighbour*));
	
	graphNeighbour->node = node;
	graphNeighbour->link = NULL;

	return graphNeighbour;
}

/* Aggiunge nodo in grafo */
void addNodeToGraph(struct Graph** g, struct GraphNode* node)
{
	struct Graph* graph = *g;

	struct GraphNode* graphNode = graph->start;

	if (graphNode == NULL) {
		graph->start = node;
	}
	else {
		while (graphNode->next != NULL)
		{
			graphNode = graphNode->next;
		}
		graphNode->next = node;
	}

	graph->numberOfNodes++;

	*g = graph;
}

/* Aggiunge vicino per nodo */
void addNeighbourToNode(struct GraphNode** gNode, struct GraphNeighbour* neighbour)
{
	struct GraphNode* graphNode = *gNode;

	struct GraphNeighbour* neighbourNode = graphNode->neighbour;

	if (neighbourNode == NULL) {
		graphNode->neighbour = neighbour;
	}
	else {
		while (neighbourNode->link != NULL)
		{
			neighbourNode = neighbourNode->link;
		}
		neighbourNode->link = neighbour;
	}

	*gNode = graphNode;
}

/* Trova nodo con dato nome di autore */
struct GraphNode* findNodeInGraphByName(struct Graph* graph, char* autorName)
{
	struct GraphNode* graphNode = graph->start;

	if (graphNode == NULL)
	{
		return NULL;
	}

	while (graphNode != NULL)
	{
		if (strcmp(graphNode->autorName, autorName) == 0)
		{
			return graphNode;
		}

		graphNode = graphNode->next;
	}

	return NULL;
}

struct GraphNode* findNodeInGraphByNode(struct Graph* graph, struct GraphNode* node)
{
	struct GraphNode* graphNode = graph->start;

	if (graphNode == NULL)
	{
		return NULL;
	}

	while (graphNode != NULL)
	{
		if (graphNode == node)
		{
			return graphNode;
		}

		graphNode = graphNode->next;
	}

	return NULL;
}

struct GraphNeighbour* findNeighbourForNode(struct GraphNode* graphNode, struct GraphNode* targetNode)
{
	struct GraphNeighbour* graphNeighbour = graphNode->neighbour;

	if (graphNeighbour == NULL)
	{
		return NULL;
	}

	while (graphNeighbour != NULL)
	{
		struct GraphNode* node = graphNeighbour->node;

		if (node == targetNode)
		{
			return graphNeighbour;
		}

		graphNeighbour = graphNeighbour->link;
	}

	return NULL;

}

/* Stampa nodi */
void printNodes(struct Graph* graph)
{
    struct GraphNeighbour* neighbour;
	struct GraphNode* graphNode = graph->start;

	while (graphNode != NULL)
	{
		printf("\nNODE ---> NAME:%s, NEIGHBOURS:", graphNode->autorName);

		neighbour = graphNode->neighbour;
		while (neighbour != NULL)
		{
			struct GraphNode* node = neighbour->node;
			printf("%s, ", node->autorName);

			neighbour = neighbour->link;
		}
		printf("\n");

		graphNode = graphNode->next;
	}
}

/* Aggiunge autori in grafo */
void fillGraphWithAutors(struct Graph** g, struct ArticlesList* articlesList)
{
    int i;
	struct Graph* graph = *g;

	for (i = 0; i < articlesList->maxArticleId + 1; i++)
	{
		if (articlesList->articles[i] != ((struct Article*)NULL))
		{
			struct Article* article = articlesList->articles[i];

			/* Aggiunge i nodi con dati nomi */
			addNodesByAutorsName(&graph, article);

			/* Aggiunge vicini */
			addNeighboursForAutor(&graph, article);
		}
	}

	*g = graph;
}

/* Aggiunge nodi con dato nome di autore */
void addNodesByAutorsName(struct Graph** g, struct Article* article)
{
    int j;
	struct Graph* graph = *g;

	for (j = 0; j < article->numberOfAutors; j++)
	{
		char* autorName = article->autors[j];
		struct GraphNode* graphNode = findNodeInGraphByName(graph, autorName);

		if (graphNode == NULL)
		{
			graphNode = createGraphNode(autorName);
			addNodeToGraph(&graph, graphNode);
		}
	}

	*g = graph;
}

/* Aggiunge vicino per autore */
void addNeighboursForAutor(struct Graph** g, struct Article* article)
{
    int j, k;
    char* name;
    struct GraphNode* node;
    struct GraphNeighbour* neighbourNode;

    struct Graph* graph = *g;

	/* Due cicli for attraverso tutti autori di questo articolo */
	for (j = 0; j < article->numberOfAutors; j++)
	{
		char* autorName = article->autors[j];
		struct GraphNode* graphNode = findNodeInGraphByName(graph, autorName);

		for (k = 0; k < article->numberOfAutors; k++)
		{
			/* Quando sono uguali */
			if (j == k)
			{
				continue;
			}

			name = article->autors[k];
			node = findNodeInGraphByName(graph, name);

			/* Chiedo se il nodo si trova gia' nella lista degli vicini */
			neighbourNode = findNeighbourForNode(graphNode, node);
			
			/* Se non si trova, lo aggiungo */
			if (neighbourNode == NULL)
			{
				neighbourNode = createGraphNeighbour(node);
				addNeighbourToNode(&graphNode, neighbourNode);
			}
		}
	}

	*g = graph;
}
