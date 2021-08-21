/* quicksort.c */

/* Direttive */
#include "quicksort.h"

void swapAutors(struct Autor** a, struct Autor** b)
{
	struct Autor* t = *a;
	*a = *b;
	*b = t;
}

void swapChars(char** a, char** b)
{
	char* t = *a;
	*a = *b;
	*b = t;
}

int partitionAutors(struct AutorsList* array, int low, int high)
{
  	int j;
	struct Autor* pivot = array->autors[high];
	
	int i = (low - 1);
	for (j = low; j <= high - 1; j++)
	{
		bool changePlaces = false;
		struct Autor* autor = array->autors[j];

		if (autor->numberOfArticles > pivot->numberOfArticles) {
			changePlaces = true;
		}
		else if (autor->numberOfArticles == pivot->numberOfArticles) {
			if (autor->numberOfQuotes > pivot->numberOfQuotes) {
				changePlaces = true;
			}
			else if (autor->numberOfQuotes == pivot->numberOfQuotes) {
				if (strcmp(autor->name, pivot->name) < 0) {
					changePlaces = true;
				}
			}
		}

		if (changePlaces)
		{
			i++;
			swapAutors(&array->autors[i], &array->autors[j]);
			swapChars(&array->autorsHelperArray[i], &array->autorsHelperArray[j]);

		}
	}
	swapAutors(&array->autors[i + 1], &array->autors[high]);
	swapChars(&array->autorsHelperArray[i + 1], &array->autorsHelperArray[high]);

	return (i + 1);
}

void quickSortAutors(struct AutorsList* array, int low, int high)
{
	if (low < high)
	{
		int pi = partitionAutors(array, low, high);
		quickSortAutors(array, low, pi - 1);
		quickSortAutors(array, pi + 1, high);
	}
}
