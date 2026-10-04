%{
#include <stdio.h>
int yylex();
void yyerror(char *s);
%}

%token LETTER DIGIT

%%

stmt: var '\n'  { printf("Valid variable\n"); return 0; }
    ;

var: LETTER rest
   ;

rest: LETTER rest
    | DIGIT rest
    |
    ;

%%

void yyerror(char *s) {
    printf("Invalid variable\n");
}

int main() {
    printf("Enter variable name: ");
    yyparse();
    return 0;
}

/*
Note: This sample input is for the final executed file (output of gcc after compiling y.tab.c and lex.yy.c).

Sample Input 1:
count1
Expected Output:
Valid variable

Sample Input 2:
1count
Expected Output:
Invalid variable
*/

