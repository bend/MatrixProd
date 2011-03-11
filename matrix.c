#include "matrix.h"

matrix*
matrix_alloc(unsigned int l, unsigned int c){
	unsigned int i;
	matrix *matr;

  	matr = malloc(sizeof(matrix));				/* Allocate memory for the structure */
	if(matr == NULL){							/* Check if malloc succeeded	   	 */
	  	perror("malloc error");					/* If not print error			     */
		exit(-1);
	}
	matr->matrix = malloc(sizeof(mpz_t*)*l);		/* Allocate memory for columns of the matrix*/
	if(matr->matrix == NULL){
	  	perror("malloc error");
		free(matr);
		exit(-1);
	}
	
	for(i=0; i<l; i++){
		matr->matrix[i] = malloc(sizeof(mpz_t)*c);
		if(matr->matrix[i] == NULL){
		  	perror("malloc error");
			/*TODO free the other cells allocated ? */
			free(matr);
			exit(-1);
		}
	}
	matr->l = l;
	matr->c = c;
	return matr;
}

int
matrix_free(matrix* matr){
  	free(matr);
	return 1;
}

int 
matrix_get_elem_at(mpz_t result, unsigned int l, unsigned int c, matrix* matr){
	mpz_set(result,matr->matrix[l][c]);
	return 0;
}

int
matrix_set_elem_at(unsigned int l, unsigned int c, matrix* matr, mpz_t val){
	if(matr == NULL || matr->matrix == NULL)
	  	return -1;
  	mpz_set(matr->matrix[l][c],val);
	return 0;
}

int
matrix_fill(matrix* matr, int from[]){
	unsigned int i, j,l;
	mpz_t v;
	l=0;
	mpz_init(v);
	for(i=0; i<matr->l; i++)
	  	for(j=0; j<matr->c; j++){
			mpz_set_si(v,from[l]);
			matrix_set_elem_at(i,j,matr,v);
			l++;
		}
	return 0;
}

int
matrix_equals(matrix* m1, matrix* m2){
  	unsigned int i,j;
	mpz_t v, v2;
	mpz_init(v);
	mpz_init(v2);
  	if(m1->l != m2->l || m1->c != m2->c)
	  	return -1;
	for(i=0; i<m1->l; i++)
	  	for(j=0; j<m1->c; j++)
			matrix_get_elem_at(v,i,j,m1);
			matrix_get_elem_at(v2,i,j,m2);
		  	if (mpz_cmp(v,v2)!=0)
			  	return -1;
	return 0;
}

int
matrix_compute_cell(unsigned int l, unsigned int c, matrix *m1, matrix* m2, matrix* res){
  	return -1;
}



