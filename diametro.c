/* diametro.c */

/* Direttive */
#include "diametro.h"

int calculateDiametroForGraph(struct Graph* graph)
{
    int diametroMax;
    struct GraphNode* node;
	int** matrix = calloc(graph->numberOfNodes * graph->numberOfNodes, sizeof(int**));
	char** helpersArray = calloc(graph->numberOfNodes, sizeof(char*));

	/* Inizializazzione di matrice */
	/* Tutti gli elementi sono all'inizio uguali ad n - numero di nodi */
	/* All'inizio tutti gli nodi non sono vicini, grafo non e' conesso */
	matrixInitialization(&matrix, graph->numberOfNodes);

	helpersArrayInitialization(&helpersArray, graph);

	/* Cambia la matrice */
	/* Se gli nodi sono vicini - elemento in matrice e' 1 */
	node = graph->start;
	while (node != NULL)
	{
		int m = getKeyForValue(helpersArray, graph->numberOfNodes, node->autorName);

		struct GraphNeighbour* neighbour = node->neighbour;
		while (neighbour != NULL)
		{
			struct GraphNode* neighbourNode = neighbour->node;
			int n = getKeyForValue(helpersArray, graph->numberOfNodes, neighbourNode->autorName);

			matrix[m][n] = 1;

			neighbour = neighbour->link;
		}

		node = node->next;
	}

    /* Stampa matrice con numeri 1 e n - nodi vicini o no */
	/* Dal testo di progetto questo non deve essere stampato */
	/* quindi puo' essere commentato */
	/* mi serve solo per controllo */
	/* printMatrix(matrix, graph->numberOfNodes); */

	/* Algoritmo di Floyd-Warshall */
	floydAlgorithm(&matrix, graph->numberOfNodes);

	/* Stampa matrice con i numeri che rappresentano distanze tra due nodi */
	/* Dal testo di progetto questo non deve essere stampato */
	/* quindi puo' essere commentato */
	/* mi serve solo per controllo */
	/* printMatrix(matrix, graph->numberOfNodes); */

	/* Diametro - numero massimo che si trova in matrice */
	diametroMax = getMaximumFromMatrix(matrix, graph->numberOfNodes);

	return diametroMax;
}

/*  Inizializazzione di matrice */
void matrixInitialization(int*** m, int n)
{
    int i, j;
	int** matrix = *m;

	for (i = 0; i < n; i++)
	{
		matrix[i] = calloc(n, sizeof(int*));
		for (j = 0; j < n; j++)
		{
			matrix[i][j] = n;
		}
	}

	*m = matrix;
}

/* Help array con i nomi dei nodi */
void helpersArrayInitialization(char*** ha, struct Graph* graph)
{
	char** helpersArray = *ha;

	int i = 0;
	struct GraphNode* node = graph->start;
	while (node != NULL)
	{
		helpersArray[i] = node->autorName;
		i++;
		node = node->next;
	}

	*ha = helpersArray;
}

int getKeyForValue(char** arr, int n, char* value)
{
    int i;

	for (i = 0; i < n; i++)
	{
		if (strcmp(arr[i], value) == 0)
		{
			return i;
		}
	}
  return -1;
}

/* Stampa la matrice */
void printMatrix(int** matrix, int numberOfNodes)
{
    int i, j;

	printf("\n");
	for (i = 0; i < numberOfNodes; i++)
	{
		for (j = 0; j < numberOfNodes; j++)
		{
			printf("%3d ", matrix[i][j]);
		}
		printf("\n");
	}
}

/* Algoritmo di Floyd-Warshall - implementazione */
void floydAlgorithm(int*** m, int n)
{
    int i, j, k;
	int **matrix = *m;

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			for (k = 0; k < n; k++)
			{
				if (matrix[j][k] >(matrix[j][i] + matrix[i][k]))
				{
					matrix[j][k] = matrix[j][i] + matrix[i][k];
				}
			}
		}
	}

	*m = matrix;
}

/* Massimo tra tutti gli elementi di matrice */
int getMaximumFromMatrix(int** m, int n)
{
    int i, j;

	int maximum = 0;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			maximum = max_speciale(maximum, m[i][j]);
		}
	}

	return maximum;
}

/* Calcola massimo tra due numeri interi */
int max_speciale(int a, int b)
{
	int m;
	if (a>=b)
		m=a;
	else if(a<b)
		m=b;
		
    return m;
}
