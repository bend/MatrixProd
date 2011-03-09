#include <assert.h>
#include <stdio.h>

#include "../matrix.h"

void
test_create_matrix(){
	matrix *matr;
	matr = create_matrix(10,10);
	assert(matr!=NULL);
	assert(matr->n =10);
	assert(matr->m=10);
	free_matrix(matr);
	
	matr = create_matrix(100,100);
	assert(matr!=NULL);
	free_matrix(matr);
	
	matr = create_matrix(1000,100);
	assert(matr!=NULL);
	assert(matr->n=1000);
	assert(matr->m=100);
	free_matrix(matr);

	
	matr = create_matrix(3000,3000);
	assert(matr!=NULL);
	free_matrix(matr);
}

void
test_set_matrix_elem_at(){
  	matrix *matr;
	matr = create_matrix(1,1);
	assert(matr!=NULL);
	assert(set_matrix_elem_at(0,0,matr,5)==0);
	assert(get_matrix_elem_at(0,0,matr)==5);
	free_matrix(matr);
}


int main(){
  	//test_create_matrix();
	test_set_matrix_elem_at();
	printf("All tests Succeded\n");
}

