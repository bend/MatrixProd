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
	mpz_t v;
	mpz_init_set_si(v,5);
	n1 = node_alloc();
	assert(matrix_alloc(&matr ,1,1)==0);
	matrix_set_elem_at(0,0,matr,v);
	assert(node_set_elem(n1,matr)==0);
	assert(n1->matr == matr);
}

void test_linked_list(){
	linked_list *ll;
	matrix *m,*m1,*m2;
	mpz_t v1,v2,v3,r1,r2,r3;
	ll = linked_list_alloc();
	mpz_init_set_si(v1,1);
	mpz_init_set_si(v2,2);
	mpz_init_set_si(v3,3);
	mpz_init(r1);
	mpz_init(r2);
	mpz_init(r3);

	assert(matrix_alloc(&m,5,5)==0);
	assert(matrix_alloc(&m1,6,6)==0);
	assert(matrix_alloc(&m2,7,7)==0);
	assert(matrix_set_elem_at(0,0,m,v1)==0);
	assert(matrix_set_elem_at(0,0,m1,v2)==0);
	assert(matrix_set_elem_at(0,0,m2,v3)==0);
	
	assert(linked_list_add_first(ll, m)==0);
	assert(linked_list_add_first(ll, m1)==0);
	assert(linked_list_add_last(ll, m2)==0);

	matrix_get_elem_at(r1,0,0,linked_list_get_first(ll));
	assert(mpz_cmp(r1,v2)==0);
	matrix_get_elem_at(r1,0,0,linked_list_remove_first(ll));
	assert(mpz_cmp(r1,v2)==0);
	              
	matrix_get_elem_at(r2,0,0,linked_list_get_first(ll));
	assert(mpz_cmp(r2,v1)==0);
	matrix_get_elem_at(r2,0,0,linked_list_remove_first(ll));
	assert(mpz_cmp(r2,v1)==0);

	matrix_get_elem_at(r3,0,0,linked_list_get_first(ll));
	assert(mpz_cmp(r3,v3)==0);
	matrix_get_elem_at(r3,0,0,linked_list_remove_first(ll));
	assert(mpz_cmp(r3,v3)==0);
}


int 
main(){
	test_node_set_get();
	test_node_set_elem();
	test_linked_list();
	printf("All linked list tests Succeeded\n");
	return 0;
}

