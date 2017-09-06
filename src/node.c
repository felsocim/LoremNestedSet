#include "../include/node.h"

Node * new_node(unsigned short int identifier) {
	Node * node = (Node *) malloc(sizeof(Node));
	
	if(node != 0) {
		node->identifier = identifier;
		node->ch_size = 0;
		node->ch_length = 0;
		node->children = NULL;
		return node;
	}
	
	die("Failed to create new node!");
	
	return NULL;
}	

Node * append_child(Node * node, Node * parent) {
	if(node == NULL || parent == NULL) {
		die("Node or parent null!\n");
	}
	
	if(parent->children == NULL) {
		parent->children = (Node **) malloc(INITIAL_NODE_LIST_SIZE * sizeof(Node*));
		if(parent->children != 0) {
			parent->children[0] = node;
			parent->ch_size = INITIAL_NODE_LIST_SIZE;
			parent->ch_length = 1;
			return parent;
		}
		die("Unable to allocate empty node list!");
	}
	
	if(parent->ch_size == parent->ch_length) {
		parent->children = realloc(parent->children, (parent->ch_length + 1) * sizeof(Node *));
		if(parent->children != 0) {
			parent->children[parent->ch_length] = node;
			parent->ch_size += 1;
			parent->ch_length += 1;
			return parent;
		}
		die("Unable to reallocate full node list!");
	}
	
	parent->children[parent->ch_length] = node;
	parent->ch_length += 1;
	
	return parent;
}
	
				
Node * generate_tree(Node * tree, unsigned short int level, unsigned short previous_count, unsigned short int max_level, unsigned short int max_nodes_per_level) {
	if(level == max_level) {
		return tree;
	}
	
	unsigned short min_nodes_per_level = 1;
	
	if(previous_count > 1 ) {
		min_nodes_per_level = previous_count;
	}
	
	unsigned short int random_count = ( rand() % (max_nodes_per_level + 1 - min_nodes_per_level) ) + min_nodes_per_level;
	unsigned short int i = 0;
	
	if(tree == NULL) {
		tree = new_node(previous_count);
	} else {
		tree->identifier = previous_count;
	}
	
	tree->level = level;
	
	for(i = 0; i < random_count; i++) {
		Node * child = new_node(previous_count + i);
		child->level = level + 1;
		tree = append_child(child, tree);
	}
	
	for(i = 0; i < tree->ch_length; i++) {
		generate_tree(tree->children[i], level + 1, random_count, max_level, max_nodes_per_level);
	}
	
	return tree;
}	

void show_tree(Node * tree) {
	unsigned short int i = 0;
	
	for(i = 0; i < tree->level; i++) {
		printf("\t");
	}
	
	printf("[%d] Lorem ipsum dolor sit amet.\n", tree->level);	
	
	for(i = 0; i < tree->ch_length; i++) {
		show_tree(tree->children[i]);
	}
}

void die(char * message) {
	if(message != NULL && strlen(message) > 0) {
		fprintf(stderr, "%s\n", message);
	}
	
	exit(-1);
}
