#include <assert.h>
#include <stdio.h>

#include "../matrix.h"
/*
void
test_create_matrix(){
	matrix *matr;
	assert(create_matrix(10,10, matr)==0);
	free_matrix(matr);
	
	assert(create_matrix(100,100, matr)==0);
	free_matrix(matr);
	
	assert(create_matrix(1000,1000, matr)==0);
	free_matrix(matr);
	
	assert(create_matrix(3000,3000, matr)==0);
	free_matrix(matr);
}
*/
void
test_set_matrix_elem_at(){
  	matrix *matr;
	matr = create_matrix(1,1);
	if(matr == NULL)
	  printf("eror");
	assert(set_matrix_elem_at(0,0,matr,5)==0);
	assert(get_matrix_elem_at(0,0,matr)==5);

	free_matrix(matr);
}


int main(){
  	//test_create_matrix();
	test_set_matrix_elem_at();
	printf("All tests Succeded\n");
}

