%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "varTypes.c"
#include "symtab.c"

extern FILE *yyin;
extern FILE *yyout;
extern int lineno;
extern int yylex();

struct label {
	int for_goto;
	int for_jmp_false;
};
struct label *newlabel() {
	return (struct label *) malloc(sizeof(struct label));
};

void yyerror();
%}

%union semrec{
	char *id;

	int ival;
	float fval;

	int data_type;
	int const_type;

	struct label *lbl;

	list_t *symtab_item;
	Value val;
}

%start	program
%token	INT FLOAT VOID
%token<lbl>	IF DO WHILE
%token	ELSE READ WRITE
%token	ADDOP MULOP DIVOP INCR NOTOP ANDOP OROP EQUOP RELOP
%token	LPAREN RPAREN LBRACK RBRACK LBRACE RBRACE COLON SEMI DOT COMMA ASSIGN
%token	VAR PROG MAIN FUNC RET
%token	CLASS PUB PRIV
%token <id>	ID
%token <val.ival>	CTEI
%token <val.fval>	CTEF

%type <data_type> type

%%

program: PROG ID SEMI variables functions MAIN block;

variables: VAR vars;
vars: vars vars1 | /* empty */;
vars1: { declare = 1; } type vars2 { declare = 0; } SEMI;
vars2: vars3 | vars2 COMMA vars3;
vars3: ID | ID arr;
arr: arr LBRACK CTEI RBRACK | LBRACK CTEI RBRACK;

functions: FUNC func;
func: func func1 | /* empty */;
func1: { incr_scope(); } funcHead funcTail { hide_scope(); };
funcHead: { declare = 1; } type ID LPAREN { declare = 0; } parameter RPAREN;
funcTail: LBRACE variables funcStmt RBRACE;
funcStmt: funcStmt statement | /* empty */;

parameter: par | /* empty */;
par: par1 | par COMMA par1;
par1: { declare = 1; } type ID { declare = 0; };

type: INT { $$ = INT_TYPE; }
	| FLOAT { $$ = REAL_TYPE; }
	| VOID { $$ = VOID_TYPE; }
;

block: LBRACE block1 RBRACE;
block1: block1 statement | /* empty */;

statement: assignment
	| condition
	| cycle
	| readStmt
	| writeStmt
	| callFunc
	| RET expression SEMI;

assignment: ID ASSIGN expression SEMI;

condition:IF LPAREN expression RPAREN block cond1 SEMI;
cond1: ELSE block | /* empty */;

cycle: cycle1 | cycle2;
cycle1: DO block WHILE LPAREN expression RPAREN SEMI;
cycle2: WHILE LPAREN expression RPAREN DO block SEMI;

readStmt: READ ID;

writeStmt: WRITE ID;

callFunc: ID LPAREN callParam RPAREN;
callParam: callPm1 | /* empty */;
callPm1: callPm1 COMMA varcte | varcte;

expression: exp expr1;
expr1: expr2 exp | /* empty */
expr2: RELOP | EQUOP;

exp: term exp1;
exp1: exp2 exp | /* empty */;
exp2: ADDOP;

term: factor term1;
term1: term2 term | /* empty */;
term2: MULOP | DIVOP;

factor: LPAREN expression RPAREN | fact1 varcte;
fact1: ADDOP | /* empty */;

varcte: ID | CTEI | CTEF | callFunc;

%%

void yyerror(){
	fprintf(stderr, "Syntax error at line %d\n", lineno);
	exit(1);
}

int main (int argc, char *argv[]){
	init_hash_table();

	int flag;
	yyin = fopen(argv[1], "r");
	flag = yyparse();
	fclose(yyin);

	yyout = fopen("symtab_dump.out", "w");
	symtab_dump(yyout);
	fclose(yyout);

	return flag;
}