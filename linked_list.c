#include "linked_list.h"

int
linked_list_alloc(linked_list** ll)
{
    node* h, *t;
    *ll = malloc(sizeof(linked_list));

    if (*ll == NULL)
    {
        perror("malloc failed");
        return -1;
    }

    if (node_alloc(&h) == -1)
        return -1;

    if (node_alloc(&t) == -1)
        return -1;

    /* Set nodes type */
    h->t = head;
    t->t = tail;
    /* Set head and tail node */
    (*ll)->head = h;
    node_set_next(h, t);
    (*ll)->tail = t;
    return 0;
}

void
linked_list_free(linked_list* ll)
{
    node* n, *next;
    n = ll->head;

    while (n != NULL)
    {
        next = n->next;
        node_free(n);
        n = next;
    }

    free(ll);
}

int
linked_list_add_last(linked_list* ll, matrix* matr)
{
    node* n;

    if (node_alloc(&n) == -1)
        return -1;

    node_set_elem(ll->tail, matr);
    ll->tail->t = unreserved;
    node_set_next(ll->tail, n);
    n->t = tail;
    ll->tail = n;
    return 0;
}

int
linked_list_add_first(linked_list* ll, matrix* matr)
{
    node* n;

    if (node_alloc(&n) == -1)
        return -1;

    node_set_elem(ll->head, matr);
    node_set_next(n, ll->head);
    ll->head->t = unreserved;
    ll->head = n;
    n->t = head;
    return 0;
}

int
linked_list_get_last(linked_list* ll, matrix** matr)
{
    *matr = ll->tail->prev->matr;

    if (*matr == NULL)
        return -1;

    return 0;
}

int
linked_list_get_first(linked_list* ll, matrix** matr)
{
    *matr = ll->head->next->matr;

    if (*matr == NULL)
        return -1;

    return 0;
}

int
linked_list_remove_first(linked_list* ll, matrix** matr)
{
    node* n;
    *matr = ll->head->next->matr;

    if (*matr == NULL)
        return -1;

    n = ll->head->next;
    ll->head->next = ll->head->next->next;
    node_only_free(n);
    return 0;
}


