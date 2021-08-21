#ifndef __quicksort_h
#define __quicksort_h

#include "autor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bool.h"

void swapAutors(struct Autor** a, struct Autor** b);

int partitionAutors(struct AutorsList* array, int low, int high);

void quickSortAutors(struct AutorsList* array, int low, int high);

void swapChars(char** a, char** b);

#endif
