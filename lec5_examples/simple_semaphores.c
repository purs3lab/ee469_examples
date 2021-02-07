#include <stdio.h> 
#include <pthread.h> 
#include <semaphore.h> 
#include <unistd.h> 
  
#define MAX_THREADS 5
// Declaration of the semaphore.
sem_t max_workers_s; 

// function representing a worker. 
void* worker(void* arg); 

// We want to ensure that only certain number (n) of workers 
// are doing work at a given time.  
int main(int argc, char **argv) 
{ 
    unsigned n, i;
    pthread_t parr[MAX_THREADS];
    printf("Enter number of simulataneours workers (< 3):\n");
    scanf("%u", &n);
    
    // We initialize the semaphone with n.
    // Thus limiting the number of workers.
    sem_init(&max_workers_s, 0, n);
    
    // We create MAX_THREADS number of workers
    // however, only n will be doing work..rest all
    // will be waiting on the semaphore max_workers_s.
    printf("Creating %u workers\n", n);
    for (i=0; i < MAX_THREADS; i++) {
       pthread_create(&(parr[i]),NULL,worker,(void*)i); 
    }
    
    // Waiting for the threads to finish.
    for (i=0; i < MAX_THREADS; i++) {
       pthread_join(parr[i],NULL); 
    }
    sem_destroy(&max_workers_s); 
    return 0; 
} 

// Every thread wants to do some work and starts
// by waiting on s
void* worker(void* arg) 
{ 
    int worknum = (int)arg;
    while (1) {
	    // wait 
	    printf("Worker %d waiting.\n", worknum);
	    sem_wait(&max_workers_s); 
	    printf("Worker %d entered.\n", worknum);
	  
	    // Mimicking work!
	    sleep(1);  
	    
	    printf("Worker %d signalling.\n", worknum);
	    //signal
	    sem_post(&max_workers_s); 
    }
    return NULL;
} 
