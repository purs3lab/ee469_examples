#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<sys/wait.h>

#define CHILD_EXIT_CODE 1

void main() {
  int i, ret_status, ret_of_fork;
  pid_t pi;
  printf("%s:%d, Process started (%d)\n", __FILE__, __LINE__, getpid());
  ret_of_fork= fork(); /* fork another process */
  if (ret_of_fork < 0) {
     // error occurred.
     exit(-1);
  }

  if (ret_of_fork == 0) { /* child process */
	printf("%s:%d, New process started (%d)\n", __FILE__, __LINE__, getpid());
 	printf("%s:%d, Process (%d) sleeping for 20 seconds.\n", __FILE__, __LINE__, getpid());
	for (i=0; i < 20; i++) {
  		sleep(1);
        }
        printf("%s:%d, New process exiting (%d)\n", __FILE__, __LINE__, getpid());
        exit(CHILD_EXIT_CODE);
    
 } else { /* pid > 0; parent process */
	printf("%s:%d, Parent process waiting (%d)\n", __FILE__, __LINE__, getpid());
	pi = wait(&ret_status);
	printf("%s:%d, Parent process (%d) saw pid %d exit with %d code\n", __FILE__, __LINE__, getpid(), pi, ret_status);
  }
}

