#ifndef __PRODUCER_H__
#define __PRODUCER_H__

#include <pthread.h>

#include "file_reader.h"
#include "linked_list.h"
#include "matrix.h"
#include "node.h"
#include "state.h"

typedef struct producer producer;

struct producer{
	FILE* f;
	state* s;
};

/*
 * Initialize the producer: opens the file, initialize the producer descriptor
 * @param filename: the path to the matrix file
 * @param s: a pointer to the state descriptor
 * @param p: a pointer to the pointer to the  producer descriptor (not initialized) 
 * @return : 0 if success, -1 otherwise
 */
int
producer_alloc(char* filename,state* s,producer** p);

/*
 * Starts the producer. The producer in NOT created in a thread.
 * @param p: a pointer to the producer desciptor
 * @return 0 or 2 if success, -1 otherwise
 */
int
producer_start(producer* p);

/*
 * function called by pthread_create.
 * DO NOT USE ELSEWHERE
 * @param arg: a pointer to the param descriptor
 * @return : void, but a status code is set to 0 or 2 in pthread_exit if success and to -1 othrewise, and can be retrieved with pthread_join
 * DO NOT FORGET TO FREE THE STATUS CODE AFTER RETRIEVING
 *
 */
void*
producer_thread_init(void* arg);

/*
 * Starts the producer in a thread
 * @param p: a pointer to the producer descriptor
 * @param thread: a pointer to the pointer of the thread
 * This function does not call pthread_join function. This function may be called in the main function
 * @return 0 or 2 if success, -1 otherwise
 */
int
producer_thread_start(producer *p, pthread_t** thread);

/*
 * Free the producer struct
 * @param p: pointer to producer
 */
void
producer_free(producer *p);


#endif
