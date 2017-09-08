#ifndef __SHARED_H
#define __SHARED_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define SQL_IDENTIFIER_NAME_MAX_LENGTH 64
#define DEFAULT_STRUCTURE_DEPTH 3
#define DEFAULT_MINIMUM_NODES_PER_LEVEL 1
#define DEFAULT_MAXIMUM_NODES_PER_LEVEL 5
#define DEFAULT_TABLE_NAME "mock_table"
#define DEFAULT_LEFT_BOUND_COLUMN_NAME "left"
#define DEFAULT_RIGHT_BOUND_COLUMN_NAME "right"
#define DEFAULT_LEVEL_COLUMN_NAME "level"

typedef enum {
	False,
	True
} Bool;

struct s_sqlparams {
	char * table;
	char * left_bound_column;
	char * right_bound_column;
	char * level_column;
	Bool export_level_column;
	char * output_file;
};

struct s_sqlparams new_params();
void print_params(struct s_sqlparams params);
void destroy_params(struct s_sqlparams params);

void die(char * message);

#endif
