%{
#include <stdio.h>
%}

%%
[aeiouAEIOU] { printf("%s is a Vowel\n", yytext); }
[a-zA-Z] { printf("%s is a Consonant\n", yytext); }
. { printf("%s is not a letter\n", yytext); }
\n { /* Ignore newlines */ }
%%

int main() {
    printf("Enter a character: ");
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}