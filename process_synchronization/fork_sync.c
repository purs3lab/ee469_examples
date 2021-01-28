#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<sys/wait.h>

void main()
{ 
  int ret_of_fork;        
  int was = 3;
  
  printf("Main PId: %d\n", getpid());
  
  ret_of_fork= fork(); /* fork another process */
  if (ret_of_fork < 0) {
     // error occurred.
     exit(-1);
  }

  if (ret_of_fork == 0) { /* child process */
    was=2;
    printf("Set the value of was to %d\n", was);
    // wait for 2 seconds to allow parent to set "was"
    printf("Child waiting for 2 seconds\n");
    sleep(2);
    if (was != 2) {
       printf("Another process changed values of was to %d\n", was);
    } else {
       printf("No change to was detected\n");
    }
    
 } else { /* pid > 0; parent process */
    // Parent changing the value of was.
     was = 4; 
     printf("Parent changed the value of was to %d\n", was);
     printf("Parent waiting for child to exit\n");
     // wait for all children to exit. 
     wait(NULL);
     exit(0);
  }
}

