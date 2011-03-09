#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <stdlib.h>
#include <stdio.h>

struct matrix{
	int **matrix;
	short flag;
	unsigned int n;
	unsigned int m;
};

typedef struct matrix matrix;

/*
 * Creates a matrix of size nxm
 * @param m: the number of lines
 * @param n: the number of columns
 * @return the matrix descriptor
 */
matrix*
create_matrix(unsigned int n, unsigned int m);

/*
 * Frees the matrix
 * @param: a pointer to the matrix descriptor
 * @return 0 if succeeded, -1 otherwise
 */
int
free_matrix(matrix* matr);

/*
 * Returns the value stored at position (n,m) in the matrix
 * @param (n,m): the position of the element
 * @param matr: a pointer to the matrix descriptor
 * @return the value stored at(n,m)
 */
int
get_matrix_elem_at(unsigned int n, unsigned int m, matrix* matr);

/*
 * Adds an element at position (n,m)
 * @param n,m the position where to add the element
 * returns -1 if failed, 0 otherwise
 */
int
set_matrix_elem_at(unsigned int n, unsigned int m, matrix* matr, int val);
#endif 
