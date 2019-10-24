%start prog;
%define api.value.type { double }
%left LEFT_PAR
%left RIGHT_PAR
%left MULT_TOKEN
%left DIV_TOKEN
%left ADD_TOKEN
%left SUB_TOKEN
%token NUMBER_TOKEN  // Numbers 
%token ADD_TOKEN // +
%token SUB_TOKEN // -
%token MULT_TOKEN // *
%token DIV_TOKEN // /
%token LEFT_PAR // (
%token RIGHT_PAR // )

%{
#include <stdio.h>
#include "common.h"
%}

%%
prog: /* empty */
    | expr prog { printf("%lf\n", $1); }

expr: NUMBER_TOKEN { $$ = $1; }
   | expr ADD_TOKEN expr { $$ = $1 + $3; }
   | expr SUB_TOKEN expr { $$ = $1 - $3; }
   | expr MULT_TOKEN expr { $$ = $1 * $3; }
   | expr DIV_TOKEN expr { $$ = $1 / $3; }
   | LEFT_PAR expr RIGHT_PAR { $$ = ( $2 ); }
   ;

%%
#include <stdio.h>

int main(int argc, char **argv)
{
  if (argc > 0) yyin = fopen(argv[1], "r");
  yyparse();
  return 0;
}

