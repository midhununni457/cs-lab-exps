%{
#include <stdio.h>
#include <string.h>
%}

%%

[a-zA-Z]+   {
    if (strstr(yytext, "abcd") == NULL)
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

/*
Sample Input (for the final executed file / output of gcc):
apple
abcdef
hello
abcd

Expected Output:
Accepted: apple
Rejected: abcdef
Accepted: hello
Rejected: abcd
*/

