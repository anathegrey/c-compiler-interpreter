#include <stdio.h>
#include "parser.h"

void printBool(BoolExpr *b);
void printCmd(CmdList *l);

void printExpr(Expr *exp) {
  if(exp == 0)
    yyerror("Null expression!!");
  else if(exp -> kind == E_INTEGER)
    printf("%d", exp -> attr.value);
  else if(exp -> kind == E_VAR)
    printf("%s", exp -> attr.var);
  else if(exp -> kind == E_BOOL)
    printf("%d", exp -> attr.b_value);
  else if(exp -> kind == E_OPERATION) {
    printExpr(exp -> attr.op.left);
    printExpr(exp -> attr.op.right);
    switch(exp -> attr.op.operator) {
    case PLUS:
      printf(" + ");
      break;
    case SUB:
      printf(" - ");
      break;
    case MULT:
      printf(" * ");
      break;
    case DIV:
      printf(" / ");
      break;
    case REST:
      printf(" mod ");
      break;
    default: yyerror("Unknown operator!");
    }
  }
  else if(exp -> kind == IF_CON) {
    printf("if ");
    printBool(exp -> attr.if_else.if_op.if_statement.if_state);
    printf(" {\n");
    printCmd(exp -> attr.if_else.if_op.if_statement.if_condition);
    printf("\n}\n");
  }
  else if(exp -> kind == ELSE_CON) {
    printf("if ");
    printBool(exp -> attr.if_else.if_op.else_statement.if_state);
    printf(" {\n");
    printCmd(exp -> attr.if_else.if_op.else_statement.if_condition);
    printf("\n}\nelse {\n");
    printCmd(exp -> attr.if_else.if_op.else_statement.else_condition);
    printf("\n}\n");
  }
}

void printBool(BoolExpr *b) {
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

void printSeq(Cmd *i) {
  switch(i -> kind) {
  case EXPR:
    printExpr(i -> cmd_attr.cmd);
    break;
  case ATTRIB_EXPR: //atribuições
    printf("let %s = ", i -> cmd_attr.attrib.var);
    printExpr(i -> cmd_attr.attrib.attrib_op.expr);
    printf("; ");
    break;
    /*case ATTRIB_IF:
    printf("let %s = ", i -> cmd_attr.attrib.var);
    printCmd(i -> cmd_attr.attrib.attrib_op.cmdif);
    printf("; ");
    break;*/
  case CMD_PRINT: //println
    printf("println!(\"{}\",");
    printExpr(i -> cmd_attr.print.expr);
    printf(");\n");
    break;
  case CMD_READ:  //read_line
    printf("let %s = String::new();\nlet %s = std::io::stdin().read_line(&mut %s).unwrap();", (i -> cmd_attr.read.var), (i -> cmd_attr.read.aux_var), (i -> cmd_attr.read.var));
    break;
  case CMD_WHILE:  //while
    printf("while ");
    printBool(i -> cmd_attr.while_op.while_state);
    printf(" {\n");
    printCmd(i -> cmd_attr.while_op.while_condition);
    printf("\n}\n");
    break;
  default: yyerror("Unknown operator!");
  }
}

void printCmd(CmdList *l) {
  while(l != NULL) {
    printSeq(l -> cmd);
    l = l -> next;
  }
}

int main(int argc, char** argv) {
  --argc; ++argv;
  if (argc != 0) {
    yyin = fopen(*argv, "r");
    if (!yyin) {
      printf("'%s': could not open file\n", *argv);
      return 1;
    }
  } //  yyin = stdin
  if (yyparse() == 0) {
    printCmd(root);
    printf("\n");
  }
  return 0;
}
