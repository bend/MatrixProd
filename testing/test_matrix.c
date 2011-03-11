#include <assert.h>
#include <stdio.h>

#include "../matrix.h"
#include "../node.h"
#include "../linked_list.h"

void
test_create_matrix(){
	matrix *matr;
	int i,j;
	mpz_t v;
	mpz_init_set_si(v,0);
	matr = matrix_alloc(10,10);
	assert(matr!=NULL);
	assert(matr->l =10);
	assert(matr->c=10);
	matrix_free(matr);
	matr = matrix_alloc(3,3);
	/* test allocation */
	for(i=0; i<3;i++){
	    for(j=0; j<3; j++){
		    mpz_set_si(v,1);
		    mpz_set(matr->matrix[i][j], v) ;
		}
	}
	for(i=0; i<3; i++)
	  	for(j=0; j<3; j++)
		  	assert(mpz_cmp(matr->matrix[i][j],v)==0);

	matr = matrix_alloc(100,100);
	assert(matr!=NULL);
	matrix_free(matr);
	
	matr = matrix_alloc(1000,100);
	assert(matr!=NULL);
	assert(matr->l=1000);
	assert(matr->c=100);
	matrix_free(matr);
	
	matr = matrix_alloc(3000,3000);
	assert(matr!=NULL);
	matrix_free(matr);
}

void
test_set_get_matrix_elem_at(){
  	matrix *matr;
	mpz_t v,r;
	mpz_init_set_si(v,5);
	mpz_init(r);
	matr = matrix_alloc(1,1);
	assert(matr!=NULL);
	assert(matrix_set_elem_at(0,0,matr,v)==0);
    matrix_get_elem_at(r,0,0,matr);
	assert(mpz_cmp(r,v)==0);
	matrix_free(matr);
}

void
test_fill_matrix(){
	int i, j,k;
	mpz_t v,r;
  	matrix *matr;
	mpz_init(v);
	mpz_init(r);
	int  array[9]={1,2,3,4,5,6,7,8,9};
	k=0;
	matr = matrix_alloc(3,3);
	assert(matrix_fill(matr, array)==0);
	for(i=0; i<3; i++)
	  	for(j=0; j<3; j++){
			mpz_set_si(v,array[k]);
			matrix_get_elem_at(r,i,j,matr);
		  	assert(mpz_cmp(r,v)==0);
			k++;
		}
}

void
test_equals_matrix(){
  	matrix *m1,*m2;
	mpz_t v;
	mpz_init_set_si(v,-1);
	int array[10]={1,2,3,4,5,6,7,8,9,0};
	m1 = matrix_alloc(3,3);
	m2 = matrix_alloc(3,3);
	assert(matrix_equals(m1,m2)==0);
	assert(matrix_fill(m1, array)==0);
	assert(matrix_fill(m2, array)==0);
	assert(matrix_equals(m1,m2)==0);
	matrix_set_elem_at(0,0,m1,v);
	assert(matrix_equals(m2,m1)==-1);
}

int 
main(){
  	test_create_matrix();
	test_set_get_matrix_elem_at();
	test_fill_matrix();
	test_equals_matrix();
	printf("All matrix tests Succeeded\n");
	return 0;
}
