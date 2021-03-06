// Tokens
%token 
  INT  
  PLUS
  SUB
  MULT
  DIV
  REST
  EQUALS
  DIFF
  LESS
  BIG
  LESS_EQUAL
  BIG_EQUAL

// Operator associativity & precedence
%left EQUALS
%left DIFF
%left LESS
%left BIG
%left LESS_EQUAL
%left BIG_EQUAL
%left PLUS
%left SUB
%left MULT
%left DIV
%left REST

// Root-level grammar symbol
%start program;

// Types/values in association to grammar symbols.
%union {
  int intValue;
  Expr* exprValue;
  BoolExpr* boolValue;
}

%type <intValue> INT
%type <exprValue> expr
%type <boolValue> boolV

// Use "%code requires" to make declarations go
// into both parser.c and parser.h
%code requires {
#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

extern int yylex();
extern int yyline;
extern char* yytext;
extern FILE* yyin;
extern void yyerror(const char* msg);
Expr* root;
BoolExpr *bool_root;
}

%%
program: expr { root = $1; }
program: boolV { bool_root = $1; }

expr: 
  INT { 
    $$ = ast_integer($1); 
  }
  | 
  expr PLUS expr { 
    $$ = ast_operation(PLUS, $1, $3); 
  }
  |
  expr SUB expr {
    $$ = ast_operation(SUB, $1, $3);
  }
  |
  expr MULT expr {
    $$ = ast_operation(MULT, $1, $3);
  }
  |
  expr DIV expr {
    $$ = ast_operation(DIV, $1, $3);
  }
  |
  expr REST expr {
    $$ = ast_operation(REST, $1, $3);
  }

boolV:
  expr EQUALS expr {
    $$ = ast_boperation(EQUALS, $1, $3);
  }
  |
  expr DIFF expr {
    $$ = ast_boperation(DIFF, $1, $3);
  }
  |
  expr LESS expr {
    $$ = ast_boperation(LESS, $1, $3);
  }
  |
  expr BIG expr {
    $$ = ast_boperation(BIG, $1, $3);
  }
  |
  expr LESS_EQUAL expr {
    $$ = ast_boperation(LESS_EQUAL, $1, $3);
  }
  |
  expr BIG_EQUAL expr {
    $$ = ast_boperation(BIG_EQUAL, $1, $3);
  }
  ;
%%

void yyerror(const char* err) {
  printf("Line %d: %s - '%s'\n", yyline, err, yytext  );
}

