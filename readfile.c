/* readfile.c */

/* Direttive */
#include "readfile.h"
#include "article.h"
#include <string.h>

/* Legge un articolo di file - in ogni riga di file si trova un articolo */
struct Article* readOneArticle(FILE *file) 
{
 	struct Article* article;
	char *end;
	int id;
	int autorsLength;
	int quotesLength;

  	char singleChar;
	char *articleId = calloc(20, sizeof(char));
	char *articleName = calloc(20, sizeof(char));
	char **autors = calloc(10, sizeof(char*));
	char **quotes = calloc(10, sizeof(char*));

	singleChar = fgetc(file);

	if (singleChar == EOF)
	{
		return (struct Article*)NULL;
	}

	/* Legge id di articolo */
	articleId[0] = singleChar;
	articleId = strcat(articleId, readSingleItem(file));

	/* Prima id e' char, con strtol diventa int */
	id = strtol(articleId, &end, 10);

	/* Legge nome dell'articolo */
	articleName = readSingleItem(file);

	/* Legge gli autori */
	autorsLength = 0;
	autors = readMultipleItems(file, &autorsLength);

	/* Legge gli citazioni */
	quotesLength = 0;
	quotes = readMultipleItems(file, &quotesLength);

	/* Crea nuovo articolo */
	article = createNewArticle(id, articleName, autors, quotes, autorsLength, quotesLength);

	return article;
}

/* Legge id e titolo di articolo */
char* readSingleItem(FILE *file)
{
	char singleChar;
    int wordLength;

	char *word = calloc(20, sizeof(char));
	singleChar = fgetc(file);
    wordLength = 0;

	while (singleChar != '|') {
		if (singleChar == ' ' && wordLength == 0) {
			singleChar = fgetc(file);
			continue;
		}

		word[wordLength] = singleChar;
		wordLength++;
		singleChar = fgetc(file);
	}
	word[wordLength - 1] = '\0';

	return word;
}

/* Legge tutti gli autori e citati nel articolo */
char** readMultipleItems(FILE *file, int* length)
{
    int itemsLength;
    char *word;
	char singleChar;
	char **items = calloc(10, sizeof(char*));
	int wordLength = 0;

	singleChar = fgetc(file);
	wordLength = 0;
	itemsLength = 0;
	word = calloc(20, sizeof(char));
	while (singleChar != '|' && singleChar != '\n') 
	{
		if (singleChar == ' ' && wordLength == 0) 
		{
			singleChar = fgetc(file);
			continue;
		}

		if (singleChar == '&') 
		{
			word[wordLength - 1] = '\0';
			wordLength = 0;
			items[itemsLength] = word;
			itemsLength++;
			word = calloc(50, sizeof(char));
			singleChar = fgetc(file);

			continue;
		}

		word[wordLength] = singleChar;
		wordLength++;
		singleChar = fgetc(file);
	}

	if (word[0] != '\0')
	{
		int lastChar = wordLength;
		if (word[wordLength - 1] == ' ')
		{
			lastChar = wordLength - 1;
		}
		word[lastChar] = '\0';
		items[itemsLength] = word;
		itemsLength++;
	}

	*length = itemsLength;
	return items;
}
