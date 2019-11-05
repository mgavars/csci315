/*
 * Mitch Gavars
 * CSCI 315
 * Alan Marchiori
 * Lab 7 - allocator.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "allocator.h"


int allocator_init(size_t size) {
  free_list = dlist_create();
  allocated_list = dlist_create();

  void *initBlock = malloc(size);
 
  if (initBlock == NULL){
    return -1;
  }

  dlist_add_front(free_list, initBlock, size);

  return 0;
}

void *firstFitAllocate(size_t size){
  struct dnode *temp = free_list->front;
  void *insert;
  int nodeSize;
  
 
  while(temp != NULL) { 
    if ((int)size == temp->size){
      insert = temp->data;
      dlist_add_back(allocated_list, insert, size);
      dlist_find_remove(free_list, insert, &nodeSize);   
 
      break;
    }
    else if ((int)size < temp->size) {
      temp->size -= (int)size;
      insert = temp->data;

      dlist_add_back(free_list, temp->data + size, temp->size);

      dlist_find_remove(free_list, insert, &nodeSize);

      dlist_add_back(allocated_list, insert, size);
      

      break;
    }
    temp = temp->next;
  }
  return insert;
}

void *bestFitAllocate(size_t size) {
  
  struct dnode *temp = free_list->front;
  struct dnode *currentSmallest = temp;
  int nodeSize;
  void *insert;

  // check if free list is all allocated

  while(temp != NULL) {
    
    if (size <= (size_t)temp->size) {

      if (temp->size < currentSmallest->size) {

	currentSmallest = temp;

      }
    }
    temp = temp->next;
  }

  insert = currentSmallest->data;
  
  currentSmallest->size -= (int)size;

  dlist_add_back(free_list, currentSmallest->data + size, currentSmallest->size);

  dlist_find_remove(free_list, insert, &nodeSize);

  dlist_add_back(allocated_list, insert, size);
  
  return insert;
}

void *worstFitAllocate(size_t size) {
  
  struct dnode *temp = free_list->front;
  struct dnode *currentLargest = free_list->front;
  int nodeSize;
  void *insert;
  


  while(temp != NULL) {
    if (size <= (size_t)temp->data) {

      if (temp->size > currentLargest->size) {

	currentLargest = temp;

      }
    }
   
    temp = temp->next;
  }

  insert = currentLargest->data;
  
  currentLargest->size -= (int)size;

  dlist_add_back(free_list, currentLargest->data + size, currentLargest->size);

  dlist_find_remove(free_list, insert, &nodeSize);

  dlist_add_back(allocated_list, insert, size);
  
  
  return insert;
}


void *allocate(size_t size, enum fitType fit) {
  void *block = NULL;

  if (fit == ALLOCFITFIRST){
    block = firstFitAllocate(size);
  }

  if (fit == ALLOCFITBEST){
    block = bestFitAllocate(size);
  }

  if (fit == ALLOCFITWORST){
    block = worstFitAllocate(size);
  }

  return block;
}
  

int deallocate(void *ptr) { 
  int size;
  void *removedNode = dlist_find_remove(allocated_list, ptr, &size);
  if (removedNode != NULL) {
    dlist_add_back(free_list, removedNode, size);
    
    return 0;
  }
  else {
    return -1;
  }

}

int printList(struct dlist *l) {
  struct dnode *n = l->front;

  printf("[ ");

  while (n != NULL){
    printf("[data: %p, size = %d] ", n->data, n->size);

    n = n->next;
  }

  printf(" ]");
  return 0;
}
