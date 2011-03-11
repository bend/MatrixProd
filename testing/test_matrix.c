#include <assert.h>
#include <stdio.h>

#include "../matrix.h"
#include "../node.h"
#include "../linked_list.h"

void
test_create_matrix(){
	matrix *matr;
	int i,j;
	matr = matrix_alloc(10,10);
	assert(matr!=NULL);
	assert(matr->n =10);
	assert(matr->m=10);
	matrix_free(matr);
	matr = matrix_alloc(3,3);
	for(i=0; i<3;i++)
	  for(j=0; j<3; j++)
		matr->matrix[i][j] = 1;
	for(i=0; i<3; i++)
	  	for(j=0; j<3; j++)
		  	assert(matr->matrix[i][j] =1);

	matr = matrix_alloc(100,100);
	assert(matr!=NULL);
	matrix_free(matr);
	
	matr = matrix_alloc(1000,100);
	assert(matr!=NULL);
	assert(matr->n=1000);
	assert(matr->m=100);
	matrix_free(matr);
	
	matr = matrix_alloc(3000,3000);
	assert(matr!=NULL);
	matrix_free(matr);
}

void
test_set_get_matrix_elem_at(){
  	matrix *matr;
	matr = matrix_alloc(1,1);
	assert(matr!=NULL);
	assert(matrix_set_elem_at(0,0,matr,5)==0);
	assert(matrix_get_elem_at(0,0,matr)==5);
	matrix_free(matr);
}

void
test_fill_matrix(){
	int i, j,k;
  	matrix *matr;
	int  array[9]={1,2,3,4,5,6,7,8,9};
	k=0;
	matr = matrix_alloc(3,3);
	assert(matrix_fill(matr, array)==0);
	for(i=0; i<3; i++)
	  	for(j=0; j<3; j++){
		  	assert(matrix_get_elem_at(i,j,matr)==array[k]);
			k++;
		}
}

void
test_equals_matrix(){
  	matrix *m1,*m2;
	int array[10]={1,2,3,4,5,6,7,8,9,0};
	m1 = matrix_alloc(3,3);
	m2 = matrix_alloc(3,3);
	assert(matrix_equals(m1,m2)==0);
	assert(matrix_fill(m1, array)==0);
	assert(matrix_fill(m2, array)==0);
	assert(matrix_equals(m1,m2)==0);
	matrix_set_elem_at(0,0,m1,-1);
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
