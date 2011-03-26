#include "multiplier.h"



int
multiplier_start(unsigned int nb_threads, char* path_to_input_file, char* path_to_output_file){
	state *s;
	producer *p;
	/*pthread_t *producer_thread;
	*/pthread_t consumer_threads[nb_threads];
	multiplier_init(&s,&p, path_to_input_file);
	/*multiplier_create_producer(p, producer_thread);
	*/multiplier_create_consumers(nb_threads-1, consumer_threads,s);
	matrix_print(s->ll->head->next->matr);
	printf("%s",path_to_output_file);
	printf("%s",path_to_input_file);
	printf("%d",nb_threads);
	return 0;

}


int 
multiplier_init(state **s, producer **p, char* input_file){
	if(state_alloc(s)==-1)
		return -1;
	if(producer_alloc(input_file, *s, p)==-1)
		return -1;
	return 0;
}

int
multiplier_create_producer(producer* p, pthread_t *thread){
	if(producer_thread_start(p,&thread)==-1)
		return -1;
	return 0;
}

int
multiplier_create_consumers(unsigned int nb_threads, pthread_t *threads, state *s){
	if(consumer_threads_start(nb_threads, threads, s)==-1)
		return -1;
	return 0;
}

