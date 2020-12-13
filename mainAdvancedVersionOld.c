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

int calculateDist(int size, int path[size], int matrix[size][size]);
void swap(int size, int path[size]);
int AJPseudoEvolutive(int size, int matrix[size][size], int num_workers, int pathSolution[size]);
void pathPrint(int size, int path[size]);
void createRandomPath(int size, int path[size]);
bool checkExistingCity(int size,int path[size], int city);
int chooseRandomCity(int size);
void copyArray(int size, int arr1[size], int arr2[size]);

int main(){

    srand(time(NULL));

    int size = 5;
    int matrix[5][5] = {
        {0, 23, 10, 4, 1},
        {23, 0, 9, 5, 4},
        {10, 9, 0, 8, 2},
        {4, 5, 8, 0, 11},
        {1, 4, 2, 11, 0},
    };

    int num_workers = 5;
    int pathSolution[size];
    int dist = AJPseudoEvolutive(size, matrix, num_workers, pathSolution);

    pathPrint(size, pathSolution);
   
    printf("Distance: %d\n", dist);

    return EXIT_SUCCESS;
}





void AJPseudoEvolutiveBaseVersion(int size, int path[size],int matrix[size][size], int iterations){
    // Create shared memory map
    int memSize = sizeof(int);
    int pathMemSize = size * sizeof(int);
    int protection = PROT_READ | PROT_WRITE;
    int visibility = MAP_ANONYMOUS | MAP_SHARED;
    int *dist = mmap(NULL, memSize, protection, visibility, 0, 0);
    int *pathMem = mmap(NULL, pathMemSize, protection, visibility, 0, 0);

    *dist = __INT_MAX__;
    //*dist = calculateDist(size, path, matrix);
    printf("%d\n",*dist);
    
    // Create semaphores
    sem_unlink("job_ready");
    sem_unlink("job_done");
    sem_t *job_ready = sem_open("job_ready", O_CREAT, 0644, 0);
    sem_t *job_done = sem_open("job_done", O_CREAT, 0644, 0);
    
    // Workers
    int num_workers = 5;
    int pids[num_workers];

    createRandomPath(size,path);
    int pathAux[size];
    int distAux = 0;
    
    // Fork worker processes
    for (int i=0; i<num_workers; i++) {
        pids[i] = fork();
        if (pids[i] == 0) {
            printf("Worker process #%d!\n", i);
            while (1) {
                sem_wait(job_ready);

                printf("Worker #%d:\n", i);

                swap(size,path);
                distAux = calculateDist(size, path, matrix);
                if(distAux<*dist){
                    *dist = distAux;
                
                    copyArray(size,pathMem,path);            
                } 

                sem_post(job_done);
            }
            exit(0);
        }
    }
    
    // Parent process
    printf("Parent process!\n");

    

    /* char *msg[3] = {"Hello World", "Hi", "Waterfall"}; */
    for (int i=0; i<iterations; i++) {
        /* strcpy(dist, msg[i]); */
        sem_post(job_ready);
        sem_wait(job_done);
    }
    
    
    // Release semaphores
    sem_close(job_ready);
    sem_close(job_done);
    
    // Kill worker processes
    for (int i=0; i<num_workers; i++) {
        printf("Killing %d\n", pids[i]);
        kill(pids[i], SIGKILL);
    }    

    pathPrint(size,pathMem);
    printf("Distance: %d\n", *dist);
}

void signal_handler(int signal){
    //printf("Parent: Handling SIGUSR1 in process #%d with PID=%d\n", i, pid);

    /*for (int i=0; i<pidsMem.length; i++) {
        printf("Killing %d\n", pidsMem[i]);
        kill(pidsMem[i], SIGUSR2);
    } */

    //gHasBetterPath = true;
    
}

void signal_handler_2(int signal){
    //printf("Child: Handling SIGUSR2 in process #%d with PID=%d\n", i, getpid());
    /*
    for (size_t i = 0; i < count; i++)
    {
        
    }*/
    

    //exit(0);
}

