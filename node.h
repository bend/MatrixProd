#ifndef __NODE_H__
#define __NODE_H__

#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"


typedef struct node node;

struct node{
  node* next;
  matrix* matr;
};


node*
create_node();

int
set_next_node(node* n, node* next);

node*
get_next_node(node* n);

int
set_elem_node(node* n, matrix* matr);

#endif
