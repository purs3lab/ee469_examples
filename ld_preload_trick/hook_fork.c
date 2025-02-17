#define _GNU_SOURCE

#include <stdio.h>
#include <dlfcn.h>
#include <sys/types.h>
#include <unistd.h>


pid_t fork(void) {
    // just execute child.
    return 0;
    /*
    pid_t (*original_fork)(void);
    original_fork = dlsym(RTLD_NEXT, "fork");
    return (*original_fork)();
    */
}