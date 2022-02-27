#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

uint32_t lock = 0;
uint32_t counter = 0;
pthread_mutex_t gmutex;

#define N_THREADS (30)
#define N_COUNT (50)


void bad_lock(volatile uint32_t *lock) {
  while(*lock == 1);
  *lock = 1;
}

void bad_unlock(volatile uint32_t *lock) {
  *lock = 0;
}


static inline uint32_t
xchg(volatile uint32_t *addr, uint32_t newval)
{
	uint32_t result;
	
	asm volatile("xchgl %0, %1"
		     : "+m" (*addr), "=a" (result)
		     : "1" (newval)
		     : "cc");
	return result;
}

static inline uint32_t 
cmpxchg(volatile uint32_t *addr, uint32_t oldVal, uint32_t newVal)
{
    uint32_t ret;
    asm volatile("lock; cmpxchgl %2,%1"			\
			     : "=a" (ret), "+m" (*addr)		\
			     : "r" (newVal), "0" (oldVal)			\
			     : "memory");

    return ret;
}

void xchg_lock(volatile uint32_t *lock) {
  while(xchg(lock, 1));
}

void xchg_unlock(volatile uint32_t *lock) {
  xchg(lock, 0);
}


void cmpxchg_lock(volatile uint32_t *lock) {
  while(cmpxchg(lock, 0, 1));
}

void 
backoff_cmpxchg_lock(volatile uint32_t *lock) {
  uint32_t backoff = 1;
  int i;
  while(cmpxchg(lock, 0, 1)) {
    for (i=0; i<backoff; i++) {
      __asm volatile("pause");
    }
    if (backoff < 0x10000) {
      backoff <<=1;
    }
  }
}

void 
tts_xchg_lock(volatile uint32_t *lock) {
  while(1) {
    while(*lock == 1);
    if(xchg(lock, 1) == 0) {
      break;
    }
  }
}

void *count_tts_xchg_lock(void *args) {
  int i;
  for (i=0; i < N_COUNT; i++) {
    tts_xchg_lock(&lock);
    sched_yield();
    counter += 1;
    xchg_unlock(&lock);
  }
  return NULL;
}

void *count_backoff_cmpxchg_lock(void *args) {
  int i;
  for (i=0; i < N_COUNT; i++) {
    backoff_cmpxchg_lock(&lock);
    sched_yield();
    counter += 1;
    xchg_unlock(&lock);
  }
  return NULL;
}

void *count_xchg_lock(void *args) {
  int i;
  for (i=0; i < N_COUNT; i++) {
    xchg_lock(&lock);
    sched_yield();
    counter += 1;
    xchg_unlock(&lock);
  }
  return NULL;
}

void *count_cmpxchg_lock(void *args) {
  int i;
  for (i=0; i < N_COUNT; i++) {
    cmpxchg_lock(&lock);
    sched_yield();
    counter += 1;
    xchg_unlock(&lock);
  }
  return NULL;
}


void *count_bad_lock(void *args) {
  int i;
  for (i=0; i < N_COUNT; i++) {
    bad_lock(&lock);
    sched_yield();
    counter += 1;
    bad_unlock(&lock);
  }
  return NULL;
}

void *count_no_lock(void *args) {
  int i;
  for (i=0; i < N_COUNT; i++) {
    sched_yield();
    counter += 1;
  }
  return NULL;
}

void *count_mutex(void *args) {
  int i;
  for (i=0; i < N_COUNT; i++) {
    pthread_mutex_lock(&gmutex);
    sched_yield();
    counter += 1;
    pthread_mutex_unlock(&gmutex);
  }
  return NULL;
}

int main(int argc, char **argv) {
  pthread_t threads[N_THREADS];
  int i;
  clock_t t;
  double time_taken;
  t = clock();
  if (argc <= 1) {
    printf("Running %d threads each counting to %d using no lock\n", N_THREADS, N_COUNT);
    for (i=0; i < N_THREADS; i++) {
      pthread_create(&threads[i], NULL, count_no_lock, NULL);
    }
  } else if (!strcmp(argv[1], "no")) {
    printf("Running %d threads each counting to %d using %s lock\n", N_THREADS, N_COUNT, argv[1]);
    for (i=0; i < N_THREADS; i++) {
      pthread_create(&threads[i], NULL, count_no_lock, NULL);
    }
  } else if (!strcmp(argv[1], "bad")) {
    printf("Running %d threads each counting to %d using %s lock\n", N_THREADS, N_COUNT, argv[1]);
    for (i=0; i < N_THREADS; i++) {
      pthread_create(&threads[i], NULL, count_bad_lock, NULL);
    }
  } else if (!strcmp(argv[1], "xchg")) {
    printf("Running %d threads each counting to %d using %s lock\n", N_THREADS, N_COUNT, argv[1]);
    for (i=0; i < N_THREADS; i++) {
      pthread_create(&threads[i], NULL, count_xchg_lock, NULL);
    }
  } else if (!strcmp(argv[1], "cmpxchg")) {
    printf("Running %d threads each counting to %d using %s lock\n", N_THREADS, N_COUNT, argv[1]);
    for (i=0; i < N_THREADS; i++) {
      pthread_create(&threads[i], NULL, count_cmpxchg_lock, NULL);
    }
  } else if (!strcmp(argv[1], "tts")) {
    printf("Running %d threads each counting to %d using %s lock\n", N_THREADS, N_COUNT, argv[1]);
    for (i=0; i < N_THREADS; i++) {
      pthread_create(&threads[i], NULL, count_tts_xchg_lock, NULL);
    }
  } else if (!strcmp(argv[1], "backoff")) {
    printf("Running %d threads each counting to %d using %s lock\n", N_THREADS, N_COUNT, argv[1]);
    for (i=0; i < N_THREADS; i++) {
      pthread_create(&threads[i], NULL, count_backoff_cmpxchg_lock, NULL);
    }
  } else if (!strcmp(argv[1], "mutex")) {
    printf("Running %d threads each counting to %d using %s lock\n", N_THREADS, N_COUNT, argv[1]);
    for (i=0; i < N_THREADS; i++) {
      pthread_create(&threads[i], NULL, count_mutex, NULL);
    }
  } else {
    printf("Invalid lock type. Exiting.\n");
    exit(-1);
  }
  
  for (i=0; i < N_THREADS; i++) {
    pthread_join(threads[i], NULL);
  }
  t = clock() - t;
  time_taken = ((double)t)/(CLOCKS_PER_SEC / 1000);
  printf("Result:%u, Time taken: %lf ms\n", counter, time_taken);
}
