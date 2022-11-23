#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "virtualMachine.h"

#define SIZE 211
#define MAXTOKENLEN 40

int iCounter = 0;
int fCounter = 0;
int arrCounter = 0;
int matCounter = 0;

int curr_scope = 0;

int data_offset = 0;
int data_location() {
    return data_offset++;
}
void incr_offset(int count) {
	data_offset = data_offset + count;
}

int code_offset = 0;
int reserve_loc() {
    return code_offset++;
}
int gen_label() {
    return code_offset;
}

void gen_code(enum code_ops operation, int arg) {
    code[code_offset].op = operation;
    code[code_offset++].arg = arg;
}
void back_patch(int addr, enum code_ops operation, int arg) {
    code[addr].op = operation;
    code[addr].arg = arg;
}


typedef struct list_t{
	int st_id;
	char st_name[MAXTOKENLEN];
	int st_type;
	int offset;
	int size;
	int dim1;
	int dim2;

	struct list_t *next;
}list_t;

list_t *symtab = (list_t *)0;

list_t *putsym(char *name, int type, int dim1, int dim2) {
	int id;
	if (type == 0) {
		id = 1000 + iCounter;
		iCounter++;
	}
	else if (type == 1) {
		id = 2000 + fCounter;
		fCounter++;
	}
	else if (type == 2) {
		id = 3000 + arrCounter;
		arrCounter++;
	}
	else if (type == 3) {
		id = 4000 + matCounter;
		matCounter++;
	}
	else {
		fprintf(stderr, "ERR: Unrecognized data type\n");
	}

	list_t *l = (list_t *) malloc(sizeof(list_t));
	l->st_id = id;
	strcpy(l->st_name,name);
	l->st_type = type;
	l->size = dim1 * dim2;
	l->dim1 = dim1;
	l->dim2 = dim2;
	l->offset = data_location();

	l->next = (struct list_t *) symtab;
	symtab = l;
	return l;
}

list_t *getsym(char *name) {
	list_t *l;
	for (l = symtab; l != (list_t *)0; l = (list_t *)l->next) {
		if (strcmp(l->st_name,name) == 0) {
			return l;
		}
	}
	return 0;
}

list_t *lookupID(int id) {
	list_t *l;
	for (l = symtab; l != (list_t *)0; l = (list_t *)l->next) {
		if (id == l->st_id) {
			return l;
		}
	}
	return 0;
}

int getOffset(list_t *l, int slot) {
    return l->offset + slot;
}

void print_code() {
	int i = 0;
	while (i < code_offset) {
		printf("%3ld: %-10s%4ld\n", i, op_name[(int) code[i].op], code[i].arg);
		i++;
	}
}