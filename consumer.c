#include "consumer.h"

int consumer_start(state * state){
	node *node1, *node2;
	matrix *result;


	/* Loop as long as producer active and list longer than one matrix node */
	while (!state->producer_finished && state->ll->head->next->next->t!=tail) {
		/* consumer_search_adjacent_and_mark uses a mutex to get exclusive access
		 * to the state's linked list.
		 */
		/* try to find matrices to multiply as long as producer active and list
		 * has more than one matrix node */
		while (!consumer_search_adjacent_and_mark(state, &node1, &node2) &&  state->ll->head->next->t!=tail)
				sem_wait(state->consumer_allowed_mutex);

		/* if the linked list has more than one matrix node, it means we
		 * reserved 2 instances, otherwise the computation is finished and we
		 * rwqill get out of the while loop too.
		 * */
		if (state->ll->head->next->t!=tail) {
			/* compute the multiplication of m1 and m2 */
#ifdef DEBUG			
	printf("will call multiply on these matrices\n");
	matrix_print(node1->matr);
	printf("-------------------------------------\n");
	matrix_print(node2->matr);
#endif
			if (matrix_multiply(&result, node1->matr, node2->matr)==-1){
				perror("multiplication failed!\n");
				/*FIXME: noeed some cleanup here */
				exit(1);
			}
#ifdef DEBUG
	printf("done multiplying 2 matrices, will put result back in list\n");
	matrix_print(result);
#endif

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
			if (node1->prev->t==unreserved || node1->next->t==unreserved)
				sem_post(state->consumer_allowed_mutex);
			sem_post(state->list_access_mutex);
			/*************************************************************************
			 *                 UNLOCK ACCESS TO LIST
			 ************************************************************************/

			node_free(node2);
			sem_post(state->can_produce_sem);
		}
	}
	return 1;
}

bool
consumer_search_adjacent_and_mark(state* state, node** n1, node** n2){
	bool found=false;
	node* current_node;
	sem_wait(state->list_access_mutex);
	/* iterate over list starting at first matrix node */
	current_node=state->ll->head->next;
	while(current_node->next->t!=tail && found==false){
		if ( current_node->t==unreserved &&	current_node->next->t==unreserved) {
			/* two adjacent unreserved nodes found!
			 *  take matrices and mark nodes as reserved */
			*n1=current_node;
			current_node->t=reserved;
			*n2=current_node->next;
			current_node->next->t=reserved;
			found=true;  /*exit the while loop */
		}
	}
	sem_post(state->list_access_mutex);
	return found;
}
