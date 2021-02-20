#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *thread_func(void *ptr);
int global;

void main()
{
     pthread_t thread1;
     int local, i;
     srand(time(NULL));
     printf("---Starting---\n");
     pthread_create( &thread1, NULL, thread_func, (void*) "Child Thread");
     
     for (i=0; i<10; i++) {
		global = rand();
       	local = rand();
  		printf("Parent changing global to %d\n", global);
  		printf("Parent changing local to %d\n", local);
  		sleep(1);
     }

     pthread_join(thread1, NULL);
     
     printf("---End---\n");
     exit(0);
}

void *thread_func(void *ptr)
{
     int local, i;
     char *message;
     message = (char *) ptr;
     global = rand();
     printf("%s changing global to %d\n", message, global);
     local = rand();
     printf("%s changing local to %d\n", message, local);
     
     for(i=0; i<10; i++) {
		printf("%s global value is %d\n", message, global);
  		printf("%s local value is %d\n", message, local);
  		sleep(1);
        
     }
     return NULL;
}
