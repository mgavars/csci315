/*
 * Mitch Gavars
 * Professor Marchiori
 * CSCI 315 Prelab 2
 * 9/09/2019
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(){
  
  int *i;
  i = (int *)malloc(sizeof(int));

  int pid = fork();

  if (pid == 0) {
    printf("Heap of child is: %d\n", i);
  }
  else {
    printf("Heap of parent is: %d\n", i);
  }


}
