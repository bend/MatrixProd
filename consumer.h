#ifndef __MATRIX_MULT_H__
#define __MATRIX_MULT_H__

#include <stdbool.h>
#include "matrix.h"
#include "linked_list.h"
#include "node.h"
#include "state.h"
#include <pthread.h>



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
 * param n1: will make m1 point to the first of the couple of adjacent
 *           unreserved matrices nodes
 * param n2: will make it point to the second of the couple of adjacent
 *           unreserved matrices nodes
 * return : true if found, false otherwise
 */
bool
consumer_search_adjacent_and_mark(state* s, node** n1, node** n2);

/*
 * will start i consumer threads
 * @param i: number of threads to start
 * @param threads: will keep references to threads so they can be joined bby the calling thread
 * @param s: current state
 */
int
consumer_threads_start(int i, pthread_t *threads, state *s);

#endif
