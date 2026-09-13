%{
#include "y.tab.h"
%}

%%

[a-zA-Z]    return LETTER;
[0-9]       return DIGIT;
\n          return '\n';
.           return yytext[0];

%%

int yywrap() { return 1; }
