#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <stdlib.h>
#include <stdio.h>
#include <gmp.h>

struct matrix{
	mpz_t **matrix;
	short flag;
	unsigned int l;
	unsigned int c;
};

typedef struct matrix matrix;

/*
 * Creates a matrix of size nxm
 * @param m: the number of lines
 * @param n: the number of columns
 * @return the matrix descriptor
 */
matrix*
matrix_alloc(unsigned int l, unsigned int c);

/*
 * Frees the matrix
 * @param: a pointer to the matrix descriptor
 * @return 0 if succeeded, -1 otherwise
 */
int
matrix_free(matrix* matr);

/*
 * Returns the value stored at position (n,m) in the matrix
 * @param (n,m): the position of the element
 * @param matr: a pointer to the matrix descriptor
 * @return -1 if failed, 0 otherwise.
 */
int 
matrix_get_elem_at(mpz_t result, unsigned int l, unsigned int c, matrix* matr);

/*
 * Adds an element at position (n,m)
 * @param n,m the position where to add the element
 * returns -1 if failed, 0 otherwise
 */
int
matrix_set_elem_at(unsigned int l, unsigned int c, matrix* matr, mpz_t val);

/*
 * Fills the matrix with the elements in the tab, 
 * the matrix and the array must have the same number of row and columns
 * @param matr : the matrix descriptor
 * @param from : the 2 dim array
 * @return 0 if success, -1 otherwise
 */
int
matrix_fill(matrix* matr, int from[]);

/*
 * Fills one line of the matrix with the elements in the tab, 
 * the matrix and the array must have the same number of columns
 * @param matr : the matrix descriptor
 * @param line : line number to be filled, starting at 0
 * @param from : the 2 dim array
 * @return 0 if success, -1 otherwise
 */
int
matrix_fill_line(matrix* matr, int line, int from[]);

/*
 * Checks if the two matrices are equal
 * @param m1: the first matrix
 * @param m2: the second matrix
 * @return: 0 if equal, -1 otherwise
 */
int
matrix_equals(matrix* m1, matrix* m2);


/*
 * Mutiplies 2 matrices and puts the resulting matrix in result
 * @param result: the resulting matrix
 * @param m1: the first matrix
 * @param m2: the second matrix
 * @return 0 if success -1 otherwise
 */
int
matrix_multiply(matrix* result, matrix* m1, matrix* m2);

/*
 * Mutiplies the line of the matrix1 by the column of the matrix 2 and puts it in the matrix 3 at position (l,c)
 * @param m1: the first matrix
 * @param m2: the second result
 * @param m3: the result matrix
 * @return 0 if success -1 otherwise
 */
int
matrix_compute_cell(matrix *res,unsigned int l, unsigned int c, matrix* m1, matrix* m2);

/*
 * Prints matrix to standard output
 * @param m: matrix to print
 */
void
matrix_print(matrix *m);
#endif 
