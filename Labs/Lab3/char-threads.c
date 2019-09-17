/*
 * Mitch Gavars
 * Professor Marchiori
 * CSCI 315 Prelab3 - char-threads.c
 * 9/16/2019
 */

#include <pthread.h>
#include <stdio.h>


void *printNumber(void *arg) {
  int m = 0;
  int sum = 0;

  int number = *(int *)arg;
  while(1) {

    if (number == 10) {
      number = 0;
    }
    else {
      printf("%d\n", number);
      number++;
    }
    while (m <= 10000000) {
      sum += m;
      m++;
    }
  }
  pthread_exit(NULL);
}

void *printChar(void *arg){
  char a = *(char *)arg;
  int m = 0;
  int sum = 0;
  while(1) {
    if (a == 'z') {
      printf("%c\n", a);
      a = 'a';
    }
    else {
      printf("%c\n", a);
      a++;
    }
    while (m <= 10000000) {
      sum += m;
      m++;
    }
  }
  pthread_exit(NULL);
}

void *printPound(void *arg) {
  int sum = 0;
  int m = 0;
  while (1) {
    printf("%c\n", *(char *)arg);
    while (m <= 10000000) {
      sum += m;
      m++;
    }
  }
}



int main() {
  pthread_t tidNum;
  pthread_t tidChar;
  pthread_t tidPound;
  int number;
  char c = 'a';
  int a;
  int sum;
  int m = 1;
  char pound = '#';

  pthread_create(&tidNum, NULL, printNumber, &m);
  pthread_create(&tidChar, NULL, printChar, &c);
  pthread_create(&tidPound, NULL, printPound, &pound);
  
  pthread_join(tidChar, NULL);
  pthread_join(tidNum, NULL);
  pthread_join(tidPound,NULL);
    
  

  return 0;
}
