#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

#include <stdio.h>
#include <stdlib.h>

#include "node.h"
#include "matrix.h"

typedef struct linked_list linked_list;

struct linked_list
{
    node* head;
    node* tail;
};


/*
 * Creates a new linked list with 2 nodes : tail and head
 * @param ll: a pointer to the pointer of the ll
 * @return 0 if success, -1 otherwise
 */
int
linked_list_alloc(linked_list** ll);

/*
 * Frees the linked_list
 */
void
linked_list_free(linked_list* ll);

/*
 * Adds the matrix at the end of the list
 * @param ll: a pointer to the linked_list
 * @param matr: a pointer to the matrix
 * @return -1 if failure, 0 otherwise
 */
int
linked_list_add_last(linked_list* ll, matrix* matr);

/*
 * Adds the matrix at the begining of the list
 * @param ll: a pointer to the linked_list
 * @param matr: a pointer to the matrix
 * @return -1 if failure, 0 otherwise
 */
int
linked_list_add_first(linked_list* ll, matrix* matr);

/*
 * returns the element at the end of the list, but does not remove it
 * @param ll: a pointer to the linked_list
 * @return the matrix that is at the end of the ll.
 */
int
linked_list_get_last(linked_list* ll, matrix** matr);

/*
 * returns the element at the begining of the list, but does not remove it
 * @param ll: a pointer to the linked_list
 * @return the matrix that is at the begining of the ll
 */
int
linked_list_get_first(linked_list* ll, matrix** matr);

/*
 * removes the elements at end of the linked_list
 */
int
linked_list_remove_first(linked_list* ll, matrix** matr);

#endif