void AJPseudoEvolutiveAdvancedVersion(int size, int path[size],int matrix[size][size], int iterations){
    // Create shared memory map
    int memSize = sizeof(int);
    int pathMemSize = size * sizeof(int);

    int protection = PROT_READ | PROT_WRITE;
    int visibility = MAP_ANONYMOUS | MAP_SHARED;

    int *dist = mmap(NULL, memSize, protection, visibility, 0, 0);
    int *pathMem = mmap(NULL, pathMemSize, protection, visibility, 0, 0);
    //int *pidsMem = mmap(NULL, pathMemSize, protection, visibility, 0, 0);

    signal(SIGUSR1, signal_handler);
    signal(SIGUSR2, signal_handler_2);

    *dist = __INT_MAX__;
    //*dist = calculateDist(size, path, matrix);
    printf("%d\n",*dist);
    
    // Create semaphores
    sem_unlink("job_ready");
    sem_unlink("job_done");
    sem_t *job_ready = sem_open("job_ready", O_CREAT, 0644, 0);
    sem_t *job_done = sem_open("job_done", O_CREAT, 0644, 0);
    
    // Workers
    int num_workers = 5;
    int pids[num_workers];

    createRandomPath(size,path);

    

    int distAux = 0;
    
    // Fork worker processes
    for (int i=0; i<num_workers; i++) {
        pids[i] = fork(); 
        if (pids[i] == 0) {
            printf("Worker process #%d!\n", i);
            int *internPath = path;
            bool checked = false;
            while (1) {
                sem_wait(job_ready);


/*

                if(!checkedPids[i]){
                    internPath = pathMem;
                    checkedPids[i] = true;
                }

                gHasBetetrPath = chec()
                
                
                if(gHasBetterPath && !changed){
                        internPath = pathMem;
                        changed = true;
                }*/

                for (int j = 0; j < num_workers; j++) {
                    
                }
                //gHasBetterPath = false;
                
                
                
                distAux = calculateDist(size, internPath, matrix);
                if(distAux<*dist){
                    *dist = distAux;
                    kill(getppid(),SIGUSR1);
                    copyArray(size,pathMem,internPath);
                }
                swap(size,internPath);  
                sem_post(job_done);
            }
            exit(0);
        }
    }
    
    // Parent process
    printf("Parent process!\n");

    

    /* char *msg[3] = {"Hello World", "Hi", "Waterfall"}; */
    for (int i=0; i<iterations; i++) {
        /* strcpy(dist, msg[i]); */
        sem_post(job_ready);
        sem_wait(job_done);
    }
    
    while(1) {

       /* if (gHasBetterPath)
        {

            for (int i = 0; i < 5; i++)
            {
                kill(pids[i], SIGUSR2);
            }
        }*/
    }
    
    
    



    // Release semaphores
    sem_close(job_ready);
    sem_close(job_done);
    
    // Kill worker processes
    for (int i=0; i<num_workers; i++) {
        printf("Killing %d\n", pids[i]);
        kill(pids[i], SIGKILL);
    }    

    pathPrint(size,pathMem);
    printf("Distance: %d\n", *dist);
}

void copyArray(int size, int arr1[size], int arr2[size]){
    for(int i=0;i<size;i++){
        arr1[i] = arr2[i];
    }
}

void pathPrint(int size, int path[size]){
    printf("Path: {");
    for(int i=0;i<size;i++){
        printf("%d ",path[i]);
    }
    printf("}\n");
}

void createRandomPath(int size, int path[size]){
    for(int i=0;i<size;i++){
        
        int city = chooseRandomCity(size);
        while(checkExistingCity(size,path,city)){
            city = chooseRandomCity(size);
        }
        path[i] = city;
    }
}

bool checkExistingCity(int size,int path[size], int city){
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