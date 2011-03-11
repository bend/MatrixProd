#include "node.h"

node*
node_alloc(){
  	node *n;
	n = malloc(sizeof(node));
	if(n == NULL){
	  	perror("malloc error");
		exit(-1);
	}
	n->next = NULL;
	n->prev = NULL;
	return n;
}

int
node_set_next(node* n, node* next){
	if(n == NULL || next == NULL)
	  	return -1;
	n->next = next;
	next->prev = n;
	return 0;
}

node*
node_get_next(node* n){
  	return n->next;
}

node*
node_get_prev(node* n){
	return n->prev;
}

int
node_set_elem(node* n, matrix* matr){
  	if(n == NULL)
	  	return -1;
	n->matr = matr;
	return 0;
}

void
node_free(node* n){
  	free(n);
}
