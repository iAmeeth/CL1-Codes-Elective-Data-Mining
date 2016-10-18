%{
	#include<stdio.h>
	#include<string.h>
	#include "y.tab.h"
	extern int yylval; //IMP
%}

digit [0-9]
letter [a-zA-Z]
integer {digit}+
identifier {letter}({digit}|{letter})*
float ({digit}*)\.({digit}+)

%%
[ \t\n]+ ;
"," |
";" |
"(" |
")" {return yytext[0];}

main 	{return MAIN;}
if 	{return IF;}
for 	{return FOR;}
while 	{return WHILE;}
int|char|float|bool|double  {return DATATYPE;} //NO SPACES BETWEEN |
printf 	{return PRINTF;}
\"(.)*\" {return STR;}

{integer} {yylval=atoi(yytext);return INTEGER;}
{float} {yylval=atof(yytext);return FLOAT;}
{identifier} {return IDENTIFIER;} //IMP
. 	{return yytext[0];} //IMP

%%

int yywrap(){
	return 1;
}
