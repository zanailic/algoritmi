/* project.c */

/* Direttive */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "readfile.h"
#include "article.h"
#include "autor.h"
#include "quicksort.h"
#include "graph.h"
#include "diametro.h"
#include "queue.h"
#include "clique.h"

/* Programma principale */
int main (int argc, char *argv[])
{
	/* Parte dichiarativa */
	FILE *file;
	struct ArticlesList* articlesList;
	struct AutorsList* autorsList;
	struct Article* article;
	struct Queue* queue;
	struct Graph* graph;
	struct GraphNode* node;
	int diametro;
	int number;
	int numb;
	int i;

	/* Parte esecutiva */

	/* Legge file dal linea di commando */
	char* fileName=argv[1];
	if (argc != 2)
	{
 		fprintf(stderr,"Errore nella linea di comando!\n");
 		exit(EXIT_FAILURE);
 	}

	/* Apri file */
	file = fopen(fileName, "rt");
	if (file == NULL)
	{
		printf("Errore nell'apertura del file %s!\n", fileName);
		exit(EXIT_FAILURE);
	}

	/* Crea nuova lista degli articoli */
	articlesList = createArticleList();

	/* Legge da file e aggiunge un articolo nella lista degli articoli */
	article = readOneArticle(file);
	while (article != (struct Article*)NULL)
	{
		/* Aggiunge articolo letto nella lista */
		articlesList->articles[article->id] = article;
		
		if (articlesList->maxArticleId < article->id)
		{
			articlesList->maxArticleId = article->id;
		}
		article = readOneArticle(file);
	}
	/* Ora tutti gli articoli sono letti e aggiunti nella lista */

	fclose(file);

	/* Crea nuova lista degli autori */
	autorsList = createNewAutorsList();

	/* Va attraverso tutti articoli per creare gli autori */
	for (i = 0; i < articlesList->maxArticleId + 1; i++)
	{
		if (articlesList->articles[i] != ((struct Article*)NULL))
		{
			modifyArticlesQuotedNumber(articlesList->articles[i], &articlesList);
			modifyAllArticlesAutors(articlesList->articles[i], &autorsList, &articlesList);
			modifyAllArticlesQuotedAutors(articlesList->articles[i], &autorsList, articlesList);
		}
	}
	/* Ora abbiamo lista degli articoli e lista degli autori */
	
	/* Stampa degli articoli */
	/* Dal testo di progetto questo non deve essere stampato */
	/* quindi puo' essere commentato */
	/* mi serve solo per controllo */
	/* printArticles(articlesList); */

	/* QuickSort per autori */
	numb = autorsList->numberOfAutors - 1;
	quickSortAutors(autorsList, 0, numb);

	/* Calcola indice di Hirsch */
	calculateHindexForAutors(autorsList);

	/* Stampa autori */
	printAutors(autorsList);

	/* Crea grafo */
	graph = createGraph();

	/* Mettiamo gli autori in grafo */
	fillGraphWithAutors(&graph, articlesList);

	/* Stampa del grafo */
	/* Dal testo di progetto questo non deve essere stampato */
	/* quindi puo' essere commentato */
	/* mi serve solo per controllo */
	/* printNodes(graph); */

	/* Calcolo diametro */
	diametro = calculateDiametroForGraph(graph);
	printf("\nDiametro %d\n", diametro);

	/* Clique */
	/* Si crea la coda */
	queue = createQueue(graph->numberOfNodes * graph->numberOfNodes);
	node = graph->start;

	/* Aggiunge in coda tutte le coppie di autori che collaborano fra loro */
	fillQueueWithPairOfAutors(&queue, node);

	/* Aggiunge nuovi nodi alle coppie di autori */
	addNewAutorsConnectionToQueue(&queue, node);

	/* Determina e stampa clique number */
	number = getCliqueMaximumNumber(queue);
	printf("\nClique number %d\n", number);

	/* Stampa numero di clique massimali */
	printf("\nClique massimali %d\n", queue->size);

	/* Stampa tutte le clique massimali e numero di clique sottoinsiemi */
	calculateSubsetNumberAndPrintQueue(queue);

	return EXIT_SUCCESS;
}
