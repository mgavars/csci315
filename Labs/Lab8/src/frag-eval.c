/* Mitch Gavars
 * CSCI 315 
 * Alan Marchiori
 * Lab 8 - frag-eval.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "allocator.h"

#define size 10240
#define RUNSIZE 30

int main(int argc, char *argv[]){

  int runs = 0;
  double avgFrag = 0.0;
  double exFrag = 0.0;
  int seed = atoi(argv[2]);

  totalExFrag = 0;

  allocator_init(size);
  
  //srand(atoi(argv[2])); 

  int r = 0;

  void *p = NULL;

  int s;

  enum fitType algorithm;
  
  if (atoi(argv[1]) == 0){
    algorithm = ALLOCFITFIRST;
  }
  else if (atoi(argv[1]) == 1){
    algorithm = ALLOCFITBEST;
  }
  else if (atoi(argv[1]) == 2){
    algorithm = ALLOCFITWORST;
  }
  else {
    return -1;
  }
 
  while(runs < RUNSIZE){
    srand(seed + runs);
 
    while(r < atoi(argv[3])) {
      s = 100 + rand()%900;
      printf("%d\n", s);
      if (s < 1000 && s > 100){
	p = allocate(algorithm, (size_t)s );

	deallocate(p);

	r++;
      }
    }
    
    
      printf("Free List: \n");
      printList(free_list);
      printf("\n\nAllocated List: \n");
      printList(allocated_list);
      printf("\n\n");
    

  avgFrag += average_frag();
  
  runs += 1;

  r = 0;
  
  }
  
  exFrag = avgFrag / totalExFrag ;

  printf("Total fragmentation for %d runs is= %lf\n", RUNSIZE,  exFrag); 

  return 0;
}
