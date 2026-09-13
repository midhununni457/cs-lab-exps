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
