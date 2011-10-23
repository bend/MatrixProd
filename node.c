#include "node.h"

int
node_alloc(node** n)
{
    *n = malloc(sizeof(node));

    if (n == NULL)
    {
        fprintf(stderr, "malloc error");
        return -1;
    }

    (*n)->next = NULL;
    (*n)->prev = NULL;
    (*n)->matr = NULL;
    return 0;
}

int
node_set_next(node* n, node* next)
{
    if (n == NULL || next == NULL)
        return -1;

    n->next = next;
    next->prev = n;
    return 0;
}

int
node_get_next(node* n, node** res)
{
    if (n->next == NULL)
        return -1;

    *res = n->next;
    return 0;
}

int
node_get_prev(node* n, node** res)
{
    if (n->prev == NULL)
        return -1;

    *res = n->prev;
    return 0;
}

int
node_set_elem(node* n, matrix* matr)
{
    if (n == NULL)
        return -1;

    n->matr = matr;
    return 0;
}

void
node_free(node* n)
{
    matrix_free(n->matr);
    free(n);
}

void
node_only_free(node* n)
{
    free(n);
}
