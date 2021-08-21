/* autor.c */

/* Direttive */
#include "autor.h"

/* Crea nuova lista degli autori */
struct AutorsList* createNewAutorsList()
{
	int i;
	struct AutorsList* list = calloc(100, sizeof(struct AutorsList*));

	list->autors = calloc(100, sizeof(struct Autor*));

	for (i = 0; i < 100; i++)
	{
		list->autors[i] = (struct Autor*)NULL;
	}

	list->autorsHelperArray = calloc(100, sizeof(char*));

	return list;
}

/* Trova autore in helperArray per un nome dato */
struct Autor* getAutorByName(struct AutorsList* autorsList, char* autorName)
{
    int i;

	for (i = 0; i < autorsList->numberOfAutors; i++)
	{
		if (strcmp(autorName, autorsList->autorsHelperArray[i]) == 0)
		{
			return autorsList->autors[i];
		}
	}

	return (struct Autor*)NULL;
}

/* Trova indice di autore in helperArray */
int getKeyOfAutorArray(struct AutorsList* autorsList, char* autorName)
{
    int i;
	
    for (i = 0; i < autorsList->numberOfAutors; i++)
	{
		if (strcmp(autorName, autorsList->autorsHelperArray[i]) == 0)
		{
			return i;
		}
	}
	
    return 0;
}

/* Crea autore solo per un nome dato, agiunggendo il articolo corrispondente */
struct Autor* createNewAutor(struct Article* article, char* name)
{
	struct Autor* autor = calloc(10, sizeof(struct Autor*));

	autor->name = name;
	autor->numberOfArticles = 0;
	autor->articles = calloc(100, sizeof(struct Article*));
	insertSortedAutor(&autor, article);

	autor->quotedArticles = calloc(100, sizeof(struct Article*));
	autor->numberOfQuotes = 0;
	autor->hindex = 0;

	return autor;
}

/* Funzione che aggiunge un articolo in vettore di articolo in autore */
/* Lo aggiunge in ordine (e' importante per indice di Hirsch) */
void insertSortedAutor(struct Autor** a, struct Article* article)
{
	struct Autor* autor = *a;
	int numberOfArticles = autor->numberOfArticles;

	int i;
	for (i = numberOfArticles - 1; i >= 0 && checkQuotednumber(autor->articles[i], article); i--)
    {
		autor->articles[i + 1] = autor->articles[i];
    }
	
    autor->articles[i + 1] = article; 
    autor->numberOfArticles++;

    *a = autor;
} 

/* Condizione che utilizziamo per l'ordinamento */
bool checkQuotednumber(struct Article* a, struct Article* b)
{
	if (a->quotedNumber <= b->quotedNumber)
	{
		return true;
	}

	return false;
}

struct Autor* updateAutorArticles(struct Autor* autor, struct Article* article)
{
	insertSortedAutor(&autor, article);

	return autor;
}

/* Aggiungiamo autori dal articoli */
struct AutorsList* addAutors(struct AutorsList* autorsList, struct Article* article)
{
    int i, j;

	/* Va attraverso tutti gli autori per articolo corrente */
	for (i = 0; i < article->numberOfAutors; i++) 
	{
		/* Prova a trovarlo in lista degli autori */
		struct Autor* autor = getAutorByName(autorsList, article->autors[i]);

		if (autor == ((struct Autor*)NULL)) {
			/* Caso quando autore non si trova nella lista */
			autor = createNewAutor(article, article->autors[i]);
			autorsList->autorsHelperArray[autorsList->numberOfAutors] = article->autors[i];
			autorsList->autors[autorsList->numberOfAutors] = autor;
			autorsList->numberOfAutors++;
		}
		else {
			/* Caso quando autore si gia' trova nella lista */
			autor = updateAutorArticles(autor, article);
			j = getKeyOfAutorArray(autorsList, article->autors[i]);
			autorsList->autors[j] = autor;
		}
	}

	return autorsList;
}

/* Stampa tutti autori */
void printAutors(struct AutorsList* autorsList)
{
    int i;

	for (i = 0; i < autorsList->numberOfAutors; i++)
	{
		struct Autor* autor = autorsList->autors[i];
		if (autor != (struct Autor*)NULL) 
		{
			printAutor(autor);
		}
	}
	
}

/* Stampa uno autore */
void printAutor(struct Autor* autor)
{
	printf("%s %d %d %d\n", autor->name, autor->numberOfArticles, autor->numberOfQuotes, autor->hindex);
}

/* In questa funzione troviamo indice, non sortiamo perche' abbiamo usato insertSorted per articoli in autori */
void calculateHindexForAutor(struct Autor** a)
{
	int i;
	struct Autor* autor = *a;

	int hindex = 1;
	
	for (i = 0; i < autor->numberOfArticles; i++)
	{
		struct Article* article = autor->articles[i];

		if ((i + 1) > article->quotedNumber)
		{
			hindex = i;
			break;
		}
	}

	autor->hindex = hindex;

	*a = autor;
}

void calculateHindexForAutors(struct AutorsList* autorsList)
{
    int i;

	for (i = 0; i < autorsList->numberOfAutors; i++)
	{
		if (autorsList->autors[i] != ((struct Autor*)NULL))
		{
			struct Autor* autor = autorsList->autors[i];
			calculateHindexForAutor(&autor);
		}
	}
}

/* Aggiunge e modifica autori, di un array di articoli */
void modifyAllArticlesAutors(struct Article* article, struct AutorsList** autorsList, struct ArticlesList** articlesList)
{
	struct ArticlesList* list = *articlesList;

	*autorsList = addAutors(*autorsList, article);

	list->articles[article->id] = article;
	if (list->maxArticleId < article->id)
	{
		list->maxArticleId = article->id;
	}

	*articlesList = list;
}

void modifyAllArticlesQuotedAutors(struct Article* article, struct AutorsList** autList, struct ArticlesList* articlesList)
{
	int i, j;
	struct AutorsList* autorsList = *autList;

	for (i = 0; i < article->numberOfQuotes; i++)
	{
		char* charId = article->quotes[i];
		char* end;
		int id = strtol(charId, &end, 10);

		struct Article* quotedArticle = articlesList->articles[id];
		for (j = 0; j < quotedArticle->numberOfAutors; j++)
		{
			char* autorName = quotedArticle->autors[j];
			int key = getKeyOfAutorArray(autorsList, autorName);
			struct Autor* autor = autorsList->autors[key];
			autor->quotedArticles[autor->numberOfQuotes] = article;
			autor->numberOfQuotes++;
			autorsList->autors[key] = autor;
		}
	}

	*autList = autorsList;
}

/* Modifica articoli, aggiungendo numero di articoli dove e' stato citato */
void modifyArticlesQuotedNumber(struct Article* article, struct ArticlesList** al)
{
	int i;
	struct ArticlesList* articlesList = *al;

	for (i = 0; i < article->numberOfQuotes; i++)
	{
		char* articleId = article->quotes[i];

		char* end;
		int id = strtol(articleId, &end, 10);

		struct Article* quotedArticle = articlesList->articles[id];
		quotedArticle->quotedNumber++;
		articlesList->articles[id] = quotedArticle;
	}

	*al = articlesList;
}
