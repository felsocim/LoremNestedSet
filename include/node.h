#ifndef __NODE_H
#define __NODE_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include "shared.h"

typedef struct s_node {
	unsigned short int left_bound;
	unsigned short int right_bound;
	unsigned short int level;
	struct s_node * parent;
	struct s_node * next;
} Node;

Node * new_node();
Node * append_child(unsigned short int level, Node * parent, Node * tree);
Node * generate_level(Node * tree, unsigned short int level, unsigned short int min_nodes_per_level, unsigned short int max_nodes_per_level);
Node * build_tree(Node * tree, unsigned short int max_level, unsigned short int min_nodes_per_level, unsigned short int max_nodes_per_level);

void destroy_tree(Node * tree);
void export_to_sql(Node * tree, struct s_sqlparams params); 

#endif
