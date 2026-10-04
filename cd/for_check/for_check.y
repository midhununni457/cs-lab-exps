%{
#include <stdio.h>
int yylex();
void yyerror(char *s);
%}

%token FOR ID NUM LE GE EQ NE INC DEC

%%

stmt: FOR '(' init ';' cond ';' upd ')' { printf("Valid FOR statement\n"); return 0; }
    ;

init: ID '=' expr
    ;

cond: expr relop expr
    ;

relop: '<' | '>' | LE | GE | EQ | NE
     ;

upd: ID INC
   | ID DEC
   | ID '=' expr
   ;

expr: expr '+' term
    | expr '-' term
    | term
    ;

term: ID
    | NUM
    ;

%%

void yyerror(char *s) {
    printf("Invalid FOR statement\n");
}

int main() {
    printf("Enter FOR statement: ");
    yyparse();
    return 0;
}

/*
Note: This sample input is for the final executed file (output of gcc after compiling y.tab.c and lex.yy.c).

Sample Input 1:
for(i=0;i<10;i++)
Expected Output:
Valid FOR statement

Sample Input 2:
for(i=0;i<10)
Expected Output:
Invalid FOR statement
*/

