%{
#include<stdio.h>
extern int yylex();
extern void yyerror(const char *s);
%}
%token NUMBER
%left '+' '-'
%left '*' '/' '%'
%left '(' ')'

%%
ArithmeticExpression:
E {
printf("Result %d",$$);
return 0;};
E:E'+'E {$$=$1+$3;}
|E'-'E {$$=$1-$3;}
|E'*'E {$$=$1*$3;}
|E'/'E {$$=$1/$3;}
|E'%'E {$$=$1%$3;}
|'('E')' {$$=$2;}
|NUMBER {$$=$1;};
%%

int main(){
printf("Enter expression:");
return yyparse();

}
void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}
