%{
#include <stdio.h>
#include <string.h>
%}

%%

[a-zA-Z]+   {
    if (strstr(yytext, "Midh") == NULL)
        printf("Accepted: %s\n", yytext);
    else
        printf("Rejected: %s\n", yytext);
}

\n  ;

%%

int yywrap() { return 1; }

int main() {
    printf("Enter strings (Ctrl+Z to stop):\n");
    yylex();
    return 0;
}
