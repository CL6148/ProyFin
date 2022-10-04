%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
extern FILE *yyin;
extern int lineno;
extern int yylex();
void yyerror();
%}

%token	VAR PROG PRINT
%token	INT FLOAT IF ELSE
%token	ADDOP MULOP DIVOP EQUOP RELOP
%token	LPAREN RPAREN COLON SEMI COMMA LBRACE RBRACE ASSIGN
%token	CTEF CTEI CTES ID

%%
program: PROG ID SEMI prog1 bloque;
prog1: vars | /* empty */;

vars: VAR vars1;
vars1: vars1 vars2 ID COLON tipo SEMI | /* empty */;
vars2: vars2 ID COMMA | /* empty */;

tipo: INT | FLOAT;

bloque: LBRACE bloq1 RBRACE;
bloq1: bloq1 estatuto | /* empty */;

estatuto: asignacion | condicion | escritura;

asignacion: ID ASSIGN expresion SEMI;

condicion: IF LPAREN expresion RPAREN bloque cond1 SEMI;
cond1: ELSE bloque | /* empty */;

escritura: PRINT LPAREN escr1 RPAREN SEMI;
escr1: escr2 escr3 | /* empty */;
escr2: CTES | expresion;
escr3: COMMA escr2 | /* empty */

expresion: exp expr1;
expr1: expr2 exp | /* empty */;
expr2: RELOP | EQUOP;

exp: termino exp1;
exp1: exp2 termino | /* empty */;
exp2: ADDOP;

termino: factor term1;
term1: term2 factor | /* empty */
term2: MULOP | DIVOP;

factor: LPAREN expresion RPAREN | fact1 varcte;
fact1: ADDOP | /* empty */

varcte: ID | CTEI | CTEF

%%
void yyerror(){
	fprintf(stderr, "Syntax error at line %d\n", lineno);
	exit(1);
}

int main (int argc, char *argv[]){
	int flag;
	yyin = fopen(argv[1], "r");
	flag = yyparse();
	fclose(yyin);

	return flag;
}