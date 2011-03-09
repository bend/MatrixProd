#ifndef __NODE_H__
#define __NODE_H__

#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"


typedef struct node node;

struct node{
  node* next;
  matrix* matr;
};

/*
 * Creates the node
 * @return a pointer to the node
 */
node*
create_node();

/*
 * Sets the next node
 * @param n : a pointer to the current node
 * @param next: a pointer to the node that will be the next node to the current node
 */
int
set_next_node(node* n, node* next);

/*
 * Returns the next node
 * @param n: a pointer to the node
 * @return a pointer to the next node
 */
node*
get_next_node(node* n);

/*
 * Sets the element of the node
 * @param n: a pointer to the node
 * @param matr: a pointer to the matrix
 * @return: -1 if failed 0 otherwise
 */
int
set_elem_node(node* n, matrix* matr);

/*
 * Frees the node
 * @param n: a pointer to the node
 */
void
free_node(node* n);
#endif
