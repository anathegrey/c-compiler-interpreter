%{
// HEADERS
#include <stdlib.h>
#include "parser.h"

// variables maintained by the lexical analyser
int yyline = 1;
%}

%option noyywrap

%%
[ \t]+ {  }
#.*\n { yyline++; }
\n { yyline++; }

\-?[0-9]+ { 
   yylval.intValue = atoi(yytext);
   return INT; 
}

"+" { return PLUS; }
"-" { return SUB; }
"*" { return MULT; }
"/" { return DIV; }
"%" { return REST; }
"==" { return EQUALS; }
"!=" { return DIFF; }
"<" { return LESS; }
">" { return BIG; }
"<=" { return LESS_EQUAL; }
">=" { return BIG_EQUAL; }

.  { yyerror("unexpected character"); }
%%

