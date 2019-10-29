/* Mitch Gavars
 * CSCI 315 
 * Alan Marchiori
 * Lab 7 - memory-test.c
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "allocator.h"

#define testSize 1024

int main(int argc, char *argv[]) {

  // FIRST FIT TESTING
  printf("\nAllocating space for the first fit test...\n");
  allocator_init(testSize);
  printf("Free List length= %d\n", dlist_num_elems(free_list));
  printf("Allocated List length= %d\n", dlist_num_elems(allocated_list));

  printf("\nAllocating 30 and 100 bits of memory...\n");
  allocate(30, ALLOCFITFIRST);
  allocate(100, ALLOCFITFIRST);
  printf("Free List length= %d\n", dlist_num_elems(free_list));
  printf("Allocated List length= %d\n", dlist_num_elems(allocated_list));

  printf("\nDeallocating the 100 and 30 bytes of memory...\n");
  if (deallocate((void *)100) == -1){
    printf("\nerror deallocating\n");
  }
  if (deallocate((void *)30) == -1){
    printf("\nerror deallocating\n");
  }
  printf("Free List length= %d\n", dlist_num_elems(free_list));
  printf("Allocated List length= %d\n", dlist_num_elems(allocated_list));


  // BEST FIT TESTING
  printf("\n\n\nAllocating space for the best fit test...\n");
  allocator_init(testSize);
  printf("Free List length= %d\n", dlist_num_elems(free_list));
  printf("Allocated List length= %d\n", dlist_num_elems(allocated_list));

  printf("\nAllocating and deallocating 200 bytes of memory to have a 200 free space...\n");
  allocate(200, ALLOCFITBEST);
  if (deallocate((void *)200) == -1){
    printf("\nerror deallocating\n");
  }  
  printf("Free List length= %d\n", dlist_num_elems(free_list));
  printf("Allocated List length= %d\n", dlist_num_elems(allocated_list));
  
   printf("\nAllocating 100 bytes of memory - should go into the 200 free space...\n");
  allocate(200, ALLOCFITBEST);
  printf("Free List length= %d\n", dlist_num_elems(free_list));
  printf("Allocated List length= %d\n", dlist_num_elems(allocated_list));

  // WORST FIT TESTING
  printf("\n\n\nAllocating space for the worst fit test...\n");
  allocator_init(testSize);
  printf("Free List length= %d\n", dlist_num_elems(free_list));
  printf("Allocated List length= %d\n", dlist_num_elems(allocated_list));

  printf("\nAllocating and deallocating 202, 201, & 200 bytes of memory to create free spaces. All should pass through the main memory and not be taken from the smallest data entry...\n");
  allocate(200, ALLOCFITWORST);
  if (deallocate((void *)200) == -1){
    printf("\nerror deallocating 200\n");
  }  
  allocate(201, ALLOCFITWORST);
  if (deallocate((void *)201) == -1){
    printf("\nerror deallocating 201\n");
  }  
  allocate(202, ALLOCFITWORST);
  if (deallocate((void *)202) == -1){
    printf("\nerror deallocating 202\n");
  }  
  printf("Free List length= %d\n", dlist_num_elems(free_list));
  printf("Allocated List length= %d\n", dlist_num_elems(allocated_list));

  printf("\n\nCompleting testing...\n\n");
}
