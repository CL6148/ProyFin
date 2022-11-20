#include <stdio.h>
#include <stdlib.h>
#include "virtualMachine.h"

#define SIZE 211
#define MAXTOKENLEN 40

int iCounter = 0;

int data_offset = 0;
int data_location() {
    return data_offset++;
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

	printf("|%d %d", operation, arg);
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

	struct list_t *next;
}list_t;

list_t *symtab = (list_t *)0;

list_t *putsym(char *name, int type) {
	int id = 5000 + iCounter;
	list_t *l = (list_t *) malloc(sizeof(list_t));
	l->st_id = id;
	strcpy(l->st_name,name);
	l->st_type = type;
	l->offset = data_location();

	l->next = (struct list_t *) symtab;
	symtab = l;
	iCounter++;
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

void print_code() {
	int i = 0;
	while (i < code_offset) {
		printf("%3ld: %-10s%4ld\n", i, op_name[(int) code[i].op], code[i].arg);
		i++;
	}
}