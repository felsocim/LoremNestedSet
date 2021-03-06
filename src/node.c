/**
 * @file node.c
 * @author Marek Felsoci
 * @brief Implements nodes-related functions.
 * @version 1.0
 **/ 
#include "../include/node.h"

/**
 * @brief Allocates a new node.
 * @returns Node* Pointer to the newly allocated node (returns NULL on failure).
 **/
Node * new_node() {
	Node * node = (Node *) malloc(sizeof(Node));
	
	if(node != 0) {
		node->left_bound = 1;
		node->right_bound = 2;
		node->parent = NULL;
		node->next = NULL;
		
		return node;
	}
	
	die("Failed to create new node!");
	
	return NULL;
}	

/**
 * @brief appends a new node to given data structure.
 * @param 	unsigned short int	level 	New node's level.
 * @param 	Node* 				parent	New node's parent.
 * @param 	Node* 				tree	Target data structure.
 * @returns	Node*						Updated data structure.
 **/
Node * append_child(unsigned short int level, Node * parent, Node * tree) {	
	if(tree == NULL || parent == NULL) {
		Node * created = new_node();
		created->level = level;	
		
		return created;
	}
	
	Node * temp = tree;
	unsigned short int p_right = parent->right_bound;
	
	while(temp != NULL) {
		if(temp->right_bound >= p_right) {
			temp->right_bound += 2;
		}
		
		temp = temp->next;
	}
	
	temp = tree;
	Node * last = NULL;
	
	while(temp != NULL) {
		if(temp->left_bound >= p_right) {
			temp->left_bound += 2;
		}
		if(temp->next == NULL) {
			last = temp;
		}
		temp = temp->next;
	}
	
	last->next = new_node();
	last->next->left_bound = p_right;
	last->next->right_bound = p_right + 1;
	last->next->parent = parent;
	last->next->level = level;
	
	return tree;
}	

/**
 * @brief Generates mock nodes for given level in given data structure.
 * @param Node*					tree				Target data structure.
 * @param unsigned short int	level				Target level.
 * @param unsigned short int	min_nodes_per_level	Minimum nodes count per level.
 * @param unsigned short int	max_nodes_per_level	Maximum nodes count per level.	
 * @returns Node*									Updated data structure.
 **/		
Node * generate_level(Node * tree, unsigned short int level, unsigned short int min_nodes_per_level, unsigned short int max_nodes_per_level) {		
	if(level == 0 || tree == NULL) {
		return append_child(0, NULL, tree);
	}
	
	unsigned short int i = 0;
	unsigned short int random_count = ( rand() % (max_nodes_per_level - min_nodes_per_level + 1) ) + min_nodes_per_level;
	
	Node * temp = tree;
	
	while(temp != NULL) {
		if(temp->level == level - 1) {
			for(i = 0; i < random_count; i++) {
				tree = append_child(level, temp, tree);
			}
		}
		temp = temp->next;
	}
	
	return tree;
}	

/**
 * @brief Builds the whole data structure by grouping all levels.
 * @param Node*	tree	Target data structure.
 * @param unsigned short int	max_level	Target data structure depth.
 * @param unsigned short int	min_nodes_per_level	Minimum nodes count per level.
 * @param unsigned short int	max_nodes_per_level	Maximum nodes count per level.	
 * @returns Node*									Updated data structure.
 **/
Node * build_tree(Node * tree, unsigned short int max_level, unsigned short int min_nodes_per_level, unsigned short int max_nodes_per_level) {
	unsigned short int i = 0;
	
	printf("Building tree... ");
	
	for(i = 0; i < max_level; i++) {
		tree = generate_level(tree, i, min_nodes_per_level, max_nodes_per_level);
	}
	
	printf("Success\n");
	
	return tree;
}

/**
 * @brief Deallocates an existing data structure.
 * @param Node* tree Data structure to be deallocated.
 * @returns void
 **/
void destroy_tree(Node * tree) {
	if(tree == NULL) {
		return;
	}
	
	Node * temp = tree;
	
	while(temp != NULL) {
		Node * current = temp;
		temp = temp->next;
		free(current);
	}	
}

/**
 * @brief Exports given data structure to a SQL script following specified parameters.
 * @param Node*					tree	Data structure to be exported.
 * @param struct s_sqlparams	params	Export parameters.
 * @returns void
 **/
void export_to_sql(Node * tree, struct s_sqlparams params) {
	if(tree == NULL) {
		die("Nothing to export. Tree is empty!");
	}
	
	int fd;
	
	printf("Generating SQL statements... ");
	
	if((fd = open(params.output_file, O_WRONLY | O_CREAT | O_TRUNC)) < 0) {
		perror("SQL Export");
		die("Unable to create target file!");
	}
	
	size_t total = 0, current = 0;
	char * line = (char *) malloc(1024 * sizeof(char));
	Node * temp = tree;
	
	while(temp != NULL) {		
		if(params.export_level_column) {
			if(sprintf(line, "INSERT INTO %s (`%s`, `%s`, `%s`) VALUES (%d, %d, %d);\n", params.table, params.left_bound_column, params.right_bound_column, params.level_column, temp->left_bound, temp->right_bound, temp->level) < 1) {
				die("Error while writing into target file!");
			}
		} else {
			if(sprintf(line, "INSERT INTO %s (`%s`, `%s`) VALUES (%d, %d);\n", params.table, params.left_bound_column, params.right_bound_column, temp->left_bound, temp->right_bound) < 1) {
				die("Error while writing into target file!");
			}
		}
		
		if((current = write(fd, line, strlen(line))) < 0) {
			perror("SQL Export");
			die("Error while writing into target file!");
		}
		
		total += current;	
		
		temp = temp->next;
	}
	
	free(line);
	
	close(fd);
	
	printf("Success [output: %s (%d %s)]\n", params.output_file, (total > 1024 ? total / 1024 : total), (total > 1024 ? "kB" : "B"));
} 
