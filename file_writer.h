#ifndef __FILE_WRITER_H__
#define __FILE_WRITER_H__
#include <stdio.h>
#include <gmp.h>

#include "matrix.h"

/*
 * Opens the file in write mode
 * @param f: a pointer to the pointer of the file descriptor uninitialiszed.
 * @param path : the path to the file
 * @return 0 if success, -1 otherwise
 */
int
file_wopen(FILE** f, char* path);

/*
 * writes the matrix size "lxc"
 * @param f: the file descriptor
 * @param l: the number of lines in the matrix
 * @param c: the number of columns in the matrix
 * @return 0 if success, -1 otherwise
 */
int
file_write_matrix_size(FILE* f, unsigned int l, unsigned int c);

/*
 * writes a line of the matrix in the file
 * @param f : the file descriptor
 * @param tab : an array containing the line
 * @param size: the number of columns in the line
 * @return 0 is success, -1 otherwise
 */
int
file_write_line(FILE *f, mpz_t tab[], unsigned int size);

/*
 * writes the whole matrix in the file
 * @param f: the file descriptor
 * @param matr: a pointer to the matrix descriptor
 */
int
file_write_matrix(FILE* f, matrix* matr);

#endif
