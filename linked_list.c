#include "linked_list.h"

linked_list*
linked_list_alloc(){
	linked_list *ll;
	ll = malloc(sizeof(linked_list));
	if(ll == NULL){
	  	perror("malloc failed");
		exit(-1);
	}
	ll->size = 0;
	ll->head = NULL;
	ll->tail = NULL;
	return ll;
}

void
linked_list_free(linked_list *ll){
  	/*TODO : FREE ALL THE NODES ?*/
  	free(ll);
}

int 
linked_list_add_last(linked_list *ll, matrix *matr){
	node *n, *temp;
	n = node_alloc();
	node_set_elem(n,matr);
	temp = ll->tail;
	ll->tail = n;
	node_set_next(temp,n);
	if(ll->head == NULL)
		ll->head = n;
	return 0;
}

int
linked_list_add_first(linked_list *ll, matrix *matr){
  	node *n,*temp;
	n=node_alloc();
	node_set_elem(n,matr);
	temp = ll->head;
	ll->head = n;
	node_set_next(n,temp);
	if(ll->tail == NULL)
	  	ll->tail = n;
	return 0;
}

matrix*
linked_list_get_last(linked_list *ll){
  	return ll->tail->matr;
}

matrix*
linked_list_get_first(linked_list *ll){
	return ll->head->matr;
}

matrix*
linked_list_remove_first(linked_list *ll){
	matrix *matr;
	node *n;
	matr = ll->head->matr;
	n= ll->head;
	ll->head = n->next;
	return matr;
}


