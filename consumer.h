#ifndef __MATRIX_MULT_H__
#define __MATRIX_MULT_H__

#include <stdbool.h>
#include "matrix.h"
#include "linked_list.h"
#include "node.h"
#include "state.h"



/*
 * Start a consumer thread
 */

/*
 * consumer function/ Will repeatedly look at the linked list of matrices to
 * find 2 adjacent free matrices to compute their multiplication.
 * Exits when the length of the linked list is one and that the producer
 * stopped.
 */
int
consumer_start(state* s);

/*
 * searches 2 adjacent matrices in the state's linked list, and makes m1 poitn
 * to the first, m2 to the second.
 * param s : state
 * param m1: will make m1 point to the first of the couple of adjacent
 *           unreserved matrices
 * param m1: will make it point to the second of the couple of adjacent
 *           unreserved matrices
 * return : true if found, false otherwise
 */
bool
consumer_search_adjacent_and_mark(state* s, node** m1, node** m2);

#endif
