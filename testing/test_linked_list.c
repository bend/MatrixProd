#include <assert.h>
#include <stdio.h>

#include "../matrix.h"
#include "../node.h"
#include "../linked_list.h"
void
test_node_create(){
  node* n;
  n = node_alloc();
  assert(n!=NULL);
}

void 
test_node_set_get(){
	node *n1,*n2;
	n1=node_alloc();
	n2=node_alloc();
	assert(node_set_next(n1,n2)==0);
	assert(node_get_next(n1)==n2);
	assert(node_set_next(n2,n1)==0);
	assert(node_get_prev(n1)==n2);
	assert(node_get_next(n2)==n1);
}

void
test_node_set_elem(){
  	node *n1;
	matrix *matr;
	n1 = node_alloc();
	matr = matrix_alloc(1,1);
	matrix_set_elem_at(0,0,matr,5);
	assert(node_set_elem(n1,matr)==0);
	assert(n1->matr == matr);
}

void test_linked_list(){
	linked_list *ll;
	matrix *m,*m1,*m2;
	ll = linked_list_alloc();
	m=matrix_alloc(5,5);
	m1=matrix_alloc(6,6);
	m2=matrix_alloc(7,7);
	assert(matrix_set_elem_at(0,0,m,1)==0);
	assert(matrix_set_elem_at(0,0,m1,2)==0);
	assert(matrix_set_elem_at(0,0,m2,3)==0);
	
	assert(linked_list_add_first(ll, m)==0);
	assert(linked_list_add_first(ll, m1)==0);
	assert(linked_list_add_last(ll, m2)==0);
	
	assert(matrix_get_elem_at(0,0,linked_list_get_first(ll))==2);
	assert(matrix_get_elem_at(0,0,linked_list_remove_first(ll))==2);
	              
	assert(matrix_get_elem_at(0,0,linked_list_get_first(ll))==1);
	assert(matrix_get_elem_at(0,0,linked_list_remove_first(ll))==1);
                  
	assert(matrix_get_elem_at(0,0,linked_list_get_first(ll))==3);
	assert(matrix_get_elem_at(0,0,linked_list_remove_first(ll))==3);
}


int 
main(){
	test_node_set_get();
	test_node_set_elem();
	test_linked_list();
	printf("All linked list tests Succeeded\n");
	return 0;
}

