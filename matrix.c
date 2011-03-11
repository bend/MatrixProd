#include "matrix.h"

matrix*
matrix_alloc(unsigned int n, unsigned int m){
	unsigned int i;
	matrix *matr;

  	matr = malloc(sizeof(matrix));				/* Allocate memory for the structure */
	if(matr == NULL){							/* Check if malloc succeeded	   	 */
	  	perror("malloc error");					/* If not print error			     */
		exit(-1);
	}
	matr->matrix = malloc(sizeof(int*)*n);		/* Allocate memory for columns of the matrix*/
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
matrix_free(matrix* matr){
  	free(matr);
	return 1;
}

int
matrix_get_elem_at(unsigned int n, unsigned int m, matrix* matr){
  	return matr->matrix[n][m];
}

int
matrix_set_elem_at(unsigned int n, unsigned int m, matrix* matr, int val){
	if(matr == NULL || matr->matrix == NULL)
	  	return -1;
  	matr->matrix[n][m] = val;
	return 0;
}

int
matrix_fill(matrix* matr, int from[]){
	unsigned int i, j,l;
	l=0;
	for(i=0; i<matr->n; i++)
	  	for(j=0; j<matr->m; j++){
			matrix_set_elem_at(i,j,matr,from[l]);
			l++;
		}
	return 0;
}

int
matrix_equals(matrix* m1, matrix* m2){
  	unsigned int i,j;
  	if(m1->n != m2->n || m1->m != m2->m)
	  	return -1;
	for(i=0; i<m1->n; i++)
	  	for(j=0; j<m1->m; j++)
		  	if(matrix_get_elem_at(i,j,m1) != matrix_get_elem_at(i,j,m2))
			  	return -1;
	return 0;
}

int
matrix_compute_cell(unsigned int l, unsigned int c, matrix *m1, matrix* m2, matrix* res){
  	return -1;
}



