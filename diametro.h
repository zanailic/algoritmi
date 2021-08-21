#ifndef __diametro_h
#define __diametro_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
#include "bool.h"

void matrixInitialization(int*** m, int n);

void helpersArrayInitialization(char*** ha, struct Graph* graph);

int getKeyForValue(char** arr, int n, char* value);

void printMatrix(int** matrix, int numberOfNodes);

void floydAlgorithm(int*** m, int n);

int getMaximumFromMatrix(int** m, int n);

int max_speciale(int a, int b);

int calculateDiametroForGraph(struct Graph* graph);

#endif 
