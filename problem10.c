#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

/*
 * Problem
 * This problem was asked by Apple.
 *
 * Implement a job scheduler which takes in a function f and an integer n, and calls f after n milliseconds.
 */

long getTimeInMillis();
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

typedef struct DelayedTask {
  void (*fn)();
  long dueTimeInMillis;
  int resolved;
} DelayedTask;

// We support at most 100 tasks
DelayedTask pendingTasks[100];
int lastTaskIndex = 0;

void* timer_worker(void* args) {
  printf("[Timer Thread] Hello this comes from a separate thread!\n");
  while (1) {
    pthread_mutex_lock(&lock);
    printf("[Timer Thread] Current time=%d\n", getTimeInMillis());
    long currentTime = getTimeInMillis();
    for (int i = 0; i < lastTaskIndex; i++) {
      if (pendingTasks[i].resolved == 0 && pendingTasks[i].dueTimeInMillis < currentTime) {
        printf("[Timer Thread] Working on task!\n");
        pendingTasks[i].fn();
        pendingTasks[i].resolved = 1;
      }
    }
    sleep(1);
    pthread_mutex_unlock(&lock);
  }
}

long getTimeInMillis () {
  struct timespec start;
  clock_gettime(CLOCK_MONOTONIC_RAW, &start);
  return start.tv_sec * 1000;
}

void scheduleFnCall (void *fn(), int delayInMillis) {
  printf("Scheduling a task...\n");
  pthread_mutex_lock(&lock);
  const int currentIndex = lastTaskIndex++;
  pendingTasks[currentIndex].fn = fn;
  pendingTasks[currentIndex].dueTimeInMillis = getTimeInMillis() + delayInMillis;
  pthread_cond_signal(&cond);
  pthread_mutex_unlock(&lock);
}

void saySomething() {
  printf("Haloum Mouyeee, hello!!\n");
}

int main (char** argv, int argc) {
  pthread_t timer_thread;
  int errno;
  if (errno = pthread_create(&timer_thread, NULL, timer_worker, NULL)) {
    fprintf(stderr, "Error creating thread: %s", strerror(errno));
    return errno;
  }

  scheduleFnCall(saySomething, 3000);
  scheduleFnCall(saySomething, 5000);
  if (errno = pthread_join(timer_thread, NULL)) {
    fprintf(stderr, "Error joining thread: %s", strerror(errno));
  }

  return 0;
}
