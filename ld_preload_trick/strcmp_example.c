#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<sys/wait.h>

int main() {
    char input_str[9], tmp;
    int i, len;
    printf("Enter Password:");
    scanf("%8s", input_str);
    len = strlen(input_str);
    for (i=0; i<len/2; i++) {
        tmp = input_str[i];
        input_str[i] = input_str[len-i-1];
        input_str[len-i-1] = tmp;
    }
    if (strcmp(input_str, "w1sD)n") == 0) {
        if (strcmp("hello", "hell0") == 0) {
            printf("Cheating Detected!\n");
        } else {
            printf("You Win!! $$$$!\n");
        }
        
    } else {
        printf("Wrong Password!\n");
    }
    return 0;
}