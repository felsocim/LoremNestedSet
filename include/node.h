#ifndef __NODE_H
#define __NODE_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

#define INITIAL_NODE_LIST_SIZE 10
#define LENGTH(array) ( sizeof(array) / sizeof(array[0]) )

typedef enum {
	FALSE,
	TRUE
} Bool;

typedef struct s_node {
	unsigned short int identifier;
	unsigned short int left_bound;
	unsigned short int right_bound;
	unsigned short int level;
	unsigned short int ch_size;
	unsigned short int ch_length;
	struct s_node ** children;
} Node;

Node * new_node(unsigned short int identifier);
Node * append_child(Node * node, Node * parent);
Node * generate_tree(Node * tree, unsigned short int level, unsigned short previous_count, unsigned short int max_level, unsigned short int max_nodes_per_level);

void show_tree(Node * tree);
void die(char * message);

#endif
