#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <limits.h>
#include "../include/shared.h"
#include "../include/node.h"
#include "../include/lorem.h"

int main(int argc, char ** argv) {
	srand((unsigned int)time(NULL));
	
	int c;
	
	unsigned short int max_level = DEFAULT_STRUCTURE_DEPTH;
	unsigned short int min_nodes_per_level = DEFAULT_MINIMUM_NODES_PER_LEVEL;
	unsigned short int max_nodes_per_level = DEFAULT_MAXIMUM_NODES_PER_LEVEL;
	
	struct s_sqlparams params = new_params();
	
	Bool output_file_set = False;
	
	while( (c = getopt(argc, argv, "d:m:M:t:l:r:vL:o:h")) != -1 ) {
		switch(c) {
			case 'd':
				max_level = atoi(optarg);
				break;
			case 'm':
				min_nodes_per_level = atoi(optarg);
				break;
			case 'M':
				max_nodes_per_level = atoi(optarg);
				break;
			case 't':
				if(strlen(optarg) <= SQL_IDENTIFIER_NAME_MAX_LENGTH) {
					strcpy(params.table, optarg);
				} else {
					die("Argument parsing failed: Table name must not exceed 64 characters!");
				}
				break;
			case 'l':
				if(strlen(optarg) <= SQL_IDENTIFIER_NAME_MAX_LENGTH) {
					strcpy(params.left_bound_column, optarg);
				} else {
					die("Argument parsing failed: Left bound column name must not exceed 64 characters!");
				}
				break;
			case 'r':
				if(strlen(optarg) <= SQL_IDENTIFIER_NAME_MAX_LENGTH) {
					strcpy(params.right_bound_column, optarg);
				} else {
					die("Argument parsing failed: Right bound column name must not exceed 64 characters!");
				}
				break;
			case 'v':
				params.export_level_column = True;
				break;
			case 'L':
				if(strlen(optarg) <= SQL_IDENTIFIER_NAME_MAX_LENGTH) {
					strcpy(params.level_column, optarg);
					params.export_level_column = True;
				} else {
					die("Argument parsing failed: Level column name must not exceed 64 characters!");
				}
				break;
			case 'o':
				if(strlen(optarg) <= NAME_MAX) {
					strcpy(params.output_file, optarg);
					output_file_set = True;
				} else {
					die("Argument parsing failed: Output file name exceeds maximum length allowed by your operating system and/or file system!");
				}
				break;
			case 'h':
				printf("LoremNestedTree 1.0 created by Marek Felsoci. For more information visit: http://www.marekonline.eu.\nUsage: lnt -d, [-m, -M, -t, -r , -l, -v, -L, -V, -h]\n");
				exit(0);
				break;				
			case '?':
				die("Argument(s) mismatch!\nUsage: lorem [-d] structure depth in levels [-m] maximum nodes count per structure level");
				break;
			default:
				exit(0);
		}
	}
	
	if(!output_file_set) {
		die("Failure: No output file specified!");
	}
	
	
	show_tree(tree);
	
	printf("\n");
	
	Node * tree = build_tree(NULL, max_level, min_nodes_per_level, max_nodes_per_level);
	export_to_sql(tree, params);
	
	
	destroy_tree(tree);
	destroy_params(params);
	
	
	return 0;
}
