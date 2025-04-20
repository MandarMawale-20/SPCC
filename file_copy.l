%{
#include <stdio.h>
%}

%%
.|\n { ECHO; } /* ECHO prints the matched text */
%%

int main() {
    FILE *file;
    file = fopen("input.txt", "r");
    if (!file) {
        fprintf(stderr, "Could not open input.txt\n");
        return 1;
    }
    yyin = file;
    yylex();
    fclose(file);
    return 0;
}

int yywrap() {
    return 1;
}