#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<sys/wait.h>

int main() {
    int seed;
    printf("Enter Password:");
    scanf("%d", &seed);
    srand(seed);

    if (rand() == 23) {
        printf("You Win!! $$$$!\n");
    } else {
        printf("Wrong Password!\n");
    }
    return 0;
}