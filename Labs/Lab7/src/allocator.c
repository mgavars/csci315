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
 
  if (malloc(size) == NULL){
    return -1;
  }

  void *memory = (void *)size;

  struct dnode *init = dnode_create();
  dnode_setdata(init, memory);

  dlist_add_front(free_list, init);

  return 0;
}

void *firstFitAllocate(size_t size){
  struct dnode *temp = free_list->front;
  //struct dnode *allocate = dnode_create();
  void *memory = (void *)size;

  if (temp->next == NULL) {
    if (size <= (size_t)temp->data){
      dlist_add_front(allocated_list, memory);
    }  
  }
  
  else {
    while(temp->next != NULL) { 
      if (size <= (size_t)temp->data){
	dlist_add_front(allocated_list, memory);
	break;
      }
   
      temp = temp->next;
    }
  }
  return 0;
}

void *bestFitAllocate(size_t size) {
  struct dnode *temp = free_list->front;
  struct dnode *currentSmallest = free_list->front;
  void *memory;

  if (temp->next == NULL) {
    if (size <= (size_t)temp->data){
      memory = (void *)size;
    }  
  }

  else {
    while(true) {
      if (size <= (size_t)temp->data) {
	if (temp->data < currentSmallest->data) {
	  memory = (void *)temp->data;
	  dnode_setdata(currentSmallest, memory);
	}
      }
      if (temp->next == NULL) {
	break;
      }
      temp = temp->next;
    }
  }
  dlist_add_back(allocated_list, memory);
  dlist_find_remove(free_list, memory);
  return 0;
}

void *worstFitAllocate(size_t size) {
  struct dnode *temp = free_list->front;
  struct dnode *currentLargest = free_list->front;
  void *memory = (void *) size;
  
  if (temp->next == NULL) {
    if (size <= (size_t)temp->data){
      memory = (void *)size;
    }  
  }

  else {
    while(true) {
      if (size <= (size_t)temp->data) {
	if (temp->data > currentLargest->data) {
	  memory = (void *)temp->data;
	  dnode_setdata(currentLargest, memory);
	}
      }
      if (temp->next == NULL) {
	break;
      }
      temp = temp->next;
    }
  }
  dlist_add_back(allocated_list, memory);
  dlist_find_remove(free_list, memory);
  return 0;
}


void *allocate(size_t size, enum fitType fit) {
  if (fit == ALLOCFITFIRST){
    firstFitAllocate(size);
  }

  if (fit == ALLOCFITBEST){
    bestFitAllocate(size);
  }

  if (fit == ALLOCFITWORST){
    worstFitAllocate(size);
  }
  return 0;
}
  

int deallocate(void *ptr) { 
  void *removedNode = dlist_find_remove(allocated_list, ptr);
  if (removedNode != NULL) {
    dlist_add_back(free_list,removedNode);    
    return 0;
  }
  else {
    return -1;
  }

}
