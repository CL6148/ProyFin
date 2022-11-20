%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symtab.h"
#include "virtualMachine.h"

extern FILE *yyin;
extern FILE *yyout;
extern int yylex();

void yyerror();

struct label {
	int for_goto;
	int for_jmp_false;
};
struct label *newlabel() {
	return (struct label *) malloc(sizeof(struct label));
};
void install(char *name) {
	list_t *l = getsym(name);
	if (l == 0) {
		putsym(name, 1);
		printf("\n putsym successful");
	}
	else {
		printf("ERR: %s is already defined\n", name);
	}

	list_t *temp = getsym(name);
	printf("\n %d", temp->st_id);
	printf("\n OFFSET:%d\n\n", temp->offset);
}
void context_check(enum code_ops operation, char *name) {
	list_t *l = getsym(name);
	if (l == 0) {
		printf("ERR: %s is not defined\n", name);
	}
	else {
		gen_code(operation, l->offset);
	}
}

%}

%union semrec{
	int ival;
	char *id;
	struct label *lbl;
}

%start	program
%token <ival>	CTEI
%token <id>		ID
%token <lbl>	IF WHILE ELSE

%token	INT FLOAT VOID
%token	DO SKIP READ WRITE
%token	NOTOP ANDOP OROP EQUOP LESSTH GREATH LESST_E GREATH_E
%token	LPAREN RPAREN LBRACK RBRACK LBRACE RBRACE COLON SEMI DOT COMMA ASSIGN
%token	VAR PROG MAIN FUNC RET
%token	CLASS PUB PRIV
%token	CTEF

%left	ADDOP SUBOP
%left	MULOP DIVOP

%%

program: PROG ID SEMI { printf(" >----- Successful read of header\n"); }
	variables { printf(" >----- Successful read of variables block\n"); }
	functions MAIN { printf(" >----- Successful entry into MAIN block\n\t"); }
	block { printf("\n >----- Successful exit of MAIN block\n"); };

variables: VAR vars;
vars: vars type vars1 ID SEMI { printf(" %s", $4);
								install($4); }
	| /* empty */;
vars1: vars1 ID COMMA { printf(" %s", $2);
						install ($2); }
	| /* empty */;

functions: FUNC func;
func: func func1 | /* empty */;
func1: funcHead funcTail;
funcHead: type ID LPAREN parameter RPAREN;
funcTail: LBRACE variables funcStmt RBRACE;
funcStmt: funcStmt statement | /* empty */;

parameter: par | /* empty */;
par: par1 | par COMMA par1;
par1: type ID;

type: INT | FLOAT | VOID;

block: LBRACE block1 RBRACE;
block1: block1 statement | /* empty */;

statement: assignment
	| condition
	| cycle
	| readStmt
	| writeStmt
	| callFunc
	| SKIP SEMI;

assignment: ID ASSIGN expression SEMI { context_check(STORE, $1); };

condition:IF LPAREN expression RPAREN { $1 = (struct label *) newlabel();
										$1->for_jmp_false = reserve_loc(); }
	block { $1->for_goto = reserve_loc(); }
	ELSE { back_patch($1->for_jmp_false, JMP_FALSE, gen_label()); }
	block SEMI { back_patch($1->for_goto, GOTO, gen_label()); };

cycle: WHILE { $1 = (struct label *) newlabel();
			   $1->for_goto = gen_label(); }
	LPAREN expression RPAREN { $1->for_jmp_false = reserve_loc(); }
	DO block SEMI { gen_code(GOTO, $1->for_goto);
					back_patch(JMP_FALSE, $1->for_jmp_false, gen_label()); };

readStmt: READ ID { context_check(READ_INT, $2); } SEMI;

writeStmt: WRITE expression { gen_code(WRITE_INT, 0); } SEMI;

callFunc: ID LPAREN callParam RPAREN;
callParam: callPm1 | /* empty */;
callPm1: callPm1 COMMA varcte | varcte;

expression: exp expr1;
expr1: GREATH exp { gen_code(GT, 0); }
	| LESSTH exp { gen_code(LT, 0); }
	| EQUOP exp { gen_code(EQ, 0); }
	| /* empty */;

exp: term exp1;
exp1: ADDOP term { gen_code(ADD, 0); }
	| SUBOP term { gen_code(SUB, 0); }
	| /* empty */;

term: factor term1;
term1: MULOP factor { gen_code(MULT, 0); }
	| DIVOP factor { gen_code(DIV, 0); }
	| /* empty */;

factor: LPAREN exp RPAREN
	| varcte;

varcte: CTEI { gen_code(LD_INT, $1); }
	| SUBOP CTEI { gen_code(LD_INT, $2 * -1); }
	| ID { context_check(LD_VAR, $1); }

%%

void yyerror(){
	fprintf(stderr, "Syntax error\n");
	exit(1);
}

int main (int argc, char *argv[]){
	int flag;
	yyin = fopen(argv[1], "r");

	printf("DEBUG:\tBeginning of PARSE\n");

	flag = yyparse();
	fclose(yyin);
	
	printf("DEBUG:\tSuccessful parse of file\n");
	printf("END: Compiled without error\n");

	printf("\n");
	print_code();
	fetch_execute_cycle();

	return flag;
}