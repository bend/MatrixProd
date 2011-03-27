#include "multiplier.h"
#include <unistd.h>


int
multiplier_start(unsigned int nb_threads, char* path_to_input_file, char* path_to_output_file){
	state *s;
	unsigned int i;
	producer *p;
	pthread_t *producer_thread;
	pthread_t consumer_threads[nb_threads-1];
	void* status[nb_threads];
	if(multiplier_init(&s,&p, path_to_input_file)==-1){
		return -1;
	}
	if(multiplier_create_producer(p, &producer_thread)==-1){
		return -1;
	}
	if(multiplier_create_consumers(nb_threads-1, consumer_threads,s)==-1){
		return -1;
	}
	/* Join the threads and put the status code in a array*/
	if(pthread_join(*producer_thread,&status[0])==-1){
		return -1;
	}
	for(i=0; i<nb_threads-1; i++){
		if(pthread_join(consumer_threads[i],&status[i+1])==-1){
			return -1;
		}
	}
	/* Check the return status of the threads */
	for(i=0; i<nb_threads; i++)
		/* If thread failed  */
		if(*(int*)status[i]== -1)
			return -1;
	
	/* Write result to the output file */
	if(multiplier_write_result(s->ll->head->next->matr,path_to_output_file) == -1)
		return -1;
	
	/*FIXME: add cleanup code */

	state_free(s);
	return 0;

}

int
multiplier_write_result(matrix* matr, char* output_file){
	FILE *f;
	if(file_wopen(&f,output_file)==-1)
		return -1;
	if(file_write_matrix(f,matr)==-1)
		return -1;
	return 0;
}


int 
multiplier_init(state **s, producer **p, char* input_file){
	if(state_alloc(s)==-1)
		return -1;
	if(producer_alloc(input_file, *s, p)==-1){
		state_free(*s);
		return -1;
	}
	return 0;
}

int
multiplier_create_producer(producer* p, pthread_t **thread){
	if(producer_thread_start(p,thread)==-1)
		return -1;
	return 0;
}

int
multiplier_create_consumers(unsigned int nb_threads, pthread_t *threads, state *s){
	if(consumer_threads_start(nb_threads, threads, s)==-1)
		return -1;
	return 0;
}

