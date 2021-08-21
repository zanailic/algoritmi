#ifndef __read_file_h
#define __read_file_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "article.h"
#include "bool.h"

struct Article* readOneArticle(FILE *file);

char** readMultipleItems(FILE *file, int* length);

char* readSingleItem(FILE *file);

#endif
