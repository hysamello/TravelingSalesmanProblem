#pragma once


#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

int calculateDist(int size, int path[size], Matrix matrix);
void swap(int size, int path[size]);
int AJPseudoEvolutive(int size, Matrix matrix, int num_workers, int pathSolution[size]);
void pathPrint(int size, int path[size]);
void createRandomPath(int size, int path[size]);
bool checkExistingCity(int size,int path[size], int city);
int chooseRandomCity(int size);
void copyArray(int size, int arr1[size], int arr2[size]);