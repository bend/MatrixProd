#ifndef __NODE_H__
#define __NODE_H__

#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

typedef enum {
	head,
	tail,
	unreserved,
	reserved
}type;

typedef struct node node;

struct node{
  node* next;
  node* prev;
  matrix* matr;
  type t;
};


/*
 * Allocate mem to  the node
 * @param n: a pointer to the pointer of the node
 * @return 0 if success, -1 otherwise
 */
int
node_alloc(node** n);

/*
 * Sets the next node
 * @param n : a pointer to the current node
 * @param next: a pointer to the node that will be the next node to the current node
 */
int
node_set_next(node* n, node* next);

/*
 * Returns the next node
 * @param n: a pointer to the node
 * @return a pointer to the next node
 */
int
node_get_next(node* n, node** res);


/*
 * Returns the prev node
 * @param n: a pointer to the node
 * @return a pointer to the next node
 */
int
node_get_prev(node* n, node**res);

/*
 * Sets the element of the node
 * @param n: a pointer to the node
 * @param matr: a pointer to the matrix
 * @return: -1 if failed 0 otherwise
 */
int
node_set_elem(node* n, matrix* matr);

/*
 * Frees the node
 * @param n: a pointer to the node
 */
void
node_free(node* n);
#endif
