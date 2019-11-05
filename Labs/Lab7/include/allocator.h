/*
 * Mitch Gavars
 * CSCI 315
 * Alan Marchiori
 * Lab 7 - allocator.h
 */

#ifndef _ALLOC_H_
#define _ALLOC_H_

#include <stdio.h>
#include "dnode.h"
#include "dlist.h"

enum fitType {ALLOCFITFIRST, ALLOCFITBEST, ALLOCFITWORST};
struct dlist *free_list;
struct dlist *allocated_list;

/*
 This function will create and initialize two doubly-linked lists used for memory management: one which keeps track of the memory that is available (call it free_list) and another which keeps track of memory which is already in use (call it allocated_list). All the memory manipulated by your allocator will reside in the heap of the process that uses it. When allocator_init starts, it will call the standard malloc to request a contiguous space of size bytes from the underlying operating system. The pointer received from malloc will be used to initialize a single node in your free_list; your allocated_list must start out empty. If the malloc call does not succeed, this function must return -1, otherwise, it must return 0
*/
int allocator_init(size_t size);

/*
Equivalent to malloc. This function will traverse the free_list and find a contiguous chunk of memory that can be used to satisfy the request of an area of size bytes. If the caller makes a request for memory that is larger than what your allocator can honor, this function must return NULL. Your allocate function must be flexible enough to allow for different allocation policies, namely first-fit, best-fit, and worst-fit.
 */

void *allocate(size_t size, enum fitType fit);

void *firstFitAllocate(size_t size);

void *bestFitAllocate(size_t size);

void *worstFitAllocate(size_t size);


/*
Equivalent to free. This function will use ptr to find the corresponding node in the allocated_list and free up that chunk of memory. If the caller attempts to deallocate a pointer that cannot be found in the allocated_list, this function must return -1, otherwise it must return 0
 */
int deallocate(void *ptr);

int printList(struct dlist *l);

#endif /* _ALLOC_H_ */
