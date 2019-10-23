#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>

#define SCALE_FACTOR 100000000
#define philosopher_count 5

pthread_mutex_t chopsticks[philosopher_count];

struct thread_args {
  int tid;
};

void napping(int t){
  unsigned int i = (unsigned int) t;
  usleep(SCALE_FACTOR * rand_r(&i) / i);
}

void *Philosopher(void *id){
  struct thread_args *my_id = (struct thread_args*) id;
  //unsigned int num = my_id->tid;

  while(1){
    printf("Philosopher %d is thinking\n", my_id->tid);

    // secure the chopsticks once philosopher is hungry
    printf("Philosopher %d is hungry\n", my_id->tid);

    // entry to critical section
    if( my_id->tid % 2 == 0 ){
    pthread_mutex_lock(&chopsticks[my_id->tid]);
    printf("Philosopher %d picking up chopstick %d\n", my_id->tid, my_id->tid);
    napping(2);
    pthread_mutex_lock(&chopsticks[(my_id->tid + 1) % philosopher_count]);
    printf("Philosopher %d picking up chopstick %d\n", my_id->tid, (my_id->tid + 1) % philosopher_count);
    }
    else {
      pthread_mutex_lock(&chopsticks[(my_id->tid + 1) % philosopher_count]);
      printf("Philosopher %d picking up chopstick %d\n", my_id->tid, (my_id->tid + 1) % philosopher_count);
      napping(2);
      pthread_mutex_lock(&chopsticks[my_id->tid]);
      printf("Philosopher %d picking up chopstick %d\n", my_id->tid, my_id->tid);
    }

    printf("Philosopher %d is starting to eat\n", my_id->tid);
    printf("Philosopher %d is done eating\n", my_id->tid);

    // release the chopsticks
    pthread_mutex_unlock(&chopsticks[my_id->tid]);
    printf("Philosopher %d putting down chopstick %d\n", my_id->tid, my_id->tid);
    napping(2);
    pthread_mutex_unlock(&chopsticks[(my_id->tid + 1) % philosopher_count]);
    printf("Philosopher %d putting down chopstick %d\n", my_id->tid, (my_id->tid + 1) % philosopher_count);
  }
  //pthread_exit((void*) id);

  fflush(stdout);
}

int main(){
  int i;
  

  for(i = 0; i < philosopher_count; i++){
    pthread_mutex_init(&chopsticks[i], NULL);
  }

pthread_t *tidp;
  pthread_attr_t attr;
  struct thread_args *targs;
 
  
  targs = (struct thread_args *) calloc(philosopher_count, sizeof(struct thread_args));
  tidp = (pthread_t *) calloc(philosopher_count,sizeof(pthread_t));

  pthread_attr_init(&attr);

  for(i = 0; i < philosopher_count; i++) {
    targs[i].tid = i;
    pthread_create(&tidp[i], &attr, Philosopher, (void*)&targs[i]);
  }

  pthread_attr_destroy(&attr);
  
  usleep(10000000);

  return 0;
}
