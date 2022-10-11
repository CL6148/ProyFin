%option noyywrap
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.tab.h"
extern FILE *yyin;
extern FILE *yyout;

int lineno = 1;
%}
digit	[0-9]
letter	[A-Za-z]
ctef	{digit}*"."{digit}+
ctei	[0-9]{digit}*
ctes	\"[^"]*\"
id	{letter}+({letter}|{digit})*
%%
"var"	{return VAR; }
"program"	{return PROG; }
"main"	{return MAIN; }
"func"	{return FUNC; }
"return"	{return RET; }
"write"	{return WRITE; }
"read"	{return READ; }

"int"	{return INT; }
"float"	{return FLOAT; }
"void"	{return VOID; }
"if"	{return IF; }
"else"	{return ELSE; }
"do"	{return DO; }
"while"	{return WHILE; }

"class"	{return CLASS; }
"public"	{return PUB; }
"private"	{return PRIV; }

"+"|"-"	{return ADDOP; }
"*"	{return MULOP; }
"/"	{return DIVOP; }
"!="|"=="	{return EQUOP; }
"<"|"<="|">"|">="	{return RELOP; }

"("	{return LPAREN; }
")"	{return RPAREN; }
":"	{return COLON; }
";"	{return SEMI; }
","	{return COMMA; }
"{"	{return LBRACE; }
"}"	{return RBRACE; }
"="	{return ASSIGN; }

{ctef}	{return CTEF; }
{ctei}	{return CTEI; }
{ctes}	{return CTES; }
{id}	{return ID; }

"\n"	{lineno += 1; }
[ \t\r\f]+	/* empty */

%%