%{
#include<stdio.h>
int line=0;
%}

%%
"#include" {printf("%s is a Preprocessor Directive\n",yytext);fprintf(yyout,"%d\t%s\tPreprocessor Directive\n",line,yytext);}
"<"((.)*.h)">" {printf("%s is a Header\n",yytext);fprintf(yyout,"%d\t%s\tHeader\n",line,yytext);}
"iostream" {printf("%s is a Header\n",yytext);fprintf(yyout,"%d\t%s\tHeader\n",line,yytext);}

"using namespace "(.)*; {printf("%s is a Defining Namespace\n",yytext);fprintf(yyout,"%d\t%s\tDefining Namespace\n",line,yytext);}

main |
return |
for |
while {printf("%s is a Keyword\n",yytext);fprintf(yyout,"%d\t%s\tKeyword\n",line,yytext);}

int |
float |
double |
char |
string {printf("%s is a DataType\n",yytext);fprintf(yyout,"%d\t%s\tDataType\n",line,yytext);}

%d |
%s |
%c |
%f |
%u {printf("%s is a Format Specifier\n",yytext);fprintf(yyout,"%d\t%s\tFormat Specifier\n",line,yytext);}

\t {printf("%s is a Output Formatter\n",yytext);fprintf(yyout,"%d\t%s\tOutput Formatter\n",line,yytext);}

(printf) {printf("%s is a Function\n",yytext);fprintf(yyout,"%d\t%s\tFunction\n",line,yytext);}
printf[^(] {printf("%s is a Error\n",yytext);fprintf(yyout,"%d\t%s\tError\n",line,yytext);}

scanf {printf("%s is a Function\n",yytext);fprintf(yyout,"%d\t%s\tFunction\n",line,yytext);}
scanf[^(] {printf("%s is a Error\n",yytext);fprintf(yyout,"%d\t%s\tError\n",line,yytext);}

"//"(.)* {printf("%s is a Comment\n",yytext);fprintf(yyout,"%d\t%s\tComment\n",line,yytext);}
"/*"(.|\n)"*/" {printf("%s is a Comment\n",yytext);fprintf(yyout,"%d\t%s\tComment\n",line,yytext);}

[A-Za-z_][A-Za-z0-9]* {printf("%s is a Identifier\n",yytext);fprintf(yyout,"%d\t%s\tIdentifier\n",line,yytext);}
[0-9]+ {printf("%s is a Digit\n",yytext);fprintf(yyout,"%d\t%s\tDigit\n",line,yytext);}

[(){},;:/\\] {printf("%s is a Symbol\n",yytext);fprintf(yyout,"%d\t%s\tSymbol\n",line,yytext);}

"\n" {++line;}
" " ;
%%

int main()
{
yyin = fopen("test.cpp","r");
yyout=fopen("output.txt","w");
fprintf(yyout,"Line\tLexeme\ttoken\n");
yylex();
fclose(yyin);
return 1;
}

int yywrap()
{
return 1;
}

void yyerror()
{
printf("Error");
}
