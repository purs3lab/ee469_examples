#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *check_buy_milk( void *ptr );
int has_milk;

void main()
{
     pthread_t thread1, thread2;
     has_milk = 0;
     printf("---Starting---\n");
     pthread_create( &thread1, NULL, check_buy_milk, (void*) "PersonA");
     pthread_create( &thread2, NULL, check_buy_milk, (void*) "PersonB");

     pthread_join(thread1, NULL);
     pthread_join(thread2, NULL); 
     printf("---End---\n");
     exit(0);
}

void *check_buy_milk( void *ptr )
{
     char *message;
     message = (char *) ptr;
     if (!has_milk) {
     	  pthread_yield(); 
     	  printf("%s buying milk\n", message);
          has_milk = 1;
     }
     return NULL;
}
