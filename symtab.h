#include "varTypes.h"

#define SIZE 211
#define MAXTOKENLEN 40

typedef union Value {
	int ival;
	float fval;
	char cval;
	char *sval;
}Value;

typedef struct Param {
	int param_type;
	char param_name[MAXTOKENLEN];

	Value val;
}Param;

typedef struct list_t{
	int st_id;
	char st_name[MAXTOKENLEN];
	int st_type;
	int scope;

	Value val;

	int inf_type;

	Value *vals;
	int array_size;

	Param *parameters;
	int num_params;

	int offset;

	struct list_t *next;
}list_t;

static list_t **hash_table;

void init_hash_table();
unsigned int hash(char *key);
void insert(char *name, int type);
list_t *lookup(char *name);

void set_type(char *name, int st_type, int inf_type);
int get_type(char *name);

void hide_scope();
void incr_scope();

void symtab_dump(FILE *of);

Param def_param(int param_type, char *param_name);
int func_declare(char *name, int ret_type, int num_params, Param *parameters);
int func_param_check(char *name, int num_params, Param *parameters);