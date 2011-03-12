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
	assert(matrix_alloc(&matr,10,10)==0);
	assert(matr!=NULL);
	assert(matr->l =10);
	assert(matr->c=10);
	matrix_free(matr);
	assert(matrix_alloc(&matr,3,3)==0);
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

	assert(matrix_alloc(&matr,100,100)==0);
	assert(matr!=NULL);
	matrix_free(matr);
	
	assert(matrix_alloc(&matr,1000,100)==0);
	assert(matr!=NULL);
	assert(matr->l=1000);
	assert(matr->c=100);
	matrix_free(matr);
	
	assert(matrix_alloc(&matr, 3000,3000)==0);
	assert(matr!=NULL);
	matrix_free(matr);
}

void
test_set_get_matrix_elem_at(){
  	matrix *matr;
	mpz_t v,r;
	mpz_init_set_si(v,5);
	mpz_init(r);
	assert(matrix_alloc(&matr, 1,1)==0);
	assert(matr!=NULL);
	/* do we get the correct value back ? */
	assert(matrix_set_elem_at(0,0,matr,v)==0);
    assert(matrix_get_elem_at(r,0,0,matr)==0);
	assert(mpz_cmp(r,v)==0);

	/* out of bound access */
    assert(matrix_get_elem_at(r,1,0,matr)==-1);
    assert(matrix_get_elem_at(r,1,1,matr)==-1);
    assert(matrix_get_elem_at(r,0,1,matr)==-1);
    assert(matrix_get_elem_at(r,5,5,matr)==-1);

	/* free matrix */
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
	assert(matrix_alloc(&matr,3,3)==0);
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
	assert(matrix_alloc(&m1,3,3)==0);
	assert(matrix_alloc(&m2,3,3)==0);
	assert(matrix_cmp(m1,m2)==0);
	assert(matrix_fill(m1, array)==0);
	assert(matrix_fill(m2, array)==0);
	assert(matrix_cmp(m1,m2)==0);
	matrix_set_elem_at(0,0,m1,v);
	assert(matrix_cmp(m2,m1)==-1);
}

void
test_matrix_multiply(){
	matrix *m1, *m2, *result, *expected_result;
	int cells1[6] = {5,3,2,  4,6,-1 };
	int cells2[6] = {10,-2,  4,7,  0,-20};
	int expected_cells[4] = { 62,-29,  64,54};

	/* fimm ùatrices */
	assert(matrix_alloc(&m1 ,2,3)==0);
	assert(matrix_fill(m1, cells1)==0);

	assert(matrix_alloc(&m2 ,3,2)==0);
	assert(matrix_fill(m2, cells2)==0);

	assert(matrix_alloc(&expected_result ,2,2)==0);
	assert(matrix_fill(expected_result, expected_cells)==0);

	/* multiply and validate */
	assert(matrix_multiply(&result, m1,m2)==0);
	/*
	matrix_print(result); 
	*/
	assert(matrix_cmp(result,expected_result)==0);

}


int 
main(){
  	test_create_matrix();
	test_set_get_matrix_elem_at();
	test_fill_matrix();
	test_equals_matrix();
	test_matrix_multiply();
	printf("All matrix tests Succeeded\n");
	return 0;
}
