/*
 * Copyright (c) 2013 Bucknell University
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: L. Felipe Perrone (perrone@bucknell.edu)
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h> 
#include <unistd.h>

#include "circular-list.h" 

/* SCALE_FACTOR is a constant for you to experiment with:
 * if you choose a very large SCALE_FACTOR, your threads
 * might spend a long time sleeping. If you choose it to be
 * too small, your threads will not sleep at all. Note
 * that in the producer and consumer functions, the sleep
 * time is computed as the INTEGER DIVISION below:
 *
 *  usleep(SCALE_FACTOR * rand_r(&seed) / RAND_MAX
 *
 *  where RAND_MAX is the largest random numver returned
 *  by rand_r. If the numerator is smaller than RAND_MAX,
 *  the quotient of the integer division is ZERO!
 */
#define SCALE_FACTOR 1000

// global variables -----------------------

struct circular_list mylist;

// end of global variables ----------------

void *producer (void *param) {
  item i;
  unsigned int seed = 1234;

  while (true) {
    // sleep for random period of time
    usleep(SCALE_FACTOR * rand_r(&seed) / RAND_MAX); 
    /*
      This was code I used in a while(true) statement to see if the values were random:

      i = 1000 * rand_r(&seed) / 1234; 
	
      printf("%d\n", i);

 Here were some values to prove that they were in fact being randomized:

1495574
-992995
-1271334
-1160884
-890902
38405
1109694
1485316
-535579
-465214
1594602
-1194104
377193
1725651
587622
837406
19839
1285301
-5452
-1212052
-378542
-836465
    */
    
    // generate a random number
    i = (item) (((double) rand_r(&seed)) / RAND_MAX);

    if (circular_list_insert(&mylist, i) == -1) {
      printf("PRODUCER: error condition\n");
    } else {
      printf("PRODUCER: produced value %lf\n", i);
    }
  }
}

void *consumer (void *param) {
  item i;
  unsigned int seed = 999;

  while (true) {
    // sleep for random period of time
    usleep(SCALE_FACTOR * rand_r(&seed) / RAND_MAX);

    if (circular_list_remove(&mylist, &i) == -1) {
      printf("CONSUMER: error condition\n");
    } else {
      printf("CONSUMER: consumed value %lf\n", i);
    }
  }
}

int main (int argc, char *argv[]) {

  // if error in command line argument usage, terminate with helpful
    // message
    if(argc != 4){
        printf("Incorrect number of command line arguments\n");
        printf("Usage: $ prodcons [producer threads] [consumer threads] [sleep time]\n");
        exit(-1);
    }

    // get command line arguments
    int sleep_time = atoi(argv[3]);
    int num_prod = atoi(argv[1]);
    int num_cons = atoi(argv[2]);    
    
    // initialize buffer
    circular_list_create(&mylist, 20);

    pthread_attr_t attr;

    struct thread_args *targs; // array for thread argument structs
    struct thread_args **tstatus; // array of pointers to returns from threads
    pthread_t *tidp; // array for thread ids

    int ret_val;

  
    // create producer thread(s)
    targs = (struct thread_args *) calloc(num_prod + num_cons, sizeof(struct thread_args));
    tstatus = (struct thread_args **) calloc(num_prod + num_cons, sizeof(struct thread_args *));
    tidp = (pthread_t *) calloc(num_prod + num_cons, sizeof(pthread_t));

    // initialize attr variable
    pthread_attr_init(&attr);

    // initialize thread detached state to joinable
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    
    int i;
    for (i=0; i<num_prod; i++) {
        tstatus[i] = malloc(sizeof(struct thread_args));

        targs[i].tid = i;

        ret_val = pthread_create(&tidp[i], &attr, producer, (void *) &targs[i]);
        if (ret_val) {
            printf("ERROR in pthread_create for thread %d: return value= %d\n",
                    i, ret_val);
            exit(-1);
        }
    }
    // create consumer thread(s)
    for(i=i; i < num_prod + num_cons; i++){
        tstatus[i] = malloc(sizeof(struct thread_args));

        targs[i].tid = i;

        ret_val = pthread_create(&tidp[i], &attr, consumer, (void *) &targs[i]);
        if (ret_val) {
            printf("ERROR in pthread_create for thread %d: return value= %d\n",
                    i, ret_val);
            exit(-1);
        }
    }
    
    // free attribute variable
    pthread_attr_destroy(&attr);
  
    // sleep to give time for threads to run
    usleep(sleep_time);
  
  // exit
  return (0);
}
