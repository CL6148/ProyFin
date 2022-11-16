#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symtab.h"

int cur_scope = 0;

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
	printf("%d ", hashval);
	return hashval % SIZE;
}
 
void insert(char *name, int len, int type) {
	unsigned int hashval = hash(name);
	list_t *l = hash_table[hashval];
	while ((l != NULL) && (strcmp(name,l->st_name) != 0)) {
		l = l->next;
	}
	if (l == NULL) {
		l = (list_t*) malloc(sizeof(list_t));
		strncpy(l->st_name, name, len);  

		l->st_type = type;
		l->scope = cur_scope;
		l->next = hash_table[hashval];
		hash_table[hashval] = l; 
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
 
void hide_scope() {
	if(cur_scope > 0) {
		cur_scope--;
	}
}

void incr_scope() {
	cur_scope++;
}

void symtab_dump(FILE * of) {
	int i;
	fprintf(of, "------------ ------\n");
	fprintf(of, "Name         Type  \n");
	fprintf(of, "------------ ------\n");
	for (i = 0; i < SIZE; i++) {
		if (hash_table[i] != NULL) {
			list_t *l = hash_table[i];
			while (l != NULL) {
				fprintf(of, "%-12s ", l->st_name);
				if (l->st_type == INT_TYPE) {
					fprintf(of, "%-7s", "int");
				}
				else {
					fprintf(of, "%-7s", "undef");
				}
				
				fprintf(of, "\n");
				l = l->next;
			}
		}
	}

}