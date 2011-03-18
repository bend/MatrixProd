#include "state.h"




int
state_alloc(state** s){
	*s = malloc(sizeof(state));
	if(*s == NULL){
		perror("malloc error");
		return -1;
	}
	sem_unlink(LIST_ACCESS_MUTEX);
	(*s)->list_access_mutex = sem_open(LIST_ACCESS_MUTEX,O_CREAT|O_EXCL,0666,1);
	if((*s)->list_access_mutex == NULL){
		perror("mutex error");
		return -1;
	}
	sem_unlink(CONS_MUTEX);
	(*s)->consumer_allowed_mutex = sem_open(CONS_MUTEX, O_CREAT|O_EXCL,0666,0);
	if((*s)->consumer_allowed_mutex == NULL){
		perror("mutex error");
		return -1;
	}
	sem_unlink(CAN_PRODUCE_SEM);
	(*s)->can_produce_sem = sem_open(CAN_PRODUCE_SEM, O_CREAT|O_EXCL,0666,BUFFER_SIZE);
	if((*s)->can_produce_sem == NULL){
		perror("mutex error");
		return -1;
	}
	linked_list_alloc(&(*s)->ll);
	(*s)->producer_finished = false;
	return 0;
}



void
state_free(){
}
