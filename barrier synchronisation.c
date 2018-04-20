#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

#define count 4

pthread_barrier_t mybarrier;

void* threadFn(void *id_ptr) 
{
  int thread_id = *(int*)id_ptr;
  int wait_sec = 1 + rand() % 5;
  printf("thread %d: Wait for %d seconds.\n", thread_id, wait_sec);
  sleep(wait_sec);
  printf("thread %d: I'm ready...\n", thread_id);

  pthread_barrier_wait(&mybarrier);

  printf("thread %d: going!\n", thread_id);
  return NULL;
}


int main() 
{
  int i;
  pthread_t id[count];
  int short_id[count];

  srand(time(NULL));
  pthread_barrier_init(&mybarrier, NULL, count + 1);

  for (i=0; i < count; i++) 
  {
    short_id[i] = i;
    pthread_create(&id[i], NULL, threadFn, &short_id[i]);
  }
  printf("hey i am main()--i am ready.\n");
  pthread_barrier_wait(&mybarrier);
  printf("hey i am main()--i am going!\n");
  for (i=0; i <count; i++) 
  {
    pthread_join(id[i], NULL);
  }

  pthread_barrier_destroy(&mybarrier);

  return 0;
}
