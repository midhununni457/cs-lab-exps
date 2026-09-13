%{
#include <stdio.h>
int yylex();
void yyerror(char *s);
%}

%token NUM
%left '+' '-'
%left '*' '/'

%%

stmt: expr '\n'   { printf("Result: %d\n", $1); return 0; }
    ;

expr: expr '+' expr  { $$ = $1 + $3; }
    | expr '-' expr  { $$ = $1 - $3; }
    | expr '*' expr  { $$ = $1 * $3; }
    | expr '/' expr  { $$ = $1 / $3; }
    | '(' expr ')'   { $$ = $2; }
    | NUM             { $$ = $1; }
    ;

%%

void yyerror(char *s) {
    printf("Error: %s\n", s);
}

int main() {
    printf("Enter expression: ");
    yyparse();
    return 0;
}
