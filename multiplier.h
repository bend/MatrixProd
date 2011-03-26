#ifndef __MULTIPLIER_H__
#define __MULTIPLIER_H__

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

#include "consumer.h"
#include "producer.h"
#include "file_reader.h"
#include "file_writer.h"
#include "matrix.h"
#include "state.h"

/*
 * Starts the multiplier with nb_threads threads: nb_threads-1 consumer and 1 producer
 * @param nb_threads: the number of threads to be used including the producers and the consumers. The main threads is not included
 * @param path_to_input_file the path to the file contining the matrices
 * @param path_to_output_file the path to the output file
 * @return O if success, -1 otherwise
 */
int
multiplier_start(unsigned int nb_threads, char* path_to_input_file, char* path_to_output_file);

/*
 * Initializes the producer descriptor, the state descriptor
 * @param 
 *
 */
int
multiplier_init(state **s, producer **p, char* input_file);

/*
 * Creates the producer thread
 * @param : TODO
 */
int 
multiplier_create_producer(producer* p, pthread_t **thread);

/*
 * Creates the consumers threads
 * @param: TODO
 */
int
multiplier_create_consumers(unsigned int nb_threads, pthread_t *threads, state *s);

#endif
