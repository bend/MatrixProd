#include "state.h"


int
state_alloc(state** s, unsigned int buf_size){
	*s = malloc(sizeof(state));
	if(*s == NULL){
		fprintf(stderr,"malloc error");
		return -1;
	}
	sem_unlink(LIST_ACCESS_MUTEX);
	(*s)->list_access_mutex = sem_open(LIST_ACCESS_MUTEX,O_CREAT|O_EXCL,0666,1);
	if((*s)->list_access_mutex == NULL){
		fprintf(stderr,"mutex error");
		return -1;
	}
	sem_unlink(CONS_MUTEX);
	(*s)->consumer_allowed_mutex = sem_open(CONS_MUTEX, O_CREAT|O_EXCL,0666,0);
	if((*s)->consumer_allowed_mutex == NULL){
		fprintf(stderr,"mutex error");
		return -1;
	}
	sem_unlink(CAN_PRODUCE_SEM);
	(*s)->can_produce_sem = sem_open(CAN_PRODUCE_SEM, O_CREAT|O_EXCL,0666,buf_size);
	if((*s)->can_produce_sem == NULL){
		fprintf(stderr,"mutex error");
		return -1;
	}
	linked_list_alloc(&(*s)->ll);
	(*s)->producer_finished = false;
	(*s)->exit_on_error = 0;
	return 0;
}



void
state_free(state *s){
	/* close and unlink semaphores */
	sem_close(s->list_access_mutex);
	sem_unlink(LIST_ACCESS_MUTEX);

	sem_close(s->consumer_allowed_mutex);
	sem_unlink(CONS_MUTEX);

	sem_close(s->can_produce_sem);
	sem_unlink(CAN_PRODUCE_SEM);

	/* free all linked list */
	linked_list_free(s->ll);

	free(s);
}
