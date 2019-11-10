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
"true" { yylval.intValue = 1; return BOOL; }
"false" { yylval.intValue = 0; return BOOL; }

"while" { return WHILE; }
"if" { return IF; }
"else" { return ELSE; }

"=" { return EQUAL; }
";" { return COMMA; }
"{" { return OPEN_PARENT; }
"}" { return CLOSE_PARENT; }
"(" { return OPEN_BRACKET; }
")" { return CLOSE_BRACKET; }

"println!(\"{}\"," { return PRINTLN; }
"= String::new();" { return READSTRING; }
"= std::io::stdin().read_line(&mut" { return READLN; }
"mut" { return MUT; }
".unwrap();" { return UNWRAP; }

"let" { return LET; }
"fn main()" { return MAIN; }

[a-zA-Z][a-zA-Z0-9]* { yylval.variable =(char*)strdup(yytext); return VARIABLE; }

.  { yyerror("unexpected character"); }
%%

