#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<sys/wait.h>

int global = 1;

void main()
{ 
  int ret_of_fork;
  int local;
  int i = 0;
  
  
  ret_of_fork= fork(); /* fork another process */
  if (ret_of_fork < 0) {
     // error occurred.
     exit(-1);
  }

  if (ret_of_fork == 0) { /* child process */
        // Initialize random number generation
        srand(time(NULL));
        
  	global = rand();
  	printf("Child(%d) changing global to %d\n", getpid(), global);
  	local = rand();
  	printf("Child(%d) changing local to %d\n", getpid(), local);
  
	for (i=0; i < 10; i++) {
  		printf("Child(%d) global value is %d\n", getpid(), global);
  		printf("Child(%d) local value is %d\n", getpid(), local);
  		sleep(1);
        }
        exit(0);
    
 } else { /* pid > 0; parent process */
	sleep(2); 
        srand(time(NULL));
  	for (i=0; i < 10; i++) {
       	global = rand();
       	local = rand();
  		printf("Parent(%d) changing global to %d\n", getpid(), global);
  		printf("Parent(%d) changing local to %d\n", getpid(), local);
  		sleep(1);
  	}
	exit(0);
  }
}

