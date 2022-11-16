#define SIZE 211
#define MAXTOKENLEN 40

#define UNDEF 0
#define INT_TYPE 1
#define REAL_TYPE 2
#define STR_TYPE 3
#define LOGIC_TYPE 4
#define ARRAY_TYPE 5
#define FUNCTION_TYPE 6

#define BY_VALUE 1
#define BY_REFER 2

typedef struct list_t{
	char st_name[MAXTOKENLEN];
	int st_size;
	int scope;

	int st_ival;
	double st_fval;
	char *st_sval;
	int st_type;

	struct list_t *next;
}list_t;

static list_t **hash_table;

void init_hash_table();
unsigned int hash(char *key);
void insert(char *name, int len, int type);
list_t *lookup(char *name);
void hide_scope();
void incr_scope();
void symtab_dump(FILE *of);