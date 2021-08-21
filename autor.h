#ifndef __autor_h
#define __autor_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bool.h"
#include "article.h"

struct Autor {
	char* name;
	int numberOfArticles;
	int numberOfQuotes; /* number of articles where autor is quoted */
	struct Article** articles;
	struct Article** quotedArticles; /* articles where autor is quoted */
	int hindex;
};

struct AutorsList {
	struct Autor** autors; /* array of autors */
	char** autorsHelperArray; /* just for names of autors */
	int numberOfAutors;
};
/*
esempio
i - numero di autori all'inizio 0
autorsHelperArray[0] = 'A1' ; i++;
autorsHelperArray[1] = 'A2' ; i++;
...
...
autorsHelperArray[6] = 'A5' 

struct Autor*
AutorsList[0]	= struct Autor* 1
AutorsList[1]	= struct Autor* 2
...
...
AutorsList[6]	= struct Autor* 5
*/

struct AutorsList* createNewAutorsList();

struct Autor* getAutorByName(struct AutorsList* autorsList, char* autorName);

int getKeyOfAutorArray(struct AutorsList* autorsList, char* autorName);

struct Autor* createNewAutor(struct Article* article, char* name);

struct Autor* updateAutorArticles(struct Autor* autor, struct Article* article);

struct AutorsList* addAutors(struct AutorsList* autorsList, struct Article* article);

void printAutors(struct AutorsList* autorsList);

void insertSortedAutor(struct Autor** a, struct Article* article);

void calculateHindexForAutor(struct Autor** a);

void calculateHindexForAutors(struct AutorsList* autorsList);

bool checkQuotednumber(struct Article* a, struct Article* b);

void printAutor(struct Autor* autor);

void modifyAllArticlesAutors(struct Article* article, struct AutorsList** autorsList, struct ArticlesList** articlesList);

void modifyAllArticlesQuotedAutors(struct Article* article, struct AutorsList** autList, struct ArticlesList* articlesList);

void modifyArticlesQuotedNumber(struct Article* article, struct ArticlesList** al);

#endif
