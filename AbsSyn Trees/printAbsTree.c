#include <stdlib.h>
#include "parser.h"
#include "printAbsTree.h"

void printExpr(Expr *exp) {
  if(exp == 0)
    yyerror("Null expression!!");
  else if(exp -> kind == E_INTEGER)
    printf("%d ", exp -> attr.value);
  else if(exp -> kind == E_OPERATION) {
    printExpr(exp -> attr.op.left);
    printExpr(exp -> attr.op.right);
    switch(exp -> attr.op.operator) {
    case PLUS:
      printf("+ ");
      break;
    case SUB:
      printf("- ");
      break;
    case MULT:
      printf("* ");
      break;
    case DIV:
      printf("/ ");
      break;
    case REST:
      printf("mod ");
      break;
    default: yyerror("Unknown operator!");
    }
  }
  printf("\n");
}

void printBool(BoolExpr *b) {
  if(b == 0)
    yyerror("NULL expression!!");
  else {
    printExpr(b -> bool_op.left);
    printExpr(b -> bool_op.right);
    switch(b -> bool_op.bool_operator) {
    case EQUALS:
      printf("==");
      break;
    case DIFF:
      printf("!=");
      break;
    case LESS:
      printf("<");
      break;
    case BIG:
      printf(">");
      break;
    case LESS_EQUAL:
      printf("<=");
      break;
    case BIG_EQUAL:
      printf(">=");
      break;
    default: yyerror("Unknown operator!");
    }
  }
  printf("\n");
}
