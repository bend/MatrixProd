#include "consumer.h"

/* This is the function doing the work of one consumer
 * @param state : current state
 * @return: 0 if success, -1 otherwise
 */ 
int consumer_start(state * state){
	node *node1, *node2;
	matrix *result;

	sem_wait(state->consumer_allowed_mutex);
	/* Loop as long as producer active and list longer than one matrix node 
	 * and no error happened anywhere else in the code */
	while ((state->producer_finished!=true || state->ll->head->next->next->t!=tail) && state->exit_on_error==0) {
		/* Reinitialise pointers to null at start of loop as they're freed at
		 * the end iof the loop*/
		node1=NULL;
		node2=NULL;

		/* consumer_search_adjacent_and_mark uses a mutex to get exclusive access
		 * to the state's linked list.
		 */
		/* try to find matrices to multiply as long as producer active and list
		 * has more than one matrix node */
		/* FIXME: check that second test is ok when list empty */
		while (!consumer_search_adjacent_and_mark(state, &node1, &node2) &&  state->ll->head->next->next->t!=tail && state->exit_on_error==0){
			sem_wait(state->consumer_allowed_mutex);
		}
		/* if node1 and node2!=null , it means we reserved 2 instances,
		 * otherwise the computation is finished and we will get out of the
		 * while loop too.
		 * */
		if (node1!=NULL && node2!=NULL && state->exit_on_error==0) {
			/* compute the multiplication of m1 and m2 */
			if (matrix_multiply(&result, node1->matr, node2->matr)==-1){
				perror("multiplication failed!\n");
				/*FIXME: noeed some cleanup here */
				return -1;
			}

			/*************************************************************************
			 *                 LOCK ACCESS TO LIST
			 ************************************************************************/
			/* put result back in list */
			sem_wait(state->list_access_mutex);

			matrix_free(node1->matr);
			node1->matr=result;
			node_set_next(node1, node2->next);
			node1->t=unreserved;
			/* if previous or next matrix is unreserved, notify a consumer that he can take a look at the list */
			if (node1->prev->t==unreserved || node1->next->t==unreserved){
				sem_post(state->consumer_allowed_mutex);
			}
			sem_post(state->list_access_mutex);
			/*************************************************************************
			 *                 UNLOCK ACCESS TO LIST
			 ************************************************************************/

			node_free(node2);
			sem_post(state->can_produce_sem);
		}
	}

	/* allow consumers to unblock those waiting */
	sem_post(state->consumer_allowed_mutex);
	return 0;
}

bool
consumer_search_adjacent_and_mark(state* state, node** n1, node** n2){
	bool found=false;
	matrix *m1, *m2;
	node* current_node;
	sem_wait(state->list_access_mutex);
	/* iterate over list starting at first matrix node */
	current_node=state->ll->head->next;
	/* stop when current node is tail (in case of empty list
	 *      when current_node->next is tail
	 *      when found = true
	 */
	while( current_node->t!=tail && current_node->next->t!=tail && found==false && state->exit_on_error==0 ){
		if (current_node->t==unreserved && current_node->next->t==unreserved) {
			/* two adjacent unreserved nodes found!
			 *  take matrices and mark nodes as reserved */
			*n1=current_node;
			*n2=current_node->next;

			m1=(*n1)->matr;
			m2=(*n2)->matr;
			current_node->t=reserved;
			current_node->next->t=reserved;
			found=true;  /*exit the while loop */
		}
		else {
			current_node=current_node->next;
		}
	}
	sem_post(state->list_access_mutex);

	return found;
}

/*
 * does a malloc of the retval returned by the thread.
 * This needs to be freed after joining the thread and getting its return value
 */
void
* consumer_thread(void * params) {
	int * retval;
	state *s;
	retval=malloc(sizeof(int));
	s = (state *) params;
	if (consumer_start( s )==0){
		*retval=0;
		pthread_exit( (void *) retval);
	}
	else {
		*retval=-1;
		s->exit_on_error++;
		pthread_exit( (void *) retval);
	}
}

int
consumer_threads_start(int i, pthread_t *threads , state *s){
	int j;
	for (j=0; j<i; j++) {
#ifdef DEBUG
		printf("Starting thread %d\n",j);
#endif
		if (pthread_create(&threads[j], NULL, consumer_thread, s )==-1){
#ifdef DEBUG
			printf("Problem creating consumer thread\n");
#endif
			return -1; /*FIXME: add some cleanup */
			/*FIXME: we need to free the threads pointers allocated in the array!*/
		}
		else {
#ifdef DEBUG
			printf("Created consumer thread %d successfully\n",j);
#endif
		}
	}
	return 0;

}
