%option noyywrap

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "varTypes.h"
#include "symtab.h"
#include "parser.tab.h"

extern FILE *yyin;
extern FILE *yyout;

int lineno = 1;
%}

letter	[A-Za-z]
digit	[0-9]
print	[ -~]

id	{letter}+({letter}|{digit})*
ctei	[0-9]{digit}*
ctef	{digit}*"."{digit}+

%%

"int"	{return INT; }
"float"	{return FLOAT; }
"void"	{return VOID; }

"if"	{return IF; }
"else"	{return ELSE; }
"do"	{return DO; }
"while"	{return WHILE; }
"read"	{return READ; }
"write"	{return WRITE; }

"+"|"-"	{return ADDOP; }
"*"	{return MULOP; }
"/"	{return DIVOP; }
"++"|"--"	{return INCR; }
"!"	{return NOTOP; }
"&&"	{return ANDOP; }
"||"	{return OROP; }
"!="|"=="	{return EQUOP; }
"<"|"<="|">"|">="	{return RELOP; }

"("	{return LPAREN; }
")"	{return RPAREN; }
"["	{return LBRACK; }
"]"	{return RBRACK; }
"{"	{return LBRACE; }
"}"	{return RBRACE; }
":"	{return COLON; }
";"	{return SEMI; }
"."	{return DOT; }
","	{return COMMA; }
"="	{return ASSIGN; }

"var"	{return VAR; }
"program"	{return PROG; }
"main"	{return MAIN; }
"func"	{return FUNC; }
"return"	{return RET; }

"class"	{return CLASS; }
"public"	{return PUB; }
"private"	{return PRIV; }

{id}	{
		insert(yytext, UNDEF);
		yylval.id = (char*) strdup(yytext);
		yylval.symtab_item = lookup(yytext);
		return ID; }
{ctei}	{
		yylval.val.ival = atoi(yytext);
		return CTEI; }
{ctef}	{
		yylval.val.fval = atof(yytext);
		return CTEF; }

"\n"	{lineno += 1; }
[ \t\r\f]+	/* empty */

%%