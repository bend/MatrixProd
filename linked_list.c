#include "linked_list.h"

int
linked_list_alloc(linked_list **ll){
	/* TODO ADD HEAD AND TAIL NODE */

	node *h, *t;
	*ll = malloc(sizeof(linked_list));
	if(*ll == NULL){
	  	perror("malloc failed");
		return -1;
	}
	if(node_alloc(&h) == -1)
		return -1;
	if(node_alloc(&t) == -1)
		return -1;
	h->t= head;
	t->t = tail;
	(*ll)->head = h;
	node_set_next(h,t);
	(*ll)->tail = t;
	return 0;
}

void
linked_list_free(linked_list *ll){
  	/*TODO : FREE ALL THE NODES ?*/
  	free(ll);
}

int 
linked_list_add_last(linked_list *ll, matrix *matr){
	node *n;
	if(node_alloc(&n)==-1)
		return -1;
	node_set_elem(ll->tail,matr);
	ll->tail->t =unreserved;
	node_set_next(ll->tail, n);
	n->t = tail;
	ll->tail = n;
	return 0;
}

int
linked_list_add_first(linked_list *ll, matrix *matr){
  	node *n;
	if(node_alloc(&n) == -1)
		return -1;
	node_set_elem(ll->head,matr);
	node_set_next(n,ll->head);
	ll->head->t = unreserved;
	ll->head = n;
	n->t = head;
	return 0;
}

matrix*
linked_list_get_last(linked_list *ll){
  	return ll->tail->prev->matr;
}

matrix*
linked_list_get_first(linked_list *ll){
	return ll->head->next->matr;
}

matrix*
linked_list_remove_first(linked_list *ll){
	matrix *matr;
	node *n;
	matr = ll->head->next->matr;
	n= ll->head->next;
	ll->head->next = ll->head->next->next;
	node_free(n);
	return matr;
}


