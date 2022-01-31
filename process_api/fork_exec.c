#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<sys/wait.h>


void main() {
  int i, ret_of_fork, was;
  printf("%s:%d, Process started (%d)\n", __FILE__, __LINE__, getpid());
  ret_of_fork= fork(); /* fork another process */
  if (ret_of_fork < 0) {
     // error occurred.
     exit(-1);
  }

  if (ret_of_fork == 0) { /* child process */
	printf("%s:%d, New process started (%d)\n", __FILE__, __LINE__, getpid());
	was = 3;
	printf("%s:%d, Process (%d) changed variable to %d and sleeping for 5 seconds\n", __FILE__, __LINE__, getpid(), was);
	sleep(5); 
	
	printf("%s:%d, Process (%d) saw value of the variable as %d\n", __FILE__, __LINE__, getpid(), was);
	// Replace with ls
     	execlp("/usr/bin/ls", "ls", NULL);
        printf("%s:%d, Process (%d): You will not see this.\n", __FILE__, __LINE__, getpid());
    
 } else { /* pid > 0; parent process */
 	was = 5;
	printf("%s:%d, Process (%d) changed variable to %d\n", __FILE__, __LINE__, getpid(), was);
	printf("%s:%d, Process (%d) waiting for the child\n", __FILE__, __LINE__, getpid());
	ret_of_fork = wait(NULL);
	printf("%s:%d, Process (%d) saw value of the variable as %d - after child PID: %d exited.\n", __FILE__, __LINE__, getpid(), was, ret_of_fork);
  }
}

