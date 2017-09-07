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
	
	unsigned short int max_level = 0;
	unsigned short int min_nodes_per_level = 0;
	unsigned short int max_nodes_per_level = 0;
	char * table_name = (char *) malloc(SQL_IDENTIFIER_NAME_MAX_LENGTH * sizeof(char));
	char * left_bound_column_name = (char *) malloc(SQL_IDENTIFIER_NAME_MAX_LENGTH * sizeof(char));
	char * right_bound_column_name = (char *) malloc(SQL_IDENTIFIER_NAME_MAX_LENGTH * sizeof(char));
	char * level_column_name = (char *) malloc(SQL_IDENTIFIER_NAME_MAX_LENGTH * sizeof(char));
	char * output_file_name = (char *) malloc(NAME_MAX * sizeof(char));
	Bool default_level_column = False;
	Bool verbose_execution = False;
	
	while( (c = getopt(argc, argv, "d:m:M:t:l:r:vL:o:Vh")) != -1 ) {
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
					memset(table_name, '\0', SQL_IDENTIFIER_NAME_MAX_LENGTH);
					strcpy(table_name, optarg);
				} else {
					die("Argument parsing failed: Table name must not exceed 64 characters!");
				}
				break;
			case 'l':
				if(strlen(optarg) <= SQL_IDENTIFIER_NAME_MAX_LENGTH) {
					memset(left_bound_column_name, '\0', SQL_IDENTIFIER_NAME_MAX_LENGTH);
					strcpy(left_bound_column_name, optarg);
				} else {
					die("Argument parsing failed: Left bound column name must not exceed 64 characters!");
				}
				break;
			case 'r':
				if(strlen(optarg) <= SQL_IDENTIFIER_NAME_MAX_LENGTH) {
					memset(right_bound_column_name, '\0', SQL_IDENTIFIER_NAME_MAX_LENGTH);
					strcpy(right_bound_column_name, optarg);
				} else {
					die("Argument parsing failed: Right bound column name must not exceed 64 characters!");
				}
				break;
			case 'v':
				default_level_column = True;
				break;
			case 'L':
				if(strlen(optarg) <= SQL_IDENTIFIER_NAME_MAX_LENGTH) {
					memset(level_column_name, '\0', SQL_IDENTIFIER_NAME_MAX_LENGTH);
					strcpy(level_column_name, optarg);
					default_level_column = False;
				} else {
					die("Argument parsing failed: Level column name must not exceed 64 characters!");
				}
				break;
			case 'o':
				if(strlen(optarg) <= NAME_MAX) {
					memset(output_file_name, '\0', NAME_MAX);
					strcpy(output_file_name, optarg);
				} else {
					die("Argument parsing failed: Output file name exceeds maximum length allowed by your operating system and/or file system!");
				}
				break;
			case 'V':
				verbose_execution = True;
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
	
	Node * tree = build_tree(NULL, max_level, max_nodes_per_level);
	
	show_tree(tree);
	
	export_to_sql(tree, "export.sql");
	
	destroy_tree(tree);
	
	if(verbose_execution || default_level_column) {
	}
	
	return 0;
}
