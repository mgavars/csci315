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
  printList(free_list);
  printf("\n");
  printList(allocated_list);

  printf("\n\nAllocating 500 and 520 bytes of memory...\n");
  void *a = NULL;
  void *b = NULL;
  a= allocate(500, ALLOCFITFIRST);
  b = allocate(520, ALLOCFITFIRST);
  printList(free_list);
  printf("\n");
  printList(allocated_list);

  printf("\n\nDeallocating the 520 and 500 bytes of memory...\n");
  if (deallocate(a) == -1){
    printf("\nerror deallocating\n");
  }
  if (deallocate(b) == -1){
    printf("\nerror deallocating\n");
  }
  printList(free_list);
  printf("\n");
  printList(allocated_list);
  printf("\n");
  
  printf("\nAllocating 100 bytes of memory...\n");
  allocate(100, ALLOCFITFIRST);
  printList(free_list);
  printf("\n");
  printList(allocated_list);
  printf("\n");
  
  printf("\nSize of first block of memory remaining in Free List should be 4 bytes\n");
  printf("Free List node 1 length= %d\n", free_list->front->size);
  
  printf("\nAllocating 4 bytes should remove that from the front of the free list\n");
  allocate(4,ALLOCFITFIRST);
  printList(free_list);
  printf("\n");
  printList(allocated_list);
  printf("\n");
  
  
  
  // BEST FIT TESTING
  printf("\n\n\nAllocating space for the best fit test...\n");
  allocator_init(testSize);
  printList(free_list);
  printf("\n");
  printList(allocated_list);
  printf("\n");

  printf("\nAllocating and deallocating 200 bytes of memory to have a 200 free space...\n");
  void *d = NULL;
  d = allocate(200, ALLOCFITBEST);
  if (deallocate(d) == -1){
    printf("\nerror deallocating\n");
  }  
  printList(free_list);
  printf("\n");
  printList(allocated_list);
  printf("\n");
  
   printf("\nAllocating 100 bytes of memory - should split the 200 free space...\n");
  allocate(100, ALLOCFITBEST);
  printList(free_list);
  printf("\n");
  printList(allocated_list);
  printf("\n");
  
  
  // WORST FIT TESTING
  printf("\n\n\nAllocating space for the worst fit test...\n");
  allocator_init(testSize);
  printList(free_list);
  printf("\n");
  printList(allocated_list);
  printf("\n");
 

  printf("\nAllocating and deallocating 202, 201, & 200 bytes of memory to create free spaces. All should pass through the main memory and not be taken from the smallest data entry...\n");
  void *e = NULL;
  e = allocate(200, ALLOCFITWORST);
  if (deallocate(e) == -1){
    printf("\nerror deallocating 200\n");
  }  
  void *f = NULL;
  f = allocate(201, ALLOCFITWORST);
  if (deallocate(f) == -1){
    printf("\nerror deallocating 201\n");
  }  
  void *g = NULL;
  g = allocate(202, ALLOCFITWORST);
  if (deallocate(g) == -1){
    printf("\nerror deallocating 202\n");
  }  
  printList(free_list);
  printf("\n");
  printList(allocated_list);
  printf("\n");

  printf("\n\nCompleting testing...\n\n");
  
}
