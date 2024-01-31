#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<sys/wait.h>

int global_var = 10;

int main() {
  int i, ret_of_fork, local_var = 7;
  int *heap_var = (int*) malloc(sizeof(int));
  *heap_var = 9;

  printf("%s:%d, Process started (%d): local var=%d, global var=%d, heap var=%d\n", __FILE__, __LINE__, getpid(), local_var, global_var, *heap_var);
  ret_of_fork= fork(); /* fork another process */
  if (ret_of_fork < 0) {
     // error occurred.
     exit(-1);
  }

  

  if (ret_of_fork == 0) { /* child process */
	printf("%s:%d, Child process started (%d): local var=%d, global var=%d, heap var=%d\n", __FILE__, __LINE__, getpid(), local_var, global_var, *heap_var);
	sleep(5); 
	
	local_var = 13;
	*heap_var = 41;
	global_var = 52;
	printf("%s:%d, In child Process (%d): changed local var to %d, global var to %d, heap var to %d\n", __FILE__, __LINE__, getpid(), local_var, global_var, *heap_var);
	return 0;
    
 } else { /* pid > 0; parent process */
 	printf("%s:%d, In Parent Process (%d): local var=%d, global var=%d, heap var=%d\n", __FILE__, __LINE__, getpid(), local_var, global_var, *heap_var);
	sleep(1);
	local_var = 4;
	*heap_var = 11;
	global_var = 12;
	printf("%s:%d, In Parent Process (%d): changed local var to %d, global var to %d, heap var to %d\n", __FILE__, __LINE__, getpid(), local_var, global_var, *heap_var);
	ret_of_fork = wait(NULL);
	printf("%s:%d, (After child exited) In Parent Process (%d): local var=%d, global var=%d, heap var=%d\n", __FILE__, __LINE__, getpid(), local_var, global_var, *heap_var);
  }
}

