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

#define RATIO 3
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
 * Writes the matrix to the output file
 * @param matr: a pointer to the matrix
 * @param output_file : the output file
 */
int
multiplier_write_result(matrix* matr, char* output_file);

/*
 * Initializes the producer descriptor, the state descriptor
 * @param s: a pointer to the pointer of the state descriptor
 * @param p: a pointer to the pointer of the producer descriptor
 * @return 0 if success, -1 otherwise
 */
int
multiplier_init(state** s, producer** p, char* input_file, unsigned int nb_threads);

/*
 * Creates the producer thread
 * @param p: a pointer to the pointer of the producer descriptor
 * @param thread : a pointer to the pointer of the thread descriptor
 * @return 0 if success, -1 otherwise
 */
int
multiplier_create_producer(producer* p, pthread_t** thread);

/*
 * Creates the consumers threads
 * @param nb_threads: the number of threads
 * @param threads: a pointer to the array of threads
 * @param s: a pointer to the state
 * @return 0 if success, -1 otherwise
 */
int
multiplier_create_consumers(unsigned int nb_threads, pthread_t* threads, state* s);

#endif
