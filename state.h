#ifndef __STAT_H__
#define __STAT_H__

#include "stdbool.h"
#include <fcntl.h>  /*needed on linux for O_ constants */
#include "semaphore.h"

#include "node.h"
#include "linked_list.h"

#define LIST_ACCESS_MUTEX	"/list_mutex"
#define CONS_MUTEX			"/adjacent_mutex"
#define CAN_PRODUCE_SEM		"/can_produce_mutex"

struct state {
    sem_t *list_access_mutex;		/* to ensure that only on thread can access the list of matrices when doing changes requiring exclusive access */
    sem_t *consumer_allowed_sem;	/* to notify waiting consumer that one consumer can continue and look for matrices to multiply. This is a semaphore. */
    sem_t *can_produce_sem;			/* to notify the producer that it should add a matrix to the linked list */
    linked_list* ll;				/* linked list of nodes containing one matrix each */
    bool producer_finished;			/* flag indicating if producer is finished, ie no new matrix will me added to the linked list */
    unsigned exit_on_error;			/* flag indicating if an error happened. if >0, threads finish immediately and exit */
};
typedef struct state state;





/*
 * Allocate the memory for the state, creates the linked_list and all the semaphores.
 * @param s: a pointer of pointer of the state descriptor
 * @return 0 if success, -1 otherwise
 */
int
state_alloc(state** s, unsigned int buf_size);

/*
 * Frees the state;
 * @param s : state to be freed
 */
void
state_free(state *s);

#endif

