int foo(int a) {
   int b[2];
   b[a] = 0;
   return 0;
}
int main(int argc, char **argv) {
   foo((int)argv[0]);
   return 0;
}

