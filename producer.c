#include "producer.h"


int
producer_alloc(char* filename,state* s,producer** p){
	*p = malloc(sizeof(producer));
	if(*p == NULL){
		perror("malloc failed");
		return -1;
	}
	if(file_open(&(*p)->f,filename) ==-1)
		return -1;
	(*p)->s = s;
	return 0;
}


int
producer_start(producer* p){
	matrix *matr;
	while(file_read_next_matrix(p->f,&matr) ==0){
		if(sem_wait(p->s->can_produce_sem) ==-1){
			perror("sem wait error");
			return -1;
		}
		if(linked_list_add_last(p->s->ll,matr)==-1)
			return -1;
		if(sem_post(p->s->consumer_allowed_mutex)==-1){
			perror("sem_post error");
			return -1;
		}
	}
	p->s->producer_finished = true;
	return 0;
}
