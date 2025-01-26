#include<stdio.h>

extern float sine(float x);

int main(int argc, char **argv) {
   static float x, val;
   printf("Type Number:");
   scanf("%f", &x);
   val = sine(x);
   printf("Sine is %f\n", val);
   return 0;
}

