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

struct state{
	sem_t *list_access_mutex;
	sem_t *consumer_allowed_mutex;
	sem_t *can_produce_sem;
	linked_list* ll;
	bool producer_finished;
	unsigned exit_on_error;
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

