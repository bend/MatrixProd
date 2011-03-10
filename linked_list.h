#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

#include <stdio.h>
#include <stdlib.h>

#include "node.h"
#include "matrix.h"

typedef struct linked_list linked_list;

struct linked_list{
	node* head;
	node* tail;
	unsigned int size;
};


/*
 * Creates a new linked list
 * @return the linked_list descriptor
 */
linked_list*
create_linked_list();

/*
 * Frees the linked_list
 */
void
free_linked_list(linked_list *ll);

/*
 * Adds the matrix at the end of the list
 * @param ll: a pointer to the linked_list
 * @param matr: a pointer to the matrix
 * @return -1 if failure, 0 otherwise
 */
int
add_last_linked_list(linked_list *ll, matrix *matr);

/*
 * Adds the matrix at the begining of the list
 * @param ll: a pointer to the linked_list
 * @param matr: a pointer to the matrix
 * @return -1 if failure, 0 otherwise
 */
int
add_first_linked_list(linked_list *ll, matrix *matr);

/*
 * returns the element at the end of the list, but does not remove it
 * @param ll: a pointer to the linked_list
 * @return the matrix that is at the end of the ll.
 */
matrix*
get_last_linked_list(linked_list *ll);

/*
 * returns the element at the begining of the list, but does not remove it
 * @param ll: a pointer to the linked_list
 * @return the matrix that is at the begining of the ll
 */
matrix*
get_first_linked_list(linked_list *ll);

/*
 * removes the elements at end of the linked_list
 */
matrix*
remove_elem_first_linked_list(linked_list *ll);

#endif

