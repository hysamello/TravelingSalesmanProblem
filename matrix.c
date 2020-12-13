#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "matrix.h"

/* #define M 4

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

//typedef matrix* Matrix;


char **split(char *string, int nFields, const char *delim);
void matrixPrint(Matrix m);
void loadMatrix(char *filename, Matrix *m);
MatrixValue createValue(int line,int column,int value);
Matrix createMatrix(unsigned maxLines);
int get(Matrix m, int linha, int coluna);
//void loadMatrix2d(char *filename,int size, int matrix[size][size]); */

/* int main(){
    Matrix matrix = createMatrix(4);

    loadMatrix("ex4.txt",&matrix);

    int val = get(matrix,3,2);
    //printf("Valor: %d\n",val);

    matrixPrint(matrix);

} */

Matrix createMatrix(unsigned maxLines){
    Matrix matrix;
    matrix.capacity = maxLines*maxLines;
    matrix.size = 0;
    matrix.maxLines = maxLines;
    matrix.values = malloc(matrix.capacity*sizeof(MatrixValue));
    
    return matrix;
    //return matrix;
}

void insertValue(Matrix *m,int line, int column, int v){
    int place = 0;

    MatrixValue mv;
    mv.line = line;
    mv.column = column;
    mv.val = v;

    /* for(int i=0;i<m->maxLines;i++){
        if(m->values[i].line == line && m->values[i].column == column){
            place = i;
        }
    } */

    m->values[m->size] = mv;
    m->size++;
}

/* MatrixValue createValue(int line,int column,int value){
    MatrixValue val;
    val.column = column;
    val.line = line;
    val.value = value;
    return val;
} */



char **split(char *string, int nFields, const char *delim)
{
    char **tokens = malloc(sizeof(char*) * nFields);
	int index = 0;
	char *next_token = NULL;

	char *token = strtok_r(string, delim, &next_token);
	while (token) {
		tokens[index++] = token;
		token = strtok_r(NULL, delim, &next_token);
	}
	return tokens;
}

void loadMatrix(char *filename, Matrix *m){
    FILE *f = NULL;

    f = fopen(filename,"r");

    if(f==NULL){
        printf("File not found");
    }

    char nextline[512];

    int countLines = 0;
    bool firstline = true;
    int lines = 0;
    int val;

    while(fgets(nextline,sizeof(nextline),f)){
        if(strlen(nextline)<1){
            continue;
        }

        if(firstline){
            char **tokens = split(nextline, nextline[1], " ");
            lines = atoi(tokens[0]);
            //Matrix m;
            m->maxLines = lines;
            //countLines++;
            firstline = false;
            continue;
        }
        
        char **tokens = split(nextline, lines, " ");
        //printf("\nLine:%d\n",countLines);
        for(int i=0;i<lines;i++){
            val = atoi(tokens[i]);
            insertValue(m,countLines,i,val);
            //printf(" %d ",val); 
        }
        countLines++;

        free(tokens);
    }

    fclose(f);

} 

void matrixPrint(Matrix m){
    printf("\n size: %d",m.size);

    int v = 0;

    for(int i=0;i<m.maxLines;i++){

        printf("\n{");
        for(int j=0;j<m.maxLines;j++){
            v = get(m,i,j);
            printf("%d ",v);
        }
        printf("}\n");
    }
}

int get(Matrix m, int linha, int coluna) {
	for (int i = 0; i < m.capacity; i++) {

		if (m.values[i].line == linha) {
			if (m.values[i].column == coluna) {
                return m.values[i].val;
			}
		}
	}
    return -1;
}