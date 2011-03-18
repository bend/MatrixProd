#ifndef __NODE_H__
#define __NODE_H__

#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"


typedef struct node node;

struct node{
  node* next;
  node* prev;
  matrix* matr;
  short type;
};

/*
 * Allocate mem to  the node
 * @return a pointer to the node
 */
node*
node_alloc();

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
node*
node_get_next(node* n);


/*
 * Returns the prev node
 * @param n: a pointer to the node
 * @return a pointer to the next node
 */
node*
node_get_prev(node* n);

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
