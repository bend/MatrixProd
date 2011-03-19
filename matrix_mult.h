#ifndef __MATRIX_MULT_H__
#define __MATRIX_MULT_H__

#include "matrix.h"
#include "file_reader.h"
#include "linked_list.h"
#include "node.h"
#include "producer.h"
#include "consumer.h"
#include "state.h"



/*
 * Initialises the state structure at the start of the program.
 * @param s: state to initialise
 * @param threads: total number of threads to start
 * @param input: filename from where to read matrices
 * @param output: filename where to write result
 * @return: 0 if successful, -1 otherwise
 */
int
matrix_mult_start(state* s, int threads, char* input, char* output)

/*
 * Initialises the state structure at the start of the program.
 * @param s: state to initialise
 * @return: 0 if successful, -1 otherwise
 */
int
matrix_mult_init(state* s);

/*
 * Starts the producer reading matrices from the input file
 * @param s: state 
 * @return: 0 if successful, -1 otherwise
 */
int
matrix_mult_start_producer(state* s);

/*
 * Starts the producer reading matrices from the input file
 * @param s: state 
 * @param number: number of consumer threads to start
 * @return: 0 if successful, -1 otherwise
 */
int 
matrix_mult_start_consumers(state* s, int number);

/*
 * Writes the result in the ouput file
 * @param s: state 
 * @param output: name of the file where to write the result
 * @return: 0 if successful, -1 otherwise
 */
int 
matrix_mult_write_result(state* s, char* output);



#endif
