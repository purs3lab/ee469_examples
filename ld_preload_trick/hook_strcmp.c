#define _GNU_SOURCE

#include <stdio.h>
#include <dlfcn.h>
#include <string.h>

int strcmp(const char *s1, const char *s2) {
    // always say strings matched.
    return 0;
    /*
    int (*original_strcmp)(const char *s1, const char *s2);
    original_strcmp = dlsym(RTLD_NEXT, "strcmp");
    return (*original_strcmp)(s1, s2);
    */
}
