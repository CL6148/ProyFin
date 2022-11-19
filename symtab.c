#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "varTypes.h"
#include "codeGenerator.h"
#include "symtab.h"

int cur_scope = 0;
int declare = 0;
int intCounter = 0;

void init_hash_table() {
    int i; 
	hash_table = malloc(SIZE * sizeof(list_t*));
	for(i = 0; i < SIZE; i++) {
		hash_table[i] = NULL;
	}
}
 
unsigned int hash(char *key) {
	unsigned int hashval = 0;
	for(;*key!='\0';key++) {
		hashval += *key;
	}
	hashval += key[0] % 11 + (key[0] << 3) - key[0];
	return hashval % SIZE;
}

void insert(char *name, int type) {
	unsigned int hashval = hash(name);
	list_t *l = hash_table[hashval];

	int id = 5000 + intCounter;
	while ((l != NULL) && (strcmp(name,l->st_name) != 0)) {
		l = l->next;
	}
	if (l == NULL) {
		if (declare == 1) {
			l = (list_t*) malloc(sizeof(list_t));
			l->st_id = id;
			strcpy(l->st_name, name);
			l->st_type = type;
			l->scope = cur_scope;
			l->offset = data_location();

			l->next = hash_table[hashval];
			hash_table[hashval] = l;

			printf("Encountered %s for the first time\n", name);
			intCounter++;
		} else {
			printf("Variable %s is not declared\n", name);
		}
	}
	else {
		if (declare == 0) {
			printf("Variable %s is already in the table\n", name);
		}
		else {
			if (l->scope == cur_scope) {
				fprintf(stderr, "ERR: Multiple declaration of variable %s\n", name);
				exit(1);
			}
			else {
				l = (list_t*) malloc(sizeof(list_t));
				l->st_id = id;
				strcpy(l->st_name, name);
				l->st_type = type;
				l->scope = cur_scope;
				l->offset = data_location();
				l->next = hash_table[hashval];
				hash_table[hashval] = l;

				printf("Encountered %s in a new scope %d\n", name, cur_scope);
				intCounter++;
			}
		}
	}
}

list_t *lookup(char *name) {
	unsigned int hashval = hash(name);
	list_t *l = hash_table[hashval];
	while ((l != NULL) && (strcmp(name,l->st_name) != 0)) {
		l = l->next;
	}
	return l;
}

void set_type(char *name, int st_type, int inf_type) {
	list_t *l = lookup(name);
	l->st_type = st_type;

	if (inf_type != UNDEF) {
		l->inf_type = inf_type;
	}
}

int get_type(char *name) {
	list_t *l = lookup(name);
	if (l->st_type == INT_TYPE || l->st_type == REAL_TYPE) {
		return l->st_type;
	}
	else {
		return l->inf_type;
	}
}
 
void hide_scope() {
	list_t *l;
	int i;
	printf("Hiding scope \'%d\':\n", cur_scope);
	for (i = 0; i < SIZE; i++) {
		if (hash_table[i] != NULL) {
			l = hash_table[i];
			while ((l != NULL) && (l->scope == cur_scope)) {
				printf("Hiding %s...\n", l->st_name);
				l = l->next;
			}
			hash_table[i] = l;
		}
	}
	cur_scope--;
}

void incr_scope() {
	cur_scope++;
	printf("Increasing Scope to %d\n", cur_scope);
}

void symtab_dump(FILE * of) {
	fprintf(of, "------ ------------ -------------- -------\n");
	fprintf(of, " ID     NAME         TYPE           SCOPE\n");
	fprintf(of, "------ ------------ -------------- -------\n");
	for (int i = 0; i < SIZE; i++) {
		if (hash_table[i] != NULL) {
			list_t *l = hash_table[i];
			while (l != NULL) {
				fprintf(of, "%-7d", l->st_id);
				fprintf(of, "%-12s ", l->st_name);
				if (l->st_type == INT_TYPE) {
					fprintf(of, "%-15s ", "int");
				}
				else if (l->st_type == REAL_TYPE) {
					fprintf(of, "%-15s ", "real");
				}
				else if (l->st_type == VOID_TYPE) {
					fprintf(of, "%-15s ", "void");
				}

				else if (l->st_type == ARRAY_TYPE) {
					fprintf(of, "array of ");
					if (l->inf_type == INT_TYPE) {
						fprintf(of, "%-6s", "int");
					}
					else if (l->inf_type == REAL_TYPE) {
						fprintf(of, "%-6s", "real");
					}
					else if (l->inf_type == VOID_TYPE) {
						fprintf(of, "%-6s", "coid");
					}
					else {
						fprintf(of, "%-13s", "undef");
					}
				}
				else if (l->st_type == FUNCTION_TYPE) {
					fprintf(of, "func ret ");
					if (l->inf_type == INT_TYPE) {
						fprintf(of, "%-6s", "int");
					}
					else if (l->inf_type == REAL_TYPE) {
						fprintf(of, "%-6s", "real");
					}
					else if (l->inf_type == VOID_TYPE) {
						fprintf(of, "%-6s", "void");
					}
					else {
						fprintf(of, "%-4s", "undef");
					}
				}

				else {
					fprintf(of, "%-15s ", "undef");
				}
				fprintf(of, "%-7d ", l->scope);
				fprintf(of, "\n");
				l = l->next;
			}
		}
	}
}

Param def_param(int param_type, char *param_name) {
	Param param;
	param.param_type = param_type;
	strcpy(param.param_name, param_name);

	return param;
}

int func_declare(char *name, int ret_type, int num_params, Param *parameters) {
	list_t *l = lookup(name);

	if (l->st_type == UNDEF) {
		l->st_type = FUNCTION_TYPE;
		l->inf_type = ret_type;
		l->num_params = num_params;
		l->parameters = parameters;

		return 0;
	}
	else {
		fprintf(stderr, "Function %s has already been decared\n", name);
		exit(1);
	}
}

int func_param_check(char *name, int num_params, Param *parameters) {
	int i, type1, type2;
	list_t *l = lookup(name);

	if (l->num_params != num_params) {
		fprintf(stderr, "Function call %s has wrong number of parameters\n", name);
		exit(1);
	}

	for (i = 0; i < num_params; i++) {
		type1 = l->parameters[i].param_type;
		type2 = parameters[i].param_type;

		get_result_type(type1, type2, NONE);
	}
	return 0;
}