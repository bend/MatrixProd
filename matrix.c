#include "matrix.h"

matrix*
create_matrix(unsigned int n, unsigned int m){
	unsigned int i;
	matrix *matr;

  	matr = malloc(sizeof(matrix));				/* Allocate memory for the structure */
	if(matr == NULL){							/* Check if malloc succeeded	   	 */
	  	perror("malloc error");					/* If not print error			     */
		exit(-1);
	}
	matr->matrix = malloc(sizeof(int)*n);		/* Allocate memory for columns of the matrix*/
	if(matr->matrix == NULL){
	  	perror("malloc error");
		free(matr);
		exit(-1);
	}
	
	for(i=0; i<n; i++){
		matr->matrix[i] = malloc(sizeof(int)*m);
		if(matr->matrix[i] == NULL){
		  	perror("malloc error");
			/*TODO free the other cells allocated ? */
			free(matr);
			exit(-1);
		}
	}
	matr->n = n;
	matr->m = m;
	return matr;
}

int
free_matrix(matrix* matr){
  	free(matr);
	return 1;
}

int
get_matrix_elem_at(unsigned int n, unsigned int m, matrix* matr){
  	return matr->matrix[n][m];
}

int
set_matrix_elem_at(unsigned int n, unsigned int m, matrix* matr, int val){
	if(matr == NULL || matr->matrix == NULL)
	  	return -1;
  	matr->matrix[n][m] = val;
	return 0;
}
