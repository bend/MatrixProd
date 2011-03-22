#include "../producer.h"
#include "../state.h"
#include "../matrix.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <pthread.h>

#define PATH "test_files/gen.txt"

void
test_producer_alloc(){
	producer *p;
	state *s;
	assert(state_alloc(&s)==0);
	assert(producer_alloc(PATH,s,&p)==0);
	assert(p->f!=NULL);
}

void*
producer_thread(void* arg){
	producer *p;
	state *s;
	s =(state*)arg;
	assert(producer_alloc(PATH,s,&p)==0);
	assert(p->f!=NULL);
	assert(producer_start(p)==0);
	return NULL;
}

void test_producer_start(){
	state *s;
	pthread_t *t;
	matrix *mat;
	assert(state_alloc(&s) == 0);
	pthread_create(t,NULL,producer_thread,(void*)s);
	while(s->producer_finished==false ){
		sem_wait(s->consumer_allowed_mutex);
	 	linked_list_remove_first(s->ll, &mat);
		matrix_print(mat);
		fflush(stdout);
		sem_post(s->can_produce_sem);
	}
	pthread_join(*t,NULL);
}



int
main(){
	test_producer_alloc();
	test_producer_start();
	printf("All producer tests succeded\n");
	return EXIT_SUCCESS;
}
