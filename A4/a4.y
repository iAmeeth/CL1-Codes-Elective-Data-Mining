%{
	#include<stdio.h>
	#include "y.tab.h"
	extern FILE *yyin;
%}

%token MAIN IF FOR WHILE INTEGER FLOAT IDENTIFIER STR PRINTF DATATYPE

%%
main: MAIN '('')' '{' body '}' {printf("Valid Main\n");}
;
body: var st 
;
var: vard var |
;
vard: DATATYPE vname ';' {printf("Valid Variable Declaration\n");}
;
vname: IDENTIFIER ',' vname | IDENTIFIER
; 
st: stl st |
;
stl: printf //IMP
;
printf: PRINTF '(' STR ')'';' {printf("VALID PRINT STATEMENT\n");}
;
%%
main(){
	yyin=fopen("input.c","r");
	yyparse();
}
void yyerror(char *s){
	printf("Error:- %s\n",s);
}

