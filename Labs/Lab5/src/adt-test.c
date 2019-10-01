/* 
 * Mitch Gavars
 * CSCI 315 Prelab 5 - adt-test.c
 * Alan Marchiori
 * 9/30/19
 */
#include "circular-list.h"
#include <stdio.h>

int print_list(struct circular_list *l) {
	int start = l->start, end = l->end;
	if (l->elems == 0) {
		printf("The list is empty\n\n");
		return 0;
	}
	else if (start <= end) {
		for(int i = start; i <= end; i++) {
			printf("%lf ", l->buffer[i]);
		}
	}
	else {
		for(int i = start; i < l->size; i++) {
			printf("%lf ", l->buffer[i]);
		}
		for(int i = 0; i <= l->end; i++) {
			printf("%lf ", l->buffer[i]);
		}
	}
	printf("\n\n");
	return 0;
}

int main() {
	int LENGTH = 4;
	item a;
	// create circular list of length 4
	struct circular_list l;
	printf("TESTING CIRCULAR LIST IMPLEMENTATION\n\ncreating circular list of length 4\n");
	circular_list_create(&l, LENGTH);

	printf("testing 4 inserts\n");
	circular_list_insert(&l, 1.0);
	circular_list_insert(&l, 2.0);
	circular_list_insert(&l, 3.0);
	circular_list_insert(&l, 4.0);
	printf("printing list, should be: 1.0 2.0 3.0 4.0\n");
	print_list(&l);

	//This should not insert as the list is full
	printf("attempting to insert element into full list (list should remain unchanged)\n");
	circular_list_insert(&l, -1.0);
	print_list(&l);

	printf("Testing remove, result should be 1.0\n");
	circular_list_remove(&l, &a);
	printf("%lf\n", a);
	printf("printing list, should be 2.0 3.0 4.0\n");
	print_list(&l);

	printf("Testing remove, result should be 2.0\n");
	circular_list_remove(&l, &a);
	printf("%lf\n", a);
	printf("printing list, should be 3.0 4.0\n");
	print_list(&l);

	printf("Testing remove, result should be 3.0\n");
	circular_list_remove(&l, &a);
	printf("%lf\n", a);
	printf("printing list, should be 4.0\n");
	print_list(&l);

	printf("Testing adding 2 elements to the list, result should be 4.0, 5.0, 6.0\n");
	circular_list_insert(&l, 5.0);
	circular_list_insert(&l, 6.0);
	print_list(&l);

	printf("Removing 3 elements from list. result should be empty list\n");
	circular_list_remove(&l, &a);
	printf("%lf\n", a);
	circular_list_remove(&l, &a);
	printf("%lf\n", a);
	circular_list_remove(&l, &a);
	printf("%lf\n", a);
	print_list(&l);

	printf("Testing removing elements element from empty list. result should still be empty list\n");
	circular_list_remove(&l, &a);
	print_list(&l);

	printf("Testing complete!\n");

	return 0;
}
