#pragma once

#include <stdio.h>
#include <stdlib.h>


typedef struct matrixValue{
    int line;
    int column;
    int val;
}MatrixValue;

typedef struct matrix{    
    int size;
    int capacity;
    int maxLines;
    MatrixValue *values;
}Matrix;

char **split(char *string, int nFields, const char *delim);
void matrixPrint(Matrix m);
void loadMatrix(char *filename, Matrix *m);
/* MatrixValue createValue(int line,int column,int value); */
Matrix createMatrix(unsigned maxLines);
int get(Matrix m, int linha, int coluna);
//void loadMatrix2d(char *filename,int size, int matrix[size][size]);