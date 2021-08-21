/* article.c */

/* Direttive */
#include "article.h"
#include "autor.h"

/* Quando legge una riga di file, crea un nuovo articolo con tutte le informazioni */
struct Article* createNewArticle(int id, char* name, char** autors, char** quotes, int numberOfAutors, int numberOfQuotes)
{
	struct Article* article = calloc(100, sizeof(struct Article*));
	article->id = id;
	article->name = name;
	article->autors = autors; /* array of autors */
	article->quotes = quotes; /* array of articles that this autor is quoting (their id) */
	article->numberOfAutors = numberOfAutors;
	article->numberOfQuotes = numberOfQuotes;
	article->quotedNumber = 0; /* number of articles where this article is quoted */

	return article;
}

/* Stampa un articolo */
void printArticle(struct Article* article)
{
    int i;

	printf("ID: %d, NAME: %s, AUTORS LENGTH: %d, QUOTES LENGTH: %d, QUOTED NUMBER: %d, ", article->id, article->name, article->numberOfAutors, article->numberOfQuotes, article->quotedNumber);
	printf("AUTORS:");
	for (i = 0; i < article->numberOfAutors; i++)
	{
		printf("%s ", article->autors[i]);
	}
	printf(", QUOTES:");
	for (i = 0; i < article->numberOfQuotes; i++)
	{
		printf("%s ", article->quotes[i]);
	}
	printf("\n\n");
}

/* Crea lista degli articoli - lookup table */
struct ArticlesList* createArticleList()
{
	int i;
	struct ArticlesList* list = malloc(sizeof(struct ArticlesList*));

	list->articles = calloc(100, sizeof(struct Article*));
	/* tutti gli list->articles inizialmente NULL */
	
	for (i = 0; i < 100; i++)
	{
		list->articles[i] = (struct Article*)NULL;
	}

	list->maxArticleId = 0;

	return list;
}

/* Stampa tutti gli articoli */
void printArticles(struct ArticlesList* articlesList)
{
    int i;
	for (i = 0; i < articlesList->maxArticleId + 1; i++)
	{
		if (articlesList->articles[i] != (struct Article*)NULL) {
			printArticle(articlesList->articles[i]);
		}
	}
}
