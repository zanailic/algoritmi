#ifndef __article_h
#define __article_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bool.h"

struct Article {
	int id;
	char* name;
	char** autors;
	char** quotes; 
	int numberOfAutors; 
	int numberOfQuotes;
	int quotedNumber;
};

struct ArticlesList {
	struct Article** articles; /* array of articles read from file */
	int maxArticleId; /* id of last article */
};

struct Article* createNewArticle(int id, char* name, char** autors, char** quotes, int numberOfAutors, int numberOfQuotes);

struct ArticlesList* createArticleList();

void printArticle(struct Article* article);

void printArticles(struct ArticlesList* articlesList);


#endif
