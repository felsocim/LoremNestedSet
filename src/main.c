#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "../include/node.h"
#include "../include/lorem.h"

int main(int argc, char ** argv) {
	srand((unsigned int)time(NULL));
	
	unsigned short int max_level = 0;
	unsigned short int max_nodes_per_level = 0;
	int c;
	
	while( (c = getopt(argc, argv, "d:m:")) != -1 ) {
		switch(c) {
			case 'd':
				max_level = atoi(optarg);
				break;
			case 'm':
				max_nodes_per_level = atoi(optarg);
				break;
			case '?':
				die("Argument(s) mismatch!\nUsage: lorem [-d] structure depth in levels [-m] maximum nodes count per structure level");
				break;
			default:
				exit(0);
		}
	}
	
	Node * tree = generate_tree(NULL, 0, 0, max_level, max_nodes_per_level);
	
	show_tree(tree);
	
	destroy_tree(tree);
	
	return 0;
}
