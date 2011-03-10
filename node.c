#include "node.h"

node*
create_node(){
  	node *n;
	n = malloc(sizeof(node));
	if(n == NULL){
	  	perror("malloc error");
		exit(-1);
	}
	return n;
}

int
set_next_node(node* n, node* next){
	if(n == NULL || next == NULL)
	  	return -1;
	n->next = next;
	return 0;
}

node*
get_next_node(node* n){
  	return n->next;
}

int
set_elem_node(node* n, matrix* matr){
  	if(n == NULL)
	  	return -1;
	n->matr = matr;
	return 0;
}

void
free_node(node* n){
  	free(n);
}
