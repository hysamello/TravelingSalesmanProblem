#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/time.h>
#include <time.h>
#include "matrix.h"


int calculateDist(int size, int path[size], Matrix matrix);
void swap(int size, int path[size]);
int AJPseudoEvolutive(int size, Matrix matrix, int num_workers, int pathSolution[size]);
void pathPrint(int size, int path[size]);
void createRandomPath(int size, int path[size]);
bool checkExistingCity(int size,int path[size], int city);
int chooseRandomCity(int size);
void copyArray(int size, int arr1[size], int arr2[size]);

int main(){

    srand(time(NULL));

    char filename[50];
    int num_workers;

    printf("\nNome do ficheiro: ");
    scanf("%s", filename);

    printf("\nNumero de processos: ");
    scanf("%i", &num_workers);

    //char* filename = "p01.txt";
    int size = getSize(filename);
    Matrix matrix = createMatrix(size);
    loadMatrix(filename,&matrix);
    matrixPrint(matrix);

    //int num_workers = 5;
    int pathSolution[size];
    int dist = AJPseudoEvolutive(size, matrix, num_workers, pathSolution);

    printf("\n");
    pathPrint(size, pathSolution);
   
    printf("Distance: %d\n", dist); 

    return EXIT_SUCCESS;
}

int AJPseudoEvolutive(int size, Matrix matrix, int num_workers, int pathSolution[size]){

    const int maxInterations = 100;

    // Create shared memory map
    int protection = PROT_READ | PROT_WRITE;
    int visibility = MAP_ANONYMOUS | MAP_SHARED;
    int *distShmem = mmap(NULL, sizeof(int), protection, visibility, 0, 0);
    int *pathShmem = mmap(NULL, size * sizeof(int), protection, visibility, 0, 0);

    // Create algorithm variables

    int path[size];
    createRandomPath(size,path);

    *distShmem = __INT_MAX__;
    int distAux = 0;  
    
    // Create semaphores
    sem_unlink("job_ready");
    sem_unlink("job_done");
    sem_t *job_ready = sem_open("job_ready", O_CREAT, 0644, 0);
    sem_t *job_done = sem_open("job_done", O_CREAT, 0644, 0);
    
    // Workers
    int pids[num_workers];
    
    // Fork worker processes
    for (int i=0; i<num_workers; i++) {
        pids[i] = fork();
        if (pids[i] == 0) {
            //printf("Worker process #%d!\n", i);
            while (1) {
                sem_wait(job_ready);

                    //printf("Worker #%d:\n", i);

                    
                    distAux = calculateDist(size, path, matrix);

                    if(distAux < *distShmem){
                        *distShmem = distAux;
                        copyArray(size, pathShmem, path);            
                    }
            
                    swap(size, path);

                sem_post(job_done);
            }
            exit(0);
        }
    }
    
    // Parent process
    //printf("Parent process!\n");
    for (int i=0; i<maxInterations; i++) {
        sem_post(job_ready);
        sem_wait(job_done);
    }

    // Release semaphores
    sem_close(job_ready);
    sem_close(job_done);
    
    // Kill worker processes
    for (int i=0; i<num_workers; i++) {
        //printf("Killing %d\n", pids[i]);
        kill(pids[i], SIGKILL);
    }

    copyArray(size, pathSolution, pathShmem);

    return *distShmem;
}


int calculateDist(int size, int path[size], Matrix matrix){

    int dist = 0;

    for(int i=0; i<size-1; i++){
        int current = path[i]-1;
        int next = path[i+1]-1;

        //dist += matrix[current][next];
        dist += get(matrix,current,next);

    }

    int last = path[size-1]-1;
    int first = path[0]-1;

    //dist += matrix[last][first];
    dist += get(matrix,last,first);

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