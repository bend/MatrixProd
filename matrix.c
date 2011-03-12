#include "matrix.h"

int
matrix_alloc(matrix ** matr,unsigned int l, unsigned int c){
	unsigned int i;
  	*matr = malloc(sizeof(matrix));				/* Allocate memory for the structure */
	if(*matr == NULL){							/* Check if malloc succeeded	   	 */
	  	perror("malloc error");					/* If not print error			     */
		return -1;
	}
	(*matr)->matrix = malloc(sizeof(mpz_t*)*l);		/* Allocate memory for columns of the matrix*/
	if((*matr)->matrix == NULL){
	  	perror("malloc error");
		free(matr);
		return -1;
	}
	
	for(i=0; i<l; i++){
		(*matr)->matrix[i] = malloc(sizeof(mpz_t)*c);
		if((*matr)->matrix[i] == NULL){
		  	perror("malloc error");
			/*TODO free the other cells allocated ? */
			free(*matr);
			return -1;
		}
	}
	(*matr)->l = l;
	(*matr)->c = c;
	return 0;
}

int
matrix_free(matrix* matr){
  	free(matr);
	return 1;
}

int 
matrix_get_elem_at(mpz_t result, unsigned int l, unsigned int c, matrix* matr){
	if ( matr->l-1 < l || matr->c-1 < c) {
		return -1;
	}
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
matrix_fill_line(matrix* matr, int line, int from[]){
	mpz_t v;
	unsigned int i;
	if(matr->c != sizeof(from)/sizeof(int))
		return -1;
	mpz_init(v);
	for(i=0; i<matr->c; i++){
		mpz_set_si(v,from[i]);
		matrix_set_elem_at(line,i,matr,v);
	}
	return 0;
}

int
matrix_cmp(matrix* m1, matrix* m2){
  	unsigned int i,j;
	mpz_t v, v2;
	mpz_init(v);
	mpz_init(v2);
  	if(m1->l != m2->l || m1->c != m2->c)
	  	return -1;
	for(i=0; i<m1->l; i++){
	  	for(j=0; j<m1->c; j++){
			matrix_get_elem_at(v,i,j,m1);
			matrix_get_elem_at(v2,i,j,m2);
		  	if (mpz_cmp(v,v2)!=0)
			  	return -1;
		}
	}
	return 0;
}

int 
matrix_multiply(matrix** result, matrix* m1, matrix* m2){
	unsigned int i,j;
	if ( m1->c!=m2->l || m1->l!=m2->c )
		return -1;
	if (matrix_alloc(result, m1->l, m2->c)==-1)
		return -1;
	for (i=0; i<m1->l; i++){
		for (j=0; j<m2->c; j++){
			/*printf("will compute result cell (%i,%i)\n", i, j);*/
			if (matrix_compute_cell(*result, i, j, m1, m2)==-1)
				return -1;
		}
	}
	/*printf("finished computation\n");*/
	return 0;
}

int
matrix_compute_cell(matrix* res, unsigned int l, unsigned int c, matrix *m1, matrix* m2){
	unsigned int j;
	mpz_t result, c1, c2;
	mpz_init_set_si(result,0);
	mpz_init(c1);
	mpz_init(c2);
	for(j=0; j<m1->c; j++) {
		/*printf("multiplying cell m1(%i,%i) and m2(%i,%i)\n", l, j,j,c);*/
		matrix_get_elem_at(c1,l,j,m1);
		matrix_get_elem_at(c2,j,c,m2);
		mpz_addmul(result,c1,c2);
	}
	/*printf("will set result(%i,%i)\n",l,c);*/
	matrix_set_elem_at(l,c,res, result);
	/*printf("has set result(%i,%i)\n",l,c);*/
	return 0;
}

void
matrix_print(matrix *m){
	unsigned int i, j;
	mpz_t v;
	mpz_init(v);
	printf("********************************************************************************\n");
	printf("Lines:\t %i\n", m->l);
	printf("Cols:\t %i\n", m->c);
	printf("Matrix::\n");

	for (i=0; i<m->l; i++){
		for(j=0; j<m->c;j++){
			matrix_get_elem_at(v,i,j,m);
			printf("\t%ld", mpz_get_si(v)); 
		}
		printf("\n");
	}
	printf("********************************************************************************\n");

}



