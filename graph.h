#ifndef __graph_h
#define __graph_h

#include "article.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bool.h"

/* Nodo di grafo */
struct GraphNode {
	char* autorName;
	struct GraphNode* next; /* puntatore al prossimo nella lista degli nodi - non devono (ma possono) essere collegati */
	struct GraphNeighbour* neighbour; /* nodo con cui e' collegato */
};

struct GraphNeighbour {
	struct GraphNode* node; /* puntatore al suo nodo, che si trova in grafo */ 
	struct GraphNeighbour* link; /* puntatore al prossimo vicino di questo nodo per cui si guardano vicini */
};

struct Graph {
	struct GraphNode* start; /* il primo nodo */
	int numberOfNodes; /* numero di nodi */
};

struct Graph* createGraph();

struct GraphNode* createGraphNode(char* autorName);

struct GraphNeighbour* createGraphNeighbour(struct GraphNode* node);

void addNodeToGraph(struct Graph** g, struct GraphNode* node);

void addNeighbourToNode(struct GraphNode** gNode, struct GraphNeighbour* neighbour);

struct GraphNode* findNodeInGraphByName(struct Graph* graph, char* autorName);

struct GraphNode* findNodeInGraphByNode(struct Graph* graph, struct GraphNode* node);

struct GraphNeighbour* findNeighbourForNode(struct GraphNode* graphNode, struct GraphNode* targetNode);

void fillGraphWithAutors(struct Graph** g, struct ArticlesList* articlesList);

void addNeighboursForAutor(struct Graph** g, struct Article* article);

void addNodesByAutorsName(struct Graph** g, struct Article* article);

void printNodes(struct Graph* graph);

#endif
