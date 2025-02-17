#define _GNU_SOURCE

#include <stdio.h>
#include <dlfcn.h>

int rand(void) {
    return 23;
    /*
    int (*original_rand)(void);
    original_rand = dlsym(RTLD_NEXT, "rand");
    return (*original_rand)();
    */
}