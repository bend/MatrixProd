#include "../producer.h"
#include "../state.h"
#include "../matrix.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <pthread.h>

#define PATH "test_files/test4.txt"

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
	matrix *mat1,*mat2,*mat3;
	int m1[] = {1,
				1};
	int m2[] = {2,2,
				2,2};
	int m3[] = {1,2,3,
				1,2,3,
				1,2,3};
	assert(matrix_alloc(&mat1,2,1)==0);
	assert(matrix_alloc(&mat2,2,2)==0);
	assert(matrix_alloc(&mat3,3,3)==0);
	assert(matrix_fill(mat1,m1)==0);
	assert(matrix_fill(mat2,m2)==0);
	assert(matrix_fill(mat3,m3)==0);
	assert(state_alloc(&s) == 0);
	pthread_create(t,NULL,producer_thread,(void*)s);
	while(s->producer_finished==false ){
		sem_wait(s->consumer_allowed_mutex);
	 	
		assert(linked_list_remove_first(s->ll, &mat)==0);
		assert(matrix_cmp(mat,mat1)==0);
		sem_post(s->can_produce_sem);
	 	
		sem_wait(s->consumer_allowed_mutex);
		assert(linked_list_remove_first(s->ll, &mat)==0);
		assert(matrix_cmp(mat,mat2)==0);
		sem_post(s->can_produce_sem);
	 	
		sem_wait(s->consumer_allowed_mutex);
		assert(linked_list_remove_first(s->ll, &mat)==0);
		assert(matrix_cmp(mat,mat3)==0);
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
