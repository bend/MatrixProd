#include "producer.h"


int
producer_alloc(char* filename,state* s,producer** p){
	*p = malloc(sizeof(producer));
	if(*p == NULL){
		perror("malloc failed");
		return -1;
	}
	if(file_ropen(&(*p)->f,filename) ==-1)
		return -1;
	(*p)->s = s;
	return 0;
}


int
producer_start(producer* p){
	matrix *matr;
	int r;
	while((r=file_read_next_matrix(p->f,&matr)) == 0){
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
	return r;
}

void*
producer_thread_init(void* arg){
	producer *p;
	int *l;
	int r;
	p=(producer*)arg;
	l = malloc(sizeof(int));
	if(l==NULL){
		perror("failed allocating memory for status code");
		pthread_exit(NULL);
	}
	if((r=producer_start(p))==-1){
		perror("error while executing  producer");
		*l=-1;
		pthread_exit((void*)l);
	}
	*l=r;
	pthread_exit((void*)l);
}

int
producer_thread_start(producer* p,pthread_t** thread){

	if(*thread == NULL){
		perror("Malloc Failed");
		return -1;
	}
	if(pthread_create(*thread,NULL,producer_thread_init,(void*)p)==-1){
		perror("error while creating producer thread");
		return -1;
	}
	return 0;
}
