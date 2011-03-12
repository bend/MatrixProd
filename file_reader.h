#include <stdio.h>

#include "matrix.h"
/*
 * Opens the file in 'ro'
 * @param f: the file descriptor
 * @param path: the path to the file
 * @return the file descriptor
 */
FILE*
file_open(FILE* f, char* path);

/*
 * Closes the file
 * @param f: the file descriptor
 * @return : 0 if success, EOF otherwise
 */
int
file_close(FILE* f);

/*
 * Reads the size of the matrix, the size must be lxc
 * @param f; the file descriptor
 * @param l : the length read
 * @param c : the rows read
 * @return 0 if succes, -1 otherwise
 */
int
file_read_matrix_size(FILE* f, unsigned int *l, unsigned int *c);

/*
 * Reads a whole the line of the matrix, the number of numbers per line must be equal to size
 * @param f: the file descriptor
 * @param tab : the tab that will be filled with numbers
 * @param size: the number of columns of the matrix
 */
int
file_read_line(FILE* f, int tab[], unsigned int size);

int
file_read_matrix(FILE* f, matrix* matr, unsigned int l, unsigned int c);