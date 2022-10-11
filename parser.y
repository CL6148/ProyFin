%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
extern FILE *yyin;
extern int lineno;
extern int yylex();
void yyerror();
%}

%token	VAR PROG MAIN FUNC RET WRITE READ
%token	INT FLOAT VOID IF ELSE DO WHILE
%token	CLASS PUB PRIV
%token	ADDOP MULOP DIVOP EQUOP RELOP
%token	LPAREN RPAREN COLON SEMI COMMA LBRACE RBRACE ASSIGN
%token	CTEF CTEI CTES ID

%%
program: PROG ID SEMI prog1 prog2 prog3 MAIN LPAREN RPAREN block;
prog1: variables | /* empty */;
prog2: prog2 class | /* empty */;
prog3: prog3 function | /* empty */;

variables: VAR vars1;
vars1: vars2 ID COLON type SEMI;
vars2: vars2 ID COMMA | /* empty */;

type: INT | FLOAT;

class: CLASS ID LBRACE PUB COLON constr_def class1 class2 class3 RBRACE;
class1: constructor | /* empty */;
class2: class4 class5;
class3: PRIV COLON class2 | /* empty */;
class4: class4 method | /* empty */;
class5: class5 attribute | /* empty */;

constr_def: ID LPAREN RPAREN LBRACE c_def1 RBRACE SEMI;
c_def1: c_def1 assignment | /* empty */;

constructor: ID LPAREN constr1 RPAREN LBRACE constr2 RBRACE SEMI;
constr1: constr3 type ID;
constr2: constr2 assignment | /* empty */;
constr3: constr3 type ID COMMA | /* empty */;

method: type_r ID LPAREN met1 RPAREN block;
met1: met2 type ID;
met2: met2 type ID COMMA | /* empty */;

attribute: type ID SEMI;

function: FUNC type_r ID LPAREN func1 RPAREN block return;
func1: func2 type ID;
func2: func2 type ID COMMA | /* empty */;

type_r: VOID | type;

return: RET exp SEMI;

block: LBRACE block1 block2 RBRACE;
block1: variables | /* empty */;
block2: block2 statement | /* empty */;

statement: assignment | condition | st_read | st_write | cycle;

assignment: ID ASSIGN expression SEMI;

condition:IF LPAREN expression RPAREN block cond1 SEMI;
cond1: ELSE block | /* empty */;

st_read: READ LPAREN st_r1 RPAREN SEMI;
st_r1: st_r2 ID;
st_r2: st_r2 ID COMMA | /* empty */;

st_write: WRITE LPAREN st_w1 RPAREN SEMI;
st_w1: st_w2 st_w3;
st_w2: st_w2 st_w3 COMMA | /* empty */;
st_w3: expression | CTES;

cycle: cycle1 | cycle2;
cycle1: DO block WHILE LPAREN expression RPAREN;
cycle2: WHILE LPAREN expression RPAREN DO block;

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

varcte: ID | CTEI | CTEF;



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