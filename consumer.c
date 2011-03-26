#include "consumer.h"

/* This is the function doing the work of one consumer
 * @param state : current state
 * @return: 0 if success, -1 otherwise
 */ 
int consumer_start(state * state){
	node *node1, *node2;
	matrix *result;

#ifdef DEBUG
	printf("%u: Starting consumer\n",(unsigned int)pthread_self());
#endif

	/* Loop as long as producer active and list longer than one matrix node */
	while (state->producer_finished!=true || state->ll->head->next->next->t!=tail) {
#ifdef DEBUG
			printf("%u: In main consumer loop: consumer not finished or list longer than one element\n",(unsigned int)pthread_self());
			printf("%u: In main consumer loop: producer_finished = %d compared to true %d \n",(unsigned int)pthread_self(), state->producer_finished, true );
			printf("%u: In main consumer loop: second node type = %u, compared to tail: %u\n",(unsigned int)pthread_self(), state->ll->head->next->next->t, tail);
#endif
		/* consumer_search_adjacent_and_mark uses a mutex to get exclusive access
		 * to the state's linked list.
		 */
		/* try to find matrices to multiply as long as producer active and list
		 * has more than one matrix node */
		/* FIXME: check that second test is ok when list empty */
		while (!consumer_search_adjacent_and_mark(state, &node1, &node2) &&  state->ll->head->next->next->t!=tail){
#ifdef DEBUG
			printf("%u: will wait on consumer_allowed because no adjacent matrices found and list not empty\n",(unsigned int)pthread_self());
			fflush(stdout);
#endif
			sem_wait(state->consumer_allowed_mutex);
#ifdef DEBUG
			printf("%u: Consumer was allowed\n",(unsigned int)pthread_self());
			fflush(stdout);
#endif
		}
#ifdef DEBUG
		printf("%u: Consumer found adjacent matrices or list finished\n",(unsigned int)pthread_self());
#endif

		/* if the linked list has more than one matrix node, it means we
		 * reserved 2 instances, otherwise the computation is finished and we
		 * rwqill get out of the while loop too.
		 * */
		if (state->ll->head->next->next->t!=tail) {
			/* compute the multiplication of m1 and m2 */
#ifdef DEBUG			
			printf("%u: will call multiply on these matrices\n",(unsigned int)pthread_self());
			matrix_print(node1->matr);
			printf("-------------------------------------\n");
			matrix_print(node2->matr);
#endif
			if (matrix_multiply(&result, node1->matr, node2->matr)==-1){
				perror("multiplication failed!\n");
				/*FIXME: noeed some cleanup here */
				return -1;
			}
#ifdef DEBUG
	printf("%u: done multiplying 2 matrices in thread, will put result back in list\n",(unsigned int)pthread_self());
	matrix_print(result);
#endif

			/*************************************************************************
			 *                 LOCK ACCESS TO LIST
			 ************************************************************************/
			/* put result back in list */
#ifdef DEBUG
			printf("%u: sleep and will wait for list access to put result back\n",(unsigned int)pthread_self());
			sleep(rand()%20);
			printf("%u: done sleep before putting result back\n",(unsigned int)pthread_self());
#endif
			sem_wait(state->list_access_mutex);
#ifdef DEBUG
			printf("%u: got list access to put result back\n",(unsigned int)pthread_self());
#endif

			matrix_free(node1->matr);
			node1->matr=result;
			node_set_next(node1, node2->next);
			node1->t=unreserved;
			/* if previous or next matrix is unreserved, notify a consumer that he can take a look at the list */
			if (node1->prev->t==unreserved || node1->next->t==unreserved){
#ifdef DEBUG
				printf("%u: Posting consumer_allowed as adjacent matrix of result matrix is free\n",(unsigned int)pthread_self());
#endif
				sem_post(state->consumer_allowed_mutex);
			}
#ifdef DEBUG
			printf("%u: Freeing list access\n",(unsigned int)pthread_self());
			fflush(stdout);
#endif
			sem_post(state->list_access_mutex);
			/*************************************************************************
			 *                 UNLOCK ACCESS TO LIST
			 ************************************************************************/

			node_free(node2);
			sem_post(state->can_produce_sem);
		}
#ifdef DEBUG
		printf("%u: End of loop, will check again list size and producer finished \n",(unsigned int)pthread_self());
		fflush(stdout);
#endif
	}

#ifdef DEBUG
	
	printf("%u: Thread finished successfully, will return 0\n",(unsigned int)pthread_self(),(unsigned int)pthread_self());
#endif
	/* allow consumers to unblock those waiting */
	sem_post(state->consumer_allowed_mutex);
	return 0;
}

bool
consumer_search_adjacent_and_mark(state* state, node** n1, node** n2){
	bool found=false;
	node* current_node;
#ifdef DEBUG
	printf("%u: will wait list access to get adjacent matrices\n",(unsigned int)pthread_self());
#endif
	sem_wait(state->list_access_mutex);
	/* iterate over list starting at first matrix node */
	current_node=state->ll->head->next;
	while(current_node->next->t!=tail && found==false){
#ifdef DEBUG
		printf("%u: Adjacent matrices search: while loop;\n",(unsigned int)pthread_self());
#endif
		if (current_node->t==unreserved && current_node->next->t==unreserved) {
			/* two adjacent unreserved nodes found!
			 *  take matrices and mark nodes as reserved */
			*n1=current_node;
			current_node->t=reserved;
			*n2=current_node->next;
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

void
* consumer_thread(void * params) {
	int * retval;
	retval=malloc(sizeof(int));
#ifdef DEBUG
	printf("%u: will sleep\n",(unsigned int)pthread_self());
	fflush(stdout);
	sleep(rand()%20);
	printf("%u: done sleep\n",(unsigned int)pthread_self());
	fflush(stdout);
	printf("%u: Begin of consumer_thread\n",(unsigned int)pthread_self());
	fflush(stdout);
#endif
	if (consumer_start( (state *) params )==0){
		*retval=0;
		pthread_exit( (void *) retval);
	}
	else {
		*retval=-1;
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
