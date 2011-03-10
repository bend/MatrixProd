
#include "linked_list.h"

linked_list*
create_linked_list(){
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
free_linked_list(linked_list *ll){
  	/*TODO : FREE ALL THE NODES ?*/
  	free(ll);
}

int 
add_last_linked_list(linked_list *ll, matrix *matr){
	node *n, *temp;
	n = create_node();
	set_elem_node(n,matr);
	temp = ll->tail;
	ll->tail = n;
	set_next_node(temp,n);
	if(ll->head == NULL)
		ll->head = n;
	return 0;
}

int
add_first_linked_list(linked_list *ll, matrix *matr){
  	node *n,*temp;
	n=create_node();
	set_elem_node(n,matr);
	temp = ll->head;
	ll->head = n;
	set_next_node(n,temp);
	if(ll->tail == NULL)
	  	ll->tail = n;
	return 0;
}

matrix*
get_last_linked_list(linked_list *ll){
  	return ll->tail->matr;
}

matrix*
get_first_linked_list(linked_list *ll){
	return ll->head->matr;
}

matrix*
remove_elem_first_linked_list(linked_list *ll){
	matrix *matr;
	node *n;
	matr = ll->head->matr;
	n= ll->head;
	ll->head = n->next;
	return matr;
}


