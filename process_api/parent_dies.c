#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<sys/wait.h>

#define CHILD_EXIT_CODE 1

void main() {
  int i, ret_status, ret_of_fork;
  pid_t pi;
  //printf("%s:%d, Process started (%d)\n", __FILE__, __LINE__, getpid());
  ret_of_fork= fork(); /* fork another process */
  if (ret_of_fork < 0) {
     // error occurred.
     exit(-1);
  }

  if (ret_of_fork == 0) { /* child process */

    ret_of_fork= fork(); /* fork another process */
    if (ret_of_fork < 0) {
        // error occurred.
        exit(-1);
    }

    if (ret_of_fork == 0) { /* child process */
        printf("%s:%d, New process started (%d), Parent id: %d\n", __FILE__, __LINE__, getpid(), getppid());
        printf("%s:%d, Process (%d) sleeping for 10 seconds.\n", __FILE__, __LINE__, getpid());
        for (i=0; i < 10; i++) {
            sleep(1);
        }
        printf("%s:%d, New process exiting (%d), Parent id: %d\n", __FILE__, __LINE__, getpid(), getppid());
        exit(CHILD_EXIT_CODE);
        
    } else { /* pid > 0; parent process */
        printf("%s:%d, Parent process (%d) will sleep for 5 seconds and exit.\n", __FILE__, __LINE__, getpid());
        for (i=0; i < 5; i++) {
            sleep(1);
        }
        printf("%s:%d, Parent process (%d) exiting.\n", __FILE__, __LINE__, getpid());
    }
    exit(0);
  }
  printf("Enter a number to exit.\n");
  scanf("%d", &i);
}

