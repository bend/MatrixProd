#ifndef __PRODUCER_H__
#define __PRODUCER_H__

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
 * Starts the producer
 * TODO
 */
int
producer_start(producer* p);

/*
 * Stop the producer
 * TODO
 */
int
producer_halt(producer* p);


#endif
