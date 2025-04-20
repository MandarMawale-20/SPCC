%{
#include <stdio.h>
int count = 0;
%}

%%
"<"  { printf("LESS THAN: %s\n", yytext); count++; }
">"  { printf("GREATER THAN: %s\n", yytext); count++; }
"<=" { printf("LESS THAN OR EQUAL TO: %s\n", yytext); count++; }
">=" { printf("GREATER THAN OR EQUAL TO: %s\n", yytext); count++; }
"==" { printf("EQUAL TO: %s\n", yytext); count++; }
"!=" { printf("NOT EQUAL TO: %s\n", yytext); count++; }
[ \t\n] { /* Ignore whitespace */ }
. { /* Ignore other characters */ }
%%

int main() {
    printf("Enter expressions with relational operators:\n");
    yylex();
    printf("Total relational operators found: %d\n", count);
    return 0;
}

int yywrap() {
    return 1;
}