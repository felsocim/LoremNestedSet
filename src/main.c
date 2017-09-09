/**
 * @file main.c
 * @author Marek Felsoci
 * @brief Contains main function.
 * @version 1.0
 **/ 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <limits.h>
#include "../include/shared.h"
#include "../include/node.h"

/**
 * @brief Main function.
 **/
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
					die("Argument parsing failed (table name must not exceed 64 characters)!");
				}
				break;
			case 'l':
				if(strlen(optarg) <= SQL_IDENTIFIER_NAME_MAX_LENGTH) {
					strcpy(params.left_bound_column, optarg);
				} else {
					die("Argument parsing failed (left bound column name must not exceed 64 characters)!");
				}
				break;
			case 'r':
				if(strlen(optarg) <= SQL_IDENTIFIER_NAME_MAX_LENGTH) {
					strcpy(params.right_bound_column, optarg);
				} else {
					die("Argument parsing failed (right bound column name must not exceed 64 characters)!");
				}
				break;
			case 'v':
				if(params.export_level_column) {
					die("Argument parsing failed (-v option can not be used together with -L option)!");
				}
				params.export_level_column = True;
				break;
			case 'L':
				if(params.export_level_column) {
					die("Argument parsing failed (-L option can not be used together with -v option)!");
				}
				if(strlen(optarg) <= SQL_IDENTIFIER_NAME_MAX_LENGTH) {
					strcpy(params.level_column, optarg);
					params.export_level_column = True;
				} else {
					die("Argument parsing failed (level column name must not exceed 64 characters)!");
				}
				break;
			case 'o':
				if(strlen(optarg) <= NAME_MAX) {
					strcpy(params.output_file, optarg);
					output_file_set = True;
				} else {
					die("Argument parsing failed (output file name exceeds maximum length allowed by your operating system and/or file system)!");
				}
				break;
			case 'h':
				printf("Usage: lnt -o <output script> [-d, -m, -M, -t, -l, -r, -v, -L, -h]\n");
				printf("Allows to build a mock nested tree data strcture for database testing purposes.\nExports the resulting structure into a SQL script containing necessary insert statements.\n\n");
				printf("Mandatory option:\n  -o\tspecifies output script file\n");
				printf("Other options:\n");
				printf("  -d\tdepth of data structure (number of levels)\n");
				printf("  -m\tminimum nodes count per level (default value: 1)\n");
				printf("  -M\tmaximum nodes count per level (default value: 5)\n");
				printf("  -t\tcustom name (without quotes or `) for target SQL table (default value: 'mock_table')\n");
				printf("  -l\tcustom name (without quotes or `) for left boundary column (default value: 'left')\n");
				printf("  -r\tcustom name (without quotes or `) for right boundary column (default value: 'right')\n");
				printf("  -v\texport also level column with its default name (not associable with -L option)\n");
				printf("  -L\tcustom name (without quotes or `) for level column (not associable with -v option)\n");
				printf("  -h\tdisplays this text\n\n");
				printf("Full documentation and application information can be found at: https://github.com/felsocim/LoremNestedSet\nLicensed under the terms of MIT software license: https://github.com/felsocim/LoremNestedSet/blob/master/LICENSE/licenses/MIT\n");
				printf("Copyright (c) 2017 Marek Felsoci\n");
				exit(0);
				break;				
			case '?':
				die("Argument(s) mismatch!\nUse -h option to display help.");
				break;
			default:
				exit(0);
		}
	}
	
	if(!output_file_set) {
		die("No output file specified!");
	}
	
	printf(" _                              _   _           _           _  _____      _   \n");
	printf("| |                            | \\ | |         | |         | |/ ____|    | |  \n");
	printf("| |     ___  _ __ ___ _ __ ___ |  \\| | ___  ___| |_ ___  __| | (___   ___| |_ \n");
	printf("| |    / _ \\| '__/ _ \\ '_ ` _ \\| . ` |/ _ \\/ __| __/ _ \\/ _` |\\___ \\ / _ \\ __|\n");
	printf("| |___| (_) | | |  __/ | | | | | |\\  |  __/\\__ \\ ||  __/ (_| |____) |  __/ |_ \n");
	printf("|______\\___/|_|  \\___|_| |_| |_|_| \\_|\\___||___/\\__\\___|\\__,_|_____/ \\___|\\__|\n");
	
	printf("Version: 1.0\nDeveloped by: Marek Felsoci\nFor more information and updates, please, visit: https://github.com/felsocim/LoremNestedSet\nTo display help, run with -h option.\n\n");
	
	printf("\nP a r a m e t e r s:\n");
	printf("Structure depth: %d levels\n", max_level);
	printf("Minimum nodes count per level: %d\n", min_nodes_per_level);
	printf("Maximum nodes count per level: %d\n", max_nodes_per_level);
	
	print_params(params);
	
	printf("\n");
	
	Node * tree = build_tree(NULL, max_level, min_nodes_per_level, max_nodes_per_level);
	export_to_sql(tree, params);
	
	printf("Performing cleanup... ");
	
	destroy_tree(tree);
	destroy_params(params);
	
	printf("Success\n");
	
	printf("Bye\n");
	
	return 0;
}
