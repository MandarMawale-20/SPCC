%{
#include <stdio.h>
#include <stdlib.h>
%}

%%
[0-9]+ {
    int num = atoi(yytext);
    if(num % 2 == 0)
        printf("%d is Even\n", num);
    else
        printf("%d is Odd\n", num);
}
. { /* Ignore other characters */ }
\n { /* Ignore newlines */ }
%%

int main() {
    printf("Enter an integer: ");
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}