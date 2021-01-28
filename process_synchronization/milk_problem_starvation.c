#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *check_buy_milkA( void *ptr );
void *check_buy_milkB( void *ptr );
int has_milk;
int has_noteA;
int has_noteB;

void main()
{
     pthread_t thread1, thread2;
     has_milk = 0;
     has_noteA = 0;
     has_noteB = 0;
     
     printf("---Starting---\n");
     pthread_create( &thread1, NULL, check_buy_milkA, (void*) "PersonA");
     pthread_create( &thread2, NULL, check_buy_milkB, (void*) "PersonB");

     pthread_join(thread1, NULL);
     pthread_join(thread2, NULL); 
     if (!has_milk) {
        printf("Starvation detected: No one bought milk.\n");
     }
     printf("---End---\n");
     exit(0);
}

void *check_buy_milkA( void *ptr )
{
     char *message;
     message = (char *) ptr;
     has_noteA = 1;
     pthread_yield();
     if (!has_noteB) {
     	if (!has_milk) {
     	  pthread_yield(); 
     	  printf("%s buying milk\n", message);
          has_milk = 1;
     	}
     }
     has_noteA = 0;
     return NULL;
}

void *check_buy_milkB( void *ptr )
{
     char *message;
     message = (char *) ptr;
     has_noteB = 1;
     pthread_yield();
     if (!has_noteA) {
     	if (!has_milk) {
     	  pthread_yield(); 
     	  printf("%s buying milk\n", message);
          has_milk = 1;
     	}
     }
     has_noteB = 0;
     return NULL;
}
