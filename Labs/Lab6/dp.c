#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define SCALE_FACTOR 1000000


int napping(int t){
  unsigned int i = (unsigned int) t;
  usleep(SCALE_FACTOR * rand_r(&i) / i);

  return 0;
}

void *Philosopher(void *id){
  int fill = (int) id;
  while(1){
  printf("Philosopher %d is thinking\n", fill);
  napping(2);
  printf("Philosopher %d is hungry\n", fill);
  printf("Philosopher %d is starting to eat\n", fill);
  napping(1);
  printf("Philosopher %d is done eating\n", fill);
  }
  //pthread_exit((void*) id);

  return 0;
}

int main(){
  int i;
  pthread_t tid;
  int num_threads = 5;
  long long id;

  for(i = 0; i < num_threads; i++) {
    id = (long long)i;
    pthread_create(&tid, NULL, Philosopher, (void*)id);
  }
  while(1){
  }
  return 0;
}
