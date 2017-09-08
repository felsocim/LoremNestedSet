#include "../include/shared.h"

struct s_sqlparams new_params() {
	struct s_sqlparams params;
	
	params.table = (char *) malloc(SQL_IDENTIFIER_NAME_MAX_LENGTH * sizeof(char));
	memset(params.table, '\0', SQL_IDENTIFIER_NAME_MAX_LENGTH);
	params.table = strcpy(params.table, DEFAULT_TABLE_NAME);
	
	params.left_bound_column = (char *) malloc(SQL_IDENTIFIER_NAME_MAX_LENGTH * sizeof(char));
	memset(params.left_bound_column, '\0', SQL_IDENTIFIER_NAME_MAX_LENGTH);
	params.left_bound_column = strcpy(params.left_bound_column, DEFAULT_LEFT_BOUND_COLUMN_NAME);
	
	params.right_bound_column = (char *) malloc(SQL_IDENTIFIER_NAME_MAX_LENGTH * sizeof(char));
	memset(params.right_bound_column, '\0', SQL_IDENTIFIER_NAME_MAX_LENGTH);
	params.right_bound_column = strcpy(params.right_bound_column, DEFAULT_RIGHT_BOUND_COLUMN_NAME);
	
	params.level_column = (char *) malloc(SQL_IDENTIFIER_NAME_MAX_LENGTH * sizeof(char));
	memset(params.level_column, '\0', SQL_IDENTIFIER_NAME_MAX_LENGTH);
	params.level_column = strcpy(params.level_column, DEFAULT_LEVEL_COLUMN_NAME);
	params.export_level_column = False;
	
	params.output_file = (char *) malloc(NAME_MAX * sizeof(char));
	memset(params.output_file, '\0', NAME_MAX);
	
	return params;
}

void print_params(struct s_sqlparams params) {
	printf("Table name: `%s`\n", params.table);
	printf("Left bound column name: `%s`\n", params.left_bound_column);
	printf("Right bound column name: `%s`\n", params.right_bound_column);
	
	if(params.export_level_column) {
		printf("Level column name: `%s`\n", params.level_column);
	} else {
		printf("Level column not selected for export.\n");
	}
	
	printf("Output file: %s\n", params.output_file);
}

void destroy_params(struct s_sqlparams params) {
	if(params.table != NULL) {
		free(params.table);
	}
	if(params.left_bound_column != NULL) {
		free(params.left_bound_column);
	}
	if(params.right_bound_column != NULL) {
		free(params.right_bound_column);
	}
	if(params.level_column != NULL) {
		free(params.level_column);
	}
	if(params.output_file != NULL) {
		free(params.output_file);
	}
}

void die(char * message) {
	if(message != NULL && strlen(message) > 0) {
		fprintf(stderr, "%s\n", message);
	}
	
	exit(-1);
}
