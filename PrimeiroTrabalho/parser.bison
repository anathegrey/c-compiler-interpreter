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
  BOOL
  WHILE
  IF
  ELSE
  EQUAL
  COMMA
  OPEN_PARENT
  CLOSE_PARENT
  OPEN_BRACKET
  CLOSE_BRACKET
  PRINTLN
  READSTRING
  READLN
  MUT
  UNWRAP
  LET
  MAIN
  VARIABLE
  

// Operator associativity & precedence
%left PLUS
%left SUB
%left MULT
%left DIV
%left REST
%left EQUALS
%left DIFF
%left LESS
%left BIG
%left LESS_EQUAL
%left BIG_EQUAL

// Root-level grammar symbol
%start program;

// Types/values in association to grammar symbols.
%union {
  int intValue;
  Expr* exprValue;
  BoolExpr *boolValue;
  CmdSeq *cmdValue;
  char *variable;
  CmdList *cmdList;
}

%type <intValue> INT
%type <exprValue> expr
%type <boolValue> boolexpr
%type <cmdValue> cmd_seq
%type <variable> VARIABLE
%type <cmdList> cmd_list

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
CmdList *root;
}

%%
program: run_main

run_main: MAIN OPEN_PARENT cmd_list CLOSE_PARENT { root = $3; }

cmd_list:
  /* empty */ { $$ = NULL; }
  |
  cmd_seq COMMA cmd_list {
    $$ = list_operation($1, $3);
  }
  ;

cmd_seq:
  IF boolexpr OPEN_PARENT cmd_list CLOSE_PARENT {
    $$ = if_operation($2, $4);
  }
  |
  IF boolexpr OPEN_PARENT cmd_list CLOSE_PARENT ELSE OPEN_PARENT cmd_list CLOSE_PARENT {
    $$ = else_operation($2, $4, $8);
  }
  |
  WHILE boolexpr OPEN_PARENT cmd_list CLOSE_PARENT {
    $$ = while_operation($2, $4);
  }
  |
  LET VARIABLE EQUAL expr {
    $$ = attrib_operation($2, $4);
  }
  |
  LET VARIABLE EQUAL cmd_list {
    $$ = attribif_operation($2, $4);
  }
  |
  LET MUT VARIABLE READSTRING LET VARIABLE READLN VARIABLE CLOSE_BRACKET UNWRAP {
    $$ = read_operation($3);
  }
  |
  PRINTLN expr CLOSE_BRACKET COMMA {
    $$ = print_operation($2);
  }
  ;

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
  ;

boolexpr:
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

