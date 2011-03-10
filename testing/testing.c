#include <assert.h>
#include <stdio.h>

#include "../matrix.h"
#include "../node.h"
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
test_set_get_matrix_elem_at(){
  	matrix *matr;
	matr = create_matrix(1,1);
	assert(matr!=NULL);
	assert(set_matrix_elem_at(0,0,matr,5)==0);
	assert(get_matrix_elem_at(0,0,matr)==5);
	free_matrix(matr);
}

void
test_node_create(){
  node* n;
  n = create_node();
  assert(n!=NULL);
}

void 
test_node_set_get(){
	node *n1,*n2;
	n1=create_node();
	n2=create_node();
	assert(set_next_node(n1,n2)==0);
	assert(get_next_node(n1)==n2);
	assert(set_next_node(n2,n1)==0);
	assert(get_next_node(n2)==n1);
}

void
test_node_set_elem(){
  	node *n1;
	matrix *matr;
	matr = create_matrix(1,1);
	set_matrix_elem_at(0,0,matr,5);
	assert(set_elem_node(n1,matr)==0);
	assert(n1->matr == matr);
}



int 
main(){
  	test_create_matrix();
	test_set_get_matrix_elem_at();
	test_node_set_get();
	test_node_set_elem();
	printf("All tests Succeded\n");
}

