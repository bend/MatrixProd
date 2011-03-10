#include <assert.h>
#include <stdio.h>

#include "../matrix.h"
#include "../node.h"
#include "../linked_list.h"
void
test_create_matrix(){
	matrix *matr;
	int i,j;
	matr = create_matrix(10,10);
	assert(matr!=NULL);
	assert(matr->n =10);
	assert(matr->m=10);
	free_matrix(matr);
	matr = create_matrix(3,3);
	for(i=0; i<3;i++)
	  for(j=0; j<3; j++)
		matr->matrix[i][j] = 1;
	for(i=0; i<3; i++)
	  	for(j=0; j<3; j++)
		  	assert(matr->matrix[i][j] =1);

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
test_fill_matrix(){
	int i, j,k;
  	matrix *matr;
	int  array[9]={1,2,3,4,5,6,7,8,9};
	k=0;
	matr = create_matrix(3,3);
	assert(fill_matrix(matr, array)==0);
	for(i=0; i<3; i++)
	  	for(j=0; j<3; j++){
		  	assert(get_matrix_elem_at(i,j,matr)==array[k]);
			k++;
		}
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

void test_linked_list(){
	linked_list *ll;
	matrix *m,*m1,*m2;
	ll = create_linked_list();
	m=create_matrix(5,5);
	m1=create_matrix(6,6);
	m2=create_matrix(7,7);
	assert(set_matrix_elem_at(0,0,m,1)==0);
	assert(set_matrix_elem_at(0,0,m1,2)==0);
	assert(set_matrix_elem_at(0,0,m2,3)==0);
	
	assert(add_first_linked_list(ll, m)==0);
	assert(add_first_linked_list(ll, m1)==0);
	assert(add_last_linked_list(ll, m2)==0);
	
	assert(get_matrix_elem_at(0,0,get_first_linked_list(ll))==2);
	assert(get_matrix_elem_at(0,0,remove_elem_first_linked_list(ll))==2);
	
	assert(get_matrix_elem_at(0,0,get_first_linked_list(ll))==1);
	assert(get_matrix_elem_at(0,0,remove_elem_first_linked_list(ll))==1);

	assert(get_matrix_elem_at(0,0,get_first_linked_list(ll))==3);
	assert(get_matrix_elem_at(0,0,remove_elem_first_linked_list(ll))==3);
}

int 
main(){
  	test_create_matrix();
	test_set_get_matrix_elem_at();
	test_fill_matrix();
	test_node_set_get();
	test_node_set_elem();
	test_linked_list();
	printf("All tests Succeded\n");
}

