#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>


int calculateDist(int size, int path[size], int matrix[size][size]);
void swap(int size, int path[size]);
int AJPseudoEvolutive(int size, int matrix[size][size], int pathSolution[size]);
void pathPrint(int size, int path[size]);
void createRandomPath(int size, int path[size]);
bool checkExistingCity(int size,int path[size], int city);
int chooseRandomCity(int size);
void copyArray(int size, int arr1[size], int arr2[size]);


int main(){

    srand(time(NULL));

    const int size = 5;

    int matrix[5][5] = {
        {0, 23, 10, 4, 1},
        {23, 0, 9, 5, 4},
        {10, 9, 0, 8, 2},
        {4, 5, 8, 0, 11},
        {1, 4, 2, 11, 0},
    };

    int pathSolution[size];
    int dist = AJPseudoEvolutive(size, matrix, pathSolution);

    pathPrint(size, pathSolution);
    printf("Distance: %d\n", dist);

    return EXIT_SUCCESS;
}

int AJPseudoEvolutive(int size, int matrix[size][size], int pathSolution[size]){

    const int maxInterations = 1000;
    const long maxTime = 100;

    struct timeval startTime;
    struct timeval elapsedTime;

    int path[size];
    createRandomPath(size,path);

    int distSolution = __INT_MAX__;
    int distAux = 0;  

    gettimeofday(&startTime, NULL);

    int i = 0;
    while (((elapsedTime.tv_sec - startTime.tv_sec) * 1000000 + (elapsedTime.tv_usec - startTime.tv_usec) < maxTime) && (i < maxInterations)) {
        
        distAux = calculateDist(size, path, matrix);

        if(distAux<distSolution){
            distSolution = distAux;
            copyArray(size, pathSolution, path);            
        }
 
        swap(size, path);

        gettimeofday(&elapsedTime, NULL);
        i++;
    }

    return distSolution;
}

int calculateDist(int size, int path[size], int matrix[size][size]){

    int dist = 0;

    for(int i=0; i<size-1; i++){
        int current = path[i]-1;
        int next = path[i+1]-1;

        dist += matrix[current][next];
    }

    int last = path[size-1]-1;
    int first = path[0]-1;

    dist += matrix[last][first];

    return dist;
}

void swap(int size, int path[size]){

    int a = rand() % size;
    int b = rand() % size;
    
    int aux = path[a];

    path[a] = path[b];
    path[b] = aux;
}

void copyArray(int size, int arr1[size], int arr2[size]){

    for(int i=0; i<size; i++){
        arr1[i] = arr2[i];
    }
}

void pathPrint(int size, int path[size]){

    printf("Path: { ");
    for(int i=0;i<size;i++){
        printf("%d ",path[i]);
    }
    printf("}\n");
}

void createRandomPath(int size, int path[size]){

    int city = 0;

    for(int i=0; i<size; i++){

        while(checkExistingCity(size, path, city)){
            city = chooseRandomCity(size);
        }

        path[i] = city;
    }
}

bool checkExistingCity(int size, int path[size], int city){

    for(int i=0;i<size;i++){
        if(path[i] == city){
            return true;
        }
    }
    return false;
}

int chooseRandomCity(int size){

    int city = rand() % size;

    return city + 1;
}