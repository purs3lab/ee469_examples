#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<sys/wait.h>

void main() {
  int i, ret_status, ret_of_fork, j;
  pid_t first_process = 0;
  printf("%s:%d, Process started (%d)\n", __FILE__, __LINE__, getpid());
  i = 3;
  while (i) {
  	ret_of_fork= fork(); /* fork another process */
  	if (!ret_of_fork) {
  	  first_process = 0;
  	  printf("%s:%d, New Process started (%d)\n", __FILE__, __LINE__, getpid());
  	} else {
  	  if (!first_process)
  	  	first_process = ret_of_fork;
  	}
  	// If this is the last process in the tree. Wait for 15 seconds.
  	if (!ret_of_fork && i == 1) {
  	  printf("%s:%d, Process (%d) sleeping for 20 seconds\n", __FILE__, __LINE__, getpid());
  	  for(j=0; j < 20; j++)
  	  	sleep(1);
  	}
  	
  	i--;
  }
  if (first_process) {
      printf("%s:%d, Process (%d) waiting for %d\n", __FILE__, __LINE__, getpid(), first_process);
      waitpid(first_process, NULL, 0);
  } else {
     printf("%s:%d, Process (%d) exiting without waiting\n", __FILE__, __LINE__, getpid());
  }
}

